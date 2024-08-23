# Pong Game for Pico with OLED Display

## Overview

This project is a classic Pong game implemented on an Arduino board using an SSD1306 OLED display. It features two-player gameplay with one player controlling a paddle using a potentiometer and the other using a joystick. The game includes scoring, speed increases after each paddle hit, and sound effects via a buzzer.

## Features

- **Two-Player Game:** One player uses a potentiometer and the other uses a joystick to control their paddles.
- **Scoring System:** The game keeps track of each player's score and declares a winner once a player reaches the maximum score.
- **Sound Effects:** The game generates sound effects for scoring points and winning, enhancing the gaming experience.
- **Dynamic Speed:** The ball's speed increases each time it hits a paddle, making the game more challenging over time.
- **OLED Display:** The game is displayed on a 128x64 OLED screen, with real-time paddle movement and ball position updates.

## Components

- **Pico:** Used to run the game logic.
- **SSD1306 OLED Display:** 128x64 pixels, used to display the game.
- **Potentiometer:** Controls the left player's paddle.
- **Joystick:** Controls the right player's paddle.
- **Buzzer:** Provides sound effects for gameplay events.
- **Wiring:**
  - Potentiometer Pin: Connected to ADC0 (Pin 26).
  - Joystick Y-axis: Connected to ADC2 (Pin 28).
  - Buzzer Pin: Connected to a suitable PWM-capable pin (Pin 21).

## Game Controls

- **Left Player:** Uses the potentiometer to move the paddle up and down.
- **Right Player:** Uses the joystick’s Y-axis to move the paddle up and down.

## Game Rules

- The ball bounces off the top and bottom of the screen.
- The ball changes direction when it hits a paddle.
- If the ball passes a paddle, the opposing player scores a point.
- The game ends when a player reaches the maximum score of 5 points.
- A victory sound and message are displayed for the winning player.

## Setup and Installation

1. **Wiring:**
   - Connect the OLED display, potentiometer, joystick, and buzzer to the appropriate pins on the Arduino.
2. **Arduino Libraries:**
   - Install the `Adafruit GFX` and `Adafruit SSD1306` libraries using the Arduino IDE Library Manager.
3. **Upload the Code:**
   - Copy and upload the provided code to your Arduino using the Arduino IDE.

## How to Play

1. Power the Arduino.
2. Use the potentiometer and joystick to move the paddles.
3. The first player to reach 5 points wins the game.

## Customization

You can easily customize the game by:
- Adjusting the paddle and ball sizes.
- Modifying the winning score.
- Tuning the sound effects and speeds.

## License

This project is open-source and free to use under the MIT License. Feel free to modify and improve it!
