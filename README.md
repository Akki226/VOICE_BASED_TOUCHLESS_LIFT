# VOICE_BASED_TOUCHLESS_LIFT
This repository contains the code and documentation for a voice controlled lift prototype. The lift uses various hardware devices to function, including:

- IR sensors to count the floors
- Elechouse V3 for speech recognition
- Microcontroller ATMEGA328P
- Arduino Uno for the movement of the drivers

The software of this prototype is implemented using embedded C programming language, and it uses libraries and packages that are necessary for the functionality of the system.

# Installation
To install the necessary libraries and packages, please follow these steps:

- Install the Arduino IDE on your computer.
- Connect the Arduino Uno board to your computer using a USB cable.
- Open the Arduino IDE and select the correct board and port in the settings.
- Import the necessary libraries by going to Sketch > Include Library > Manage Libraries.
- Install the Elechouse V3 library.
- Install the IRremote library.
- Install the Servo library.
- Download the code from the repository and upload it to the Arduino board.

# Usage

- Turn on the lift and wait for the system to initialize.
- Say the desired floor number for example "Floor one" or "Floor two"
- The lift will move to the selected floor.
