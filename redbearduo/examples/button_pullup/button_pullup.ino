/*
 Pushbutton example for RedBear Duo with internal pull-up resistor.
 
 Blink an LED as long as a button is pressed.
 Adapted from the Particle Photon documentation.
 modified 29 Aug 2016
 by Bjoern Hartmann for RedBear Duo

 The circuit:
 * internal LED on D7
 * pushbutton connected to D0 and GND
 
 */

#if defined(ARDUINO) 
SYSTEM_MODE(MANUAL); 
#endif

// PIN EXAMPLE
// EXAMPLE USAGE
int button = D0;                      // button is connected to D0  and GND
int LED = D7;                         // internal LED is connected to D7

void setup()
{
  pinMode(LED, OUTPUT);               // sets pin as output
  pinMode(button, INPUT_PULLUP);    // sets pin as input
}

void loop()
{
  // blink the LED as long as the button is pressed
  while(digitalRead(button) == LOW) {
    digitalWrite(LED, HIGH);          // sets the LED on
    delay(50);                       // waits for 200mS
    digitalWrite(LED, LOW);           // sets the LED off
    delay(50);                       // waits for 200mS
  }
}
