/******************
 * MIDI over Serial Example
 * for RedBear Duo using a modified ardumidi library (included)
 * Sends MIDI messages over the Serial (USB) connection to a laptop
 * Demonstrates note on, note off, and a controller change
 * Bjoern Hartmann for IDD, Fall 2016
 */

#include "ardumidi.h"

// turn off cloud functionality
#if defined(ARDUINO) 
SYSTEM_MODE(MANUAL); 
#endif

int i=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(D7,OUTPUT);
}

void loop() {
  i++;
  if(i%2==0)
    midi_controller_change(1,77,32);
  else
    midi_controller_change(1,77,96);
    
  // put your main code here, to run repeatedly:
  digitalWrite(D7,HIGH);
  midi_note_on(1,MIDI_C,127);
  
  delay(1000);

  digitalWrite(D7,LOW);
  midi_note_off(1,MIDI_C,127);
  delay(1000);


    
  
}
