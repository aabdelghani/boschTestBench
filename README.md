# Arduino PWM Generation Using Timer1 with Selectable Frequencies

# Table of Contents

1. [Overview](#overview)
2. [Hardware Requirements](#hardware-requirements)
3. [Software Requirements](#software-requirements)
4. [Configuration](#configuration)
5. [Frequency and Time Period Details](#frequency-and-time-period-details)
6. [How to Use](#how-to-use)
7. [Code Explanation](#code-explanation)
8. [Notes](#notes)
9. [Side Note: Setting the Compare Match Register for 1kHz Frequency](#side-note-setting-the-compare-match-register-for-1khz-frequency)
	- [Timer and Compare Match Register](#timer-and-compare-match-register)
	- [Setting Up for 1kHz Frequency](#setting-up-for-1khz-frequency)
	- [2kHz Frequency](#2khz-frequency)
	- [5kHz Frequency](#5khz-frequency)
	- [0.5Hz Frequency](#0.5hz-frequency)
	- [What Happens at Runtime](#what-happens-at-runtime)


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

   OCR1A = (Timer Clock Frequency / Desired Interrupt Frequency) - 1

3. **Apply the Formula:** For a 1kHz frequency with a 2MHz timer clock (after prescaling by 8), the calculation would be:

   OCR1A = (2,000,000 / 1,000) - 1 = 1999

   
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

This documentation should provide a clear understanding of how the sketch operates and how to use it for generating PWM signals with selectable frequencies.
