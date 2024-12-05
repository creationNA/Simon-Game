#include "stm32f10x.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUMBER_OF_LEDS 4
int seed = 0;

void delay_ms(int delay);

void setup(){
    // Enable clocks for GPIOA and GPIOB
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN;

    // Configure PA0, PA1, PA4 as outputs (50 MHz, General-purpose output push-pull)
    GPIOA->CRL = 0x00030033;

    // Configure PB4 and PB6 as inputs with pull-up/pull-down
    GPIOB->CRL = 0x04040003;

    // Configure PB8 and PB9 as inputs with pull-up/pull-down
    GPIOB->CRH = 0x00000044;
}


//PUSHPULL ALLOWS US TO SET:
//WHEN BUTTON IS PRESSED, IT IS A LOGIC LOW (0), WHEN NOT PRESSED, IT IS LOGIC HIGH (1)
// Function to light a specific LED
void light_led(int led){
    // Clear all LEDs first
    GPIOA->ODR = 0x00;
    GPIOB->ODR &= ~(1 << 0);

    // Turn on the specified LED
    switch (led) {
        case 0: GPIOA->ODR = GPIOA->ODR | (1 << 0);
				break; // PA0
			
        case 1: GPIOA->ODR = GPIOA->ODR | (1 << 1);
				break; // PA1
			
        case 2: GPIOA->ODR = GPIOA->ODR | (1 << 4);
				break; // PA4
			
        case 3: GPIOB->ODR = GPIOB->ODR | (1 << 0);
				break; // PB0
    }
}
// Function to check if the corresponding button is pressed
int check_button(int led){
    switch (led) {
        case 0:
					return !(GPIOB->IDR & (1 << 4)); // Button PB4 for LED PA0
        case 1:
					return !(GPIOB->IDR & (1 << 6)); // Button PB6 for LED PA1
        case 2:
					return !(GPIOB->IDR & (1 << 8)); // Button PB8 for LED PA4
        case 3:
					return !(GPIOB->IDR & (1 << 9)); // Button PB9 for LED PB0
    }
    return 0;
}
// Function to flash all LEDs as feedback for success
void success_feedback(){
    for (int i = 0; i < 4; i++) {
        GPIOA->ODR = 0x1F; 
        GPIOB->ODR |= (1 << 0); // Turn on PB0
        delay_ms(100);
        GPIOA->ODR = 0x00; 
        GPIOB->ODR &= ~(1 << 0); // Turn off PB0
        delay_ms(100);
    }
}

void failure_feedback() {
    for (int i = 0; i < 2; i++) { 
        // Flash Left Group LEDs (PA0 and PA1)
        GPIOA->ODR = (1 << 0) | (1 << 1); // Turn on PA0 and PA1
        delay_ms(300);
        GPIOA->ODR = 0x00; // Turn off all LEDs
        GPIOB->ODR &= ~(1 << 0); // Ensure PB0 is off
        delay_ms(300);

        // Flash Right Group LEDs (PA4 and PB0)
        GPIOA->ODR = (1 << 4); // Turn on PA4
        GPIOB->ODR |= (1 << 0); // Turn on PB0
        delay_ms(300);
        GPIOA->ODR = 0x00; // Turn off all LEDs
        GPIOB->ODR &= ~(1 << 0); // Turn off PB0
        delay_ms(300);
    }
		
}




int scannerPattern(){
	 int local_seed = 0	;
	 while (1) { // Infinite loop for the Knight Rider sequence
        // Forward scanning
				local_seed++;
        GPIOA->ODR = (1 << 0); // Turn on PA0
        delay_ms(99);
        if (check_button(0) || check_button(1) || check_button(2) || check_button(3)) break; 
        GPIOA->ODR &= ~(1 << 0); // Turn off PA0
				
				local_seed++;
        GPIOA->ODR = (1 << 1); // Turn on PA1
        delay_ms(99);
        if (check_button(0) || check_button(1) || check_button(2) || check_button(3)) break;
        GPIOA->ODR &= ~(1 << 1); // Turn off PA1
		 
				local_seed++;
        GPIOA->ODR = (1 << 4); // Turn on PA4
        delay_ms(99);
        if (check_button(0) || check_button(1) || check_button(2) || check_button(3)) break;
        GPIOA->ODR &= ~(1 << 4); // Turn off PA4
		 
				local_seed++;
        GPIOB->ODR = (1 << 0); // Turn on PB0
        delay_ms(99);
        if (check_button(0) || check_button(1) || check_button(2) || check_button(3)) break;
        GPIOB->ODR &= ~(1 << 0); // Turn off PB0

        // Backward scanning
				local_seed++;
        GPIOA->ODR = (1 << 4); // Turn on PA4
        delay_ms(99);
        if (check_button(0) || check_button(1) || check_button(2) || check_button(3)) break;
        GPIOA->ODR &= ~(1 << 4); // Turn off PA4
				
				local_seed++;
        GPIOA->ODR = (1 << 1); // Turn on PA1
        delay_ms(99);
        if (check_button(0) || check_button(1) || check_button(2) || check_button(3)) break;
        GPIOA->ODR &= ~(1 << 1); // Turn off PA1

				local_seed++;
        GPIOA->ODR = (1 << 0); // Turn on PA0
        delay_ms(99);
        if (check_button(0) || check_button(1) || check_button(2) || check_button(3)) break;
        GPIOA->ODR &= ~(1 << 0); // Turn off PA0
    }
		
    // Turn off all LEDs after exiting the loop
    GPIOA->ODR = 0x00;
    GPIOB->ODR &= ~(1 << 0);
		
		return local_seed;
		
		
}



