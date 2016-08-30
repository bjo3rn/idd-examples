/*
 Pushbutton interrupt example with debouncing
 for RedBear Duo with internal pull-down resistor.

 
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
void isr(void);


long debounceDelay = 50;    // the debounce time in ms
volatile int state = LOW;

Timer timer(debounceDelay, toggle, true); // oneshot

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(button, INPUT_PULLDOWN);
  attachInterrupt(button, isr, CHANGE); //CHANGE, RISING or FALLING  
}

void loop()
{
  ;
}

void toggle() {
  if(digitalRead(button)==HIGH){
    state=!state;
    digitalWrite(LED,state);
  }
  //timer.stop(); // not needed for one-shot timer
}

void isr()
{ 
  noInterrupts();
  if(digitalRead(button)==HIGH){
    timer.resetFromISR(); //start or reset timer on every rising edge
  } else {
    timer.stopFromISR(); //stop on falling edge
  } 
  interrupts();
 
}

