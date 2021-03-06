/*
 Pushbutton interrupt example for RedBear Duo with internal pull-down resistor.

 While this works for the simple case of an internal LED, 
 note that switches are not debounced in this example.
 
 Blink an LED as long as a button is pressed.
 Adapted from the Particle Photon documentation.
 modified 29 Aug 2016
 by Bjoern Hartmann for RedBear Duo
 
 The circuit:
 * internal LED on D7
 * pushbutton connected to D1 and 3V3
 
 see https://docs.particle.io/reference/firmware/photon/#attachinterrupt-
 */

// do not use the cloud functions - assume programming through Arduino IDE
#if defined(ARDUINO) 
SYSTEM_MODE(MANUAL); 
#endif

// note: Particle documentation states external interrupts
// DO NOT work on D0 and A5, so we choose D1 instead
const int button = D1;                      // button is connected to D1 and 3V3
const int LED = D7;                         // LED is connected to D7

void toggle(void);

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(button, INPUT_PULLDOWN);
  attachInterrupt(button, toggle, CHANGE); //CHANGE, RISING or FALLING
  
}

void loop()
{
  ;
}

void toggle()
{
  digitalWrite(LED, digitalRead(button));
}