void showRound(int roundfail) {
    GPIOA->ODR = 0x00;  // Turn off all LEDs initially
    GPIOB->ODR &= ~(1 << 0);

    for (int i = 0; i < 4; i++) { // Flash the round display twice
        switch (roundfail) {
            case 1:
                GPIOA->ODR = (1 << 0); // Turn on LED PA0
                break;
            case 2:
                GPIOA->ODR = (1 << 1); // Turn on LED PA1
                break;
            case 3:
                GPIOA->ODR = (1 << 0) | (1 << 1); // Turn on PA0 and PA1
                break;
            case 4:
                GPIOA->ODR = (1 << 4); // Turn on LED PA4
                break;
            case 5:
                GPIOA->ODR = (1 << 0) | (1 << 4); // Turn on PA0 and PA4
                break;
            case 6:
                GPIOA->ODR = (1 << 1) | (1 << 4); // Turn on PA1 and PA4
                break;
            case 7:
                GPIOA->ODR = (1 << 0) | (1 << 1) | (1 << 4); // Turn on PA0, PA1, PA4
                break;
            case 8:
                GPIOB->ODR = (1 << 0); // Turn on LED PB0
                break;
            case 9:
                GPIOA->ODR = (1 << 0); // Turn on PA0
                GPIOB->ODR = (1 << 0); // Turn on PB0
                break;
            case 10:
                GPIOA->ODR = (1 << 1); // Turn on PA1
                GPIOB->ODR = (1 << 0); // Turn on PB0
                break;
            default:
                GPIOA->ODR = 0x00; // Clear LEDs if roundfail is out of range
                GPIOB->ODR &= ~(1 << 0);
                break;
        }

        //delay_ms(300);           // LEDs on for 300ms
       // GPIOA->ODR = 0x00;       // Turn off LEDs
      //  GPIOB->ODR &= ~(1 << 0); // Turn off PB0
       // delay_ms(300);           // LEDs off for 300ms
    }

   
}


int randomNumberTo4()
{
		
    int limit;
    int r;

    limit = RAND_MAX - (RAND_MAX % NUMBER_OF_LEDS);

    while((r = rand()) >= limit);
 
    return r % NUMBER_OF_LEDS;
}

int main() {
    setup();

    int sequence[10];
    int round;
    int restart;
    while (1) {

				
        seed = scannerPattern();
				srand(seed);
       
        round = 1;
        restart = 0;

        // Generate random LED sequence
        for (int i = 0; i < 10; i++) {
            sequence[i] = randomNumberTo4();
        }

        // Game loop
        while (round <= 10) {
            // Display the sequence for the current round
            for (int i = 0; i < round; i++) {
                light_led(sequence[i]); // Light up LED
                delay_ms(500);          // Wait for the user to memorize
                GPIOA->ODR = 0x00;      
                GPIOB->ODR &= ~(1 << 0);
                delay_ms(250);          
            }

            // Player's turn to mimic the sequence
            for (int i = 0; i < round; i++) {
                int time_elapsed = 0;
                int correct_press = 0;

                while (time_elapsed < 3000) { // 3-second time limit per LED
                    delay_ms(10);
                    time_elapsed += 10;

                    // Check if any button is pressed
                    for (int button = 0; button < NUMBER_OF_LEDS; button++) {
                        if (check_button(button)) {
                            if (button == sequence[i]) { //If you press the right button
                                
                                light_led(button); // Light up corresponding LED
                                delay_ms(200);     
                                GPIOA->ODR = 0x00;
                                GPIOB->ODR &= ~(1 << 0);
                                correct_press = 1; // Mark as correct
                                break;
                            } else {
                                // Incorrect button pressed
                                failure_feedback();
                                showRound(round); // Show the failed round
                                restart = 1;     // Flag to restart the game
                                break;
                            }
                        }
                    }

                    if (correct_press || restart) {
                        break;
                    }
                }

                if (!correct_press && !restart) {
                    
                    failure_feedback();
                    showRound(round); // Show the failed round
                    restart = 1;
                }

                if (restart) {
                    break; 
                }
            }

            if (restart) {
                break; // Restart the game after failure
            }
						delay_ms(500);
      
            round++;
        }

        // Reset condition (either game completed or failed)
        if (restart) {
            // Wait for button press to restart
            while (1) {
                if (check_button(0) || check_button(1) || check_button(2) || check_button(3)) {
                    GPIOA->ODR = 0x00; // Clear LEDs
                    GPIOB->ODR &= ~(1 << 0);
                    scannerPattern(); // Run Knight Rider pattern
                    break;
                }
            }
        } else if (round > 10) {
            // Show success feedback after completing all rounds
            success_feedback();
            showRound(round - 1); // Show the winning round

            // Wait for button press to restart
            while (1) {
                if (check_button(0) || check_button(1) || check_button(2) || check_button(3)) {
                    GPIOA->ODR = 0x00; 
                    GPIOB->ODR &= ~(1 << 0);
                    scannerPattern(); 
                    break;
                }
            }
        }
    }
}


void delay_ms(int delay) {
    for (int i = 0; i < delay * 4000; i++) { }
}
