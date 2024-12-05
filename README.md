# Simon-Game
This is a term project that I built for the class ENSE 352: Fundamentals of Computer Systems Architecture



**Important Note**
**The video currently excludes the following:**
1. The current code provided in this file has implemented the "Knight Ryder" sequence when the user presses the button to reset/start a new game In the video, the "Knight Ryder" sequence is not shown when you restart the game. The newest version of the code **fixes** this.

I have also added a delay between the user repeating the sequence, and the device showing you the **next sequence**.



# Project Description

Simon is an electronic game of short-term memory skill. Upon starting the game, the device will give the first signal, (turn the first light on) and the user will have to repeat that sequence back using buttons as an input. The device will then duplicate the first signal and add a new signal. This process will continue up until the 10th round. (The user will have to repeat back a sequence of 10 signals)

## Knight Ryder Sequence
The Knight Ryder sequence is a sequential sequence that lights each LED, from the first to the last. Once the last LED is lit, it reverses and lights the last LED to the first. This gives the illusion of a "moving light".

## Winning Sequence
The winning sequence is displayed only when the user has completed all 10 rounds. The winning sequence is displayed as all 4 LED's flashing 4 times. It will then flash the number "10" in binary on the LEDs (1010)

Failure to repeat the signals correctly will result in a failure sequence. 
## Failure Sequence
Failure sequences will occur when:

- The user fails to repeat the signal(s) correctly
- The user takes too long (more than 3 seconds in this case) to repeat the sequence.

The failure sequence is displayed when at least one of these situations occur. The failure sequence has been implemented as "police lights". 
The sequence divides LEDs into two groups (e.g., Left Group and Right Group).
LEDs in the Left Group light up while the Right Group remains off.
After a short delay, LEDs in the Right Group light up while the LEDs in the Left Group are turned off.

After the failure sequence, the LEDs will display the round you failed on. 
    Example: Failed on round 5 -> LEDs will show: (0101)

# Components Used
STM32F103RB, Breadboard, 270 Ohm Resistor, 10K Ohm Bus Resistor, 4 Red LED's, 4 Push Buttons, wires


# How do you play?
## 1. Start the Game
When you start the game, the Knight Ryder sequence is displayed on the LEDs
Then you can press any button to start the game

## 2. Game Rounds
Pressing the button, the user starts the game, which consists of 10 rounds. The sequence starts with one LED, and increases in sequence length if you correctly repeat the sequence. You have 3 seconds to press the button for each bit in the sequence. If you successfully complete all 10 rounds, the winning sequence will play. The game will then wait for you to press any button to restart the game.
Upon pressing any button, the Knight Ryder sequence will start up, indicating the game is in idle waiting for you to start playing again!

## 3. Enjoy!
Challenge your brain, and enjoy playing Simon!



