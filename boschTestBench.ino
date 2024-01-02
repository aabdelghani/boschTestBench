/**
 * @file pwm_timer_interrupt.ino
 * @brief Generate PWM using Timer1 with Selectable Frequencies on Arduino
 *
 * This program generates a PWM (Pulse Width Modulation) signal
 * using Timer1 interrupts on an Arduino. The user can select
 * from predefined frequencies for the PWM signal.
 *
 * @author Ahmed Abdelghany
 * @date 1/2/2024
 */

#include <avr/io.h>
#include <avr/interrupt.h>

const int ledPin = 9; ///< PWM output pin, typically connected to an LED.

/**
 * Predefined frequencies for the PWM signal.
 * FREQUENCY should be set to one of these values.
 */
#define FREQ_1KHZ 1999  ///< 1kHz frequency (Timer1 compare match value).
#define FREQ_2KHZ 999   ///< 2kHz frequency (Timer1 compare match value).
#define FREQ_5KHZ 399   ///< 5kHz frequency (Timer1 compare match value).
#define FREQ_0_5HZ 19999  ///< 0.5Hz frequency (2-second interval) (Timer1 compare match value).

#define FREQUENCY FREQ_0_5HZ  ///< Set the desired frequency here.

/**
 * @brief Initialize Timer1 in CTC (Clear Timer on Compare Match) mode.
 *
 * This function sets up Timer1, configuring the compare match register (OCR1A)
 * based on the selected frequency. It also enables timer interrupts
 * to trigger on compare match.
 */
void setup() {
  pinMode(ledPin, OUTPUT);

  noInterrupts();
  TCCR1A = 0; // Clear Timer1 Control Registers
  TCCR1B = 0;

  // Set compare match register value and prescaler based on the predefined frequency.
  #if FREQUENCY == FREQ_1KHZ
    OCR1A = FREQ_1KHZ;
    TCCR1B |= (1 << CS12); // Prescaler 256 for 1 ms resolution.
  #elif FREQUENCY == FREQ_2KHZ
    OCR1A = FREQ_2KHZ;
    TCCR1B |= (1 << CS12); // Prescaler 256 for 0.5 ms resolution.
  #elif FREQUENCY == FREQ_5KHZ
    OCR1A = FREQ_5KHZ;
    TCCR1B |= (1 << CS12); // Prescaler 256 for 0.2 ms resolution.
  #elif FREQUENCY == FREQ_0_5HZ
    OCR1A = FREQ_0_5HZ;
    TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler 1024 for 2-second resolution.
  #else
    #error "Frequency not defined"
  #endif

  TCCR1B |= (1 << WGM12); // Configure for CTC mode.
  TIMSK1 |= (1 << OCIE1A); // Enable Timer1 compare match interrupt.
  interrupts(); // Enable global interrupts.
}

/**
 * @brief Interrupt Service Routine for Timer1 Compare Match.
 *
 * This ISR toggles the state of the LED pin on each Timer1 compare match,
 * effectively creating the PWM signal.
 */
ISR(TIMER1_COMPA_vect) {
  static bool ledState = false;
  digitalWrite(ledPin, ledState);
  ledState = !ledState;
}

/**
 * @brief Main loop function.
 *
 * The loop function is empty as PWM generation is handled entirely by the Timer interrupt.
 */
void loop() {
  // Empty loop since PWM is handled by Timer interrupt.
}
