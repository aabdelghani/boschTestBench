#include <avr/io.h>
#include <avr/interrupt.h>

const int ledPin = 9; // Use a pin compatible with Timer1

// Define your desired frequency here
#define FREQUENCY 1kHz

// Predefined frequencies
#define FREQ_1KHZ 1999  // For 1kHz
#define FREQ_2KHZ 999   // For 2kHz
#define FREQ_5KHZ 399   // For 5kHz
// Add more frequencies as needed

void setup() {
  pinMode(ledPin, OUTPUT);

  // Set up Timer1
  noInterrupts();           // Disable all interrupts
  TCCR1A = 0;               // Set entire TCCR1A register to 0
  TCCR1B = 0;               // Same for TCCR1B

  // Set compare match register based on the chosen frequency
  #if FREQUENCY == 1kHz
    OCR1A = FREQ_1KHZ;
  #elif FREQUENCY == 2kHz
    OCR1A = FREQ_2KHZ;
  #elif FREQUENCY == 5kHz
    OCR1A = FREQ_5KHZ;
  // Add more cases as needed
  #else
    #error "Frequency not defined"
  #endif

  TCCR1B |= (1 << WGM12);   // Turn on CTC mode
  TCCR1B |= (1 << CS11);    // Set CS11 bit for 8 prescaler
  TIMSK1 |= (1 << OCIE1A);  // Enable timer compare interrupt
  interrupts();             // Enable all interrupts
}

ISR(TIMER1_COMPA_vect) {
  // ISR code remains the same
}

void loop() {
  // Nothing needed here
}
