/**
 * @file pwm_timer_interrupt.ino
 * @brief PWM Generation using Timer1 with Selectable Frequencies on Arduino
 *
 * This program is designed to generate a PWM (Pulse Width Modulation) signal
 * using Timer1 interrupts on an Arduino. It allows the user to select
 * predefined frequencies for the PWM signal.
 *
 * @author Ahmed Abdelghany
 * @date 1/2/2024
 */

#include <avr/io.h>
#include <avr/interrupt.h>

const int ledPin = 9; ///< PWM output pin, connected to LED.

/**
 * Predefined frequencies for PWM signal.
 * FREQUENCY can be set to any of these.
 */
#define FREQ_1KHZ 1999  ///< Frequency 1kHz (Timer1 compare match value).
#define FREQ_2KHZ 999   ///< Frequency 2kHz (Timer1 compare match value).
#define FREQ_5KHZ 399   ///< Frequency 5kHz (Timer1 compare match value).

#define FREQUENCY 1kHz  ///< Set the desired frequency here.

/**
 * @brief Sets up Timer1 in CTC (Clear Timer on Compare Match) mode.
 *
 * This function initializes Timer1 and sets the compare match register (OCR1A)
 * based on the selected frequency. It also configures the timer interrupt
 * to trigger on compare match.
 */
void setup() {
  pinMode(ledPin, OUTPUT);

  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;

  // Select compare match register value based on predefined frequencies.
  #if FREQUENCY == 1kHz
    OCR1A = FREQ_1KHZ;
  #elif FREQUENCY == 2kHz
    OCR1A = FREQ_2KHZ;
  #elif FREQUENCY == 5kHz
    OCR1A = FREQ_5KHZ;
  #else
    #error "Frequency not defined"
  #endif

  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS11);
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

/**
 * @brief Interrupt Service Routine for Timer1 Compare Match.
 *
 * The ISR toggles the LED pin at each timer compare match,
 * creating the PWM signal.
 */
ISR(TIMER1_COMPA_vect) {
  static bool ledState = false;
  digitalWrite(ledPin, ledState);
  ledState = !ledState;
}

/**
 * @brief Main loop function.
 *
 * This function runs repeatedly after setup function.
 */
void loop() {
  // Empty loop since PWM is handled by Timer interrupt.
}
