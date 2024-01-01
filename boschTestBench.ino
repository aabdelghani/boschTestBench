#include <avr/io.h>
#include <avr/interrupt.h>

const int ledPin = 9; // Use a pin compatible with Timer1
int dutyCycle = 128; // Set this value between 0 (0%) and 255 (100%) to control the duty cycle

void setup() {
  pinMode(ledPin, OUTPUT);

  // Set up Timer1
  noInterrupts();           // Disable all interrupts
  TCCR1A = 0;               // Set entire TCCR1A register to 0
  TCCR1B = 0;               // Same for TCCR1B

  // Set compare match register to desired timer count for 1kHz frequency
  OCR1A = 1999;             // = 16000000 / (8 * 1000) - 1

  TCCR1B |= (1 << WGM12);   // Turn on CTC mode
  TCCR1B |= (1 << CS11);    // Set CS11 bit for 8 prescaler
  TIMSK1 |= (1 << OCIE1A);  // Enable timer compare interrupt
  interrupts();             // Enable all interrupts
}

ISR(TIMER1_COMPA_vect) {
  static int dutyCycleCounter = 0;

  dutyCycleCounter++;
  if (dutyCycleCounter >= 1000) {
    dutyCycleCounter = 0;
  }

  if (dutyCycleCounter < dutyCycle) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

void loop() {
  // Nothing needed here
}
