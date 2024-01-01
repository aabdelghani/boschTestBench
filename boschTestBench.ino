// Define the LED pin
const int ledPin = 9; // PWM pin

void setup() {
  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Gradually increase the brightness
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    // Change the PWM duty cycle
    analogWrite(ledPin, dutyCycle);   
    
    // Wait for 10 milliseconds
    delay(10);
  }

  // Gradually decrease the brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){   
    // Change the PWM duty cycle
    analogWrite(ledPin, dutyCycle);
    
    // Wait for 10 milliseconds
    delay(10);
  }
}
