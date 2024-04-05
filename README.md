# Bosch Test Bench (Automotive)

## Table of Contents

1. [Milestone 1: Arduino PWM Generation Using Timer1 with Selectable Frequencies](#milestone-1-arduino-pwm-generation-using-timer1-with-selectable-frequencies)
	- [Software Requirements](#software-requirements)
	- [Configuration](#configuration)
	- [Frequency and Time Period Details](#frequency-and-time-period-details)
	- [How to Use](#how-to-use)
	- [Code Explanation](#code-explanation)
	- [Notes](#notes)
	- [Visual Representation](#visual-representation)
	- [Side Note: Setting the Compare Match Register for 1kHz Frequency](#side-note-setting-the-compare-match-register-for-1khz-frequency)
	    - [Timer and Compare Match Register](#timer-and-compare-match-register)
	    - [Setting Up for 1kHz Frequency](#setting-up-for-1khz-frequency)
	    - [2kHz Frequency](#2khz-frequency)
	    - [5kHz Frequency](#5khz-frequency)
	    - [0.5Hz Frequency](#0.5hz-frequency)
	    - [What Happens at Runtime](#what-happens-at-runtime)
2. [Milestone 2: OBD 2 Scanner Integration and CAN Reading](#milestone-2-obd-2-scanner-integration-and-can-reading)


## Milestone 1: Arduino PWM Generation Using Timer1 with Selectable Frequencies

## Overview

This Arduino sketch generates a Pulse Width Modulation (PWM) signal using Timer1 interrupts. It allows selecting predefined frequencies for the PWM signal, providing precise control suitable for LED dimming, motor control, and signal generation.


## Hardware Requirements

- Arduino Uno or similar AVR-based board
- LED
- 220 Ohm resistor
- Breadboard and jumper wires

## Software Requirements

- Arduino IDE for uploading the sketch to the Arduino board

## Configuration

- **PWM Pin**: The sketch uses digital pin 9 on the Arduino for PWM output, compatible with Timer1.
- **Predefined Frequencies**: The sketch provides selectable frequencies of 1kHz, 2kHz, 5kHz, and 0.5Hz, each with a corresponding time period.

## Frequency and Time Period Details

- **1kHz (1,000 Hz)**: Time period = 1 millisecond (ms)
- **2kHz (2,000 Hz)**: Time period = 0.5 milliseconds (ms)
- **5kHz (5,000 Hz)**: Time period = 0.2 milliseconds (ms)
- **0.5Hz**: Time period = 2,000 milliseconds (ms)

These time periods represent the duration of one complete cycle of the PWM signal at each frequency.

## How to Use

1. **Connect the Hardware**: Connect the LED and resistor in series between pin 9 and GND on the Arduino.
2. **Set the Desired Frequency**: Open the sketch in the Arduino IDE and select the desired frequency by setting the `FREQUENCY` definition at the top of the sketch (e.g., `#define FREQUENCY FREQ_1KHZ`).
3. **Upload the Sketch**: Connect the Arduino to your computer and upload the sketch using the Arduino IDE.
4. **Observe the PWM Signal**: The connected LED will display the PWM effect at the selected frequency and corresponding time period.

## Code Explanation

- **Timer1 Setup**: Configures Timer1 in Clear Timer on Compare Match (CTC) mode, with the compare match register (OCR1A) value set based on the selected frequency and corresponding time period.
- **Interrupt Service Routine (ISR)**: `TIMER1_COMPA_vect` ISR toggles the LED pin at each timer compare match, creating the PWM signal.
- **Frequency Selection**: Use `#define FREQUENCY` to select the PWM frequency. Available options and their corresponding time periods are defined at the beginning of the sketch.

## Notes

- Frequency values and time periods are calculated based on a 16MHz clock. Adjust these values if using a different clock or prescaler.
- The code is intended for Arduino Uno and similar AVR-based boards.

## Visual Representation

For a visual representation and simulation of the circuit used in this project, visit the following Tinkercad link: [Tinkercad Circuit Simulation](https://www.tinkercad.com/things/abLLm7h7TJJ-funky-juttuli/editel?sharecode=Xo09mCwedb-p-YJO-K1cbwH3dxxOUjxbuBEUPvEbV6E). This simulation provides an interactive way to understand how the components are connected and how the PWM signal affects the circuit. 

## Side Note: Setting the Compare Match Register for Several Frequencies

The line in the code `// Set compare match register to desired timer count for 1kHz frequency` is a crucial part of setting up the Timer1 interrupt in the Arduino. Let's break down this concept for a clearer understanding.

### Timer and Compare Match Register

**Timer Functionality:** In microcontrollers like the Arduino, timers are used for various time-related functions. They can be used for creating delays, measuring time intervals, generating signals, etc. Timers count up (or down) at a specific rate determined by the microcontroller's clock frequency and the timer's prescaler setting.

**Compare Match Register (OCR1A):** The Output Compare Register for Timer1 (OCR1A in this case) is used to set a specific value at which the timer will trigger an action. When the timer's count matches the value in the OCR1A register, an interrupt can be generated (if enabled). This is known as a Compare Match.


the line of code that sets the OCR1A register determines the desired frequency for the interrupt. Here's how it works for each frequency:

### Setting Up for 1kHz Frequency

The Arduino Uno (and similar models) use a 16MHz clock. This is the base frequency from which the timer counts are derived.

The line of code in question sets the OCR1A register to create a specific frequency for the interrupt. In this case, the goal is to achieve a frequency of 1 kHz (1,000 cycles per second).

To calculate the value to load into OCR1A:

1. **Choose a Prescaler:** A prescaler scales down the clock frequency. For instance, a prescaler of 8 will divide the 16MHz clock by 8, resulting in a 2MHz timer clock frequency.

2. **Calculate the Timer Count:** The formula to calculate the value to be put into the OCR1A register for a desired frequency is:

   `OCR1A = (Timer Clock Frequency / Desired Interrupt Frequency) - 1`

3. **Apply the Formula:** For a 1kHz frequency with a 2MHz timer clock (after prescaling by 8), the calculation would be:

   `OCR1A = (2,000,000 / 1,000) - 1 = 1999`

   
### 2kHz Frequency
- Prescaler: 8
- Calculation: `OCR1A = (2,000,000 / 2,000) - 1 = 999`

### 5kHz Frequency
- Prescaler: 8
- Calculation: `OCR1A = (2,000,000 / 5,000) - 1 = 399`

### 0.5Hz Frequency
- Prescaler: 1024 (divides the 16MHz clock by 1024, resulting in a 15,625Hz timer clock)
- Calculation: `OCR1A = (15,625 / 0.5) - 1 = 31,249`

These calculations ensure that the timer generates interrupts at the specified frequencies, creating the desired PWM signals.

### What Happens at Runtime

Each time Timer1 counts to 1999 (starting from 0), the compare match interrupt (`TIMER1_COMPA_vect`) is triggered. This creates a regular interrupt at a frequency of 1kHz. Inside the ISR (Interrupt Service Routine), you can then implement functionality that needs to run at this frequency, like toggling an LED to create a PWM signal.

In summary, setting the compare match register to the appropriate value based on the timer's clock frequency and desired output frequency is a key step in utilizing timers for precise timing operations in microcontrollers.


## Milestone 2: OBD 2 Scanner Integration and CAN Reading

## Overview

This phase of the project focuses on integrating an OBD 2 scanner and reading CAN bus data using an Arduino Uno equipped with a CAN Bus Shield v2. The objective is to establish communication with a vehicle's OBD II interface, enabling the retrieval of real-time automotive diagnostics data over the CAN bus.

## Hardware Requirements

- Arduino Uno or similar AVR-based board
- CAN Bus Shield v2 by Seeed Studio
- DB9 to OBD2 Cable for connecting the CAN Bus Shield to a vehicle's OBD II port

## Software Requirements

- Arduino IDE for compiling and uploading the sketch to the Arduino board.
- Seeed Studio Arduino CAN Shield v2 library must be manually installed from its GitHub repository. Follow these steps to download and install the library:
  1. Visit the GitHub repository at [Seeed Studio Arduino CAN](https://github.com/Seeed-Studio/Seeed_Arduino_CAN.git).
  2. Download the library by clicking on the `Code` button and selecting `Download ZIP`.
  3. Open the Arduino IDE.
  4. Go to `Sketch` > `Include Library` > `Add .ZIP Library...`
  5. Navigate to the downloaded `.zip` file, select it, and click on `Open` to install the library.

After these steps, the Seeed Studio Arduino CAN library will be available in your Arduino IDE, allowing you to compile and upload sketches that communicate with the CAN Bus Shield v2.


## Configuration

The provided Arduino sketch is configured to work with the CAN Bus Shield v2 using the MCP2515 CAN controller. Key configuration details include:

- **SPI CS (Chip Select) Pin**: Digital pin 9 is designated for the SPI CS, facilitating communication with the CAN Bus Shield.
- **Interrupt Pin**: Digital pin 2 is used to handle interrupts from the CAN controller, enabling efficient data processing.
- **CAN Bus Speed**: The CAN interface is initialized with a baud rate of 500Kbps, compatible with most automotive CAN networks.

The sketch employs polling in the `loop()` function to check for incoming CAN frames, which are then processed and displayed via the serial monitor.

## How to Use

To use this setup for OBD II data reading:

1. **Connect the Hardware**: Attach the CAN Bus Shield to the Arduino Uno and connect the DB9 to OBD2 cable from the shield to the vehicle's OBD II port.
2. **Prepare the Software**: Open the Arduino IDE and navigate to the `OBD 2 scanner integration and CAN reading/OBD_2_scanner_integration_and_CAN_reading.ino` sketch.
3. **Upload the Sketch**: Compile and upload the sketch to the Arduino Uno.
4. **Run the System**: Power the Arduino and start the vehicle to begin data transmission. Open the Arduino IDE's serial monitor to view the read CAN data, including frame ID, type, and payload.

## Code Explanation

The sketch initializes the CAN interface, continuously monitors for incoming CAN frames, and prints each frame's details (ID, type, data) to the serial monitor. This is essential for debugging and understanding vehicle-to-device communication.

## Notes

- Ensure the vehicle supports OBD II and the CAN protocol for compatibility.
- The baud rate and pin assignments may need adjustment based on your specific hardware configuration or if using a different Arduino model or CAN shield.


## Documentation

The complete Doxygen-generated documentation for this project can be found at [BoschTestBench Documentation](https://aabdelghani.github.io/boschTestBench/). This documentation provides detailed insights into the structure and functionality of the code, making it easier for developers to understand and contribute to the project.

## Automated Documentation

project uses GitHub Actions to automate the generation of Doxygen documentation. Whenever changes are pushed to the `main` branch, the documentation is automatically updated and deployed to the `gh-pages` branch. This ensures that our documentation is always current and can be easily accessed through our GitHub Pages site.

