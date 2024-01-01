# Arduino PWM Generation Using Timer1 with Selectable Frequencies

## Overview

This Arduino sketch is designed to generate a Pulse Width Modulation (PWM) signal using Timer1 interrupts. It features the ability to select predefined frequencies through preprocessor directives, allowing easy switching between different PWM frequencies. This method provides precise control over PWM signals, which is useful for a variety of applications including LED dimming, motor control, and signal generation.

## Hardware Requirements

- Arduino Uno or similar AVR-based board
- LED
- 220 Ohm resistor
- Breadboard and jumper wires

## Software Requirements

- Arduino IDE for uploading the sketch to the Arduino board

## Configuration

- **PWM Pin**: The sketch uses digital pin 9 on the Arduino for PWM output. This pin is compatible with Timer1.
- **Predefined Frequencies**: Frequencies are predefined as macros and can be selected by changing the `FREQUENCY` definition at the top of the sketch. Current predefined frequencies include 1kHz, 2kHz, and 5kHz.

## How to Use

1. **Connect the Hardware**: Connect the LED and resistor in series between pin 9 and GND on the Arduino.
2. **Set the Desired Frequency**: Open the sketch in the Arduino IDE and set the desired frequency by changing the `#define FREQUENCY` line to one of the predefined frequencies (e.g., `#define FREQUENCY 1kHz`).
3. **Upload the Sketch**: Connect the Arduino to your computer and upload the sketch using the Arduino IDE.
4. **Observe the PWM Signal**: Once uploaded, the connected LED will show the PWM effect at the selected frequency.

## Code Explanation

- **Timer1 Setup**: The sketch configures Timer1 in Clear Timer on Compare Match (CTC) mode. The compare match register (OCR1A) value is set based on the selected frequency. A prescaler of 8 is used to scale down the 16MHz clock.
- **Interrupt Service Routine (ISR)**: The `TIMER1_COMPA_vect` ISR toggles the LED pin at each timer compare match, creating the PWM signal.
- **Frequency Selection**: Use the `#define FREQUENCY` directive to select the PWM frequency. The available options are set using individual `#define` statements for each frequency.
- **Error Handling**: If an undefined frequency is selected, the preprocessor generates a compile-time error.

## Notes

- The frequency values are calculated assuming a 16MHz clock and an 8x prescaler. Adjust these values if using a different clock or prescaler.
- This code is intended for Arduino Uno and similar AVR-based boards. Other boards may require adjustments due to different timer configurations.

## Limitations

- The current setup allows for basic PWM control. For more complex applications, additional modifications might be necessary.
- The use of interrupts and timers may interfere with other time-dependent Arduino functions.

This documentation should provide a clear understanding of how the sketch operates and how to use it for generating PWM signals with selectable frequencies.
