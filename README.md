# Alarm-Clock-Puzzle

This code was written for IEEE @ UCSD's Fall 2022 Quarterly Projects competition.

Have you ever found yourself subconsciously pressing the snooze button for your alarm after it goes off over and over again, effectively defeating the purpose of the alarm?

This project aims to fix that by removing the snooze button entirely!

Here's the idea: 
The clock will function like a typical alarm clock, except when the alarm goes off there is no snooze button. Instead, the user must solve a puzzle by pressing the displayed buttons in the correct order - all while the alarm is going off! This way, you will never have to worry about waking up late again!

You're welcome!

User Testimonials:

"This is the greatest product that I have ever used in my entire life! Thanks Alarm-Clock-Puzzle!"
\- You, probably

(end of user testimonials)

# User Instructions

There are 6 buttons of varying colors. On the right, there are 2 white buttons for setting the clock time (left) and setting the alarm time (right). On the left, there are 4 buttons that have the following functionalities (left-to-right, respectively): the red button will decrement the hours displayed on the clock or alarm time when in a setting mode, the black button increments the hours displayed when in a setting mode, the yellow button decrements the minutes displayed in a setting mode, and finally the blue button increments the minutes displayed in a setting mode. Of course, the buttons are also used to solve the puzzle, should the alarm be triggered.

To set the clock time, press the clock set button once, use the left 4 buttons to adjust the time as desired, and then press the clock set button once again to confirm the changes (or press the alarm set button to cancel the changes). Similarly, to set the alarm time, press the alarm set button, use the left 4 buttons to adjust the time as desired, and then press the alarm set button again to confirm the changes (or press the clock set button to cancel the changes). Please note that you will have to re-set the alarm each time after it goes off.

When the alarm goes off, the buzzer will consistently play an ear-splitting, high-pitched frequency that has been optimized to wake up the average person in less than 0.7396 seconds (source: Arduino random number generator). Then, the user will be tasked with solving an extremely challenging puzzle (200+ IQ required) that involves pressing the button color that is displayed on the screen.
