
// do not use the cloud functions - assume programming through Arduino IDE
#if defined(ARDUINO) 
SYSTEM_MODE(MANUAL); 
#endif

int analogPin = A0;
float val;
void setup() {
  Serial.begin(9600);
}

void loop()
{
    // read analog value and convert units to Volts
    // note: floating point on a microcontroller is inefficient!
    val = (analogRead(analogPin)/4096.0)*1.0; //use 3.3 to report in Volts
    Serial.printf("%1.2f\n", val); //print ascii-encoded float to serial port
    delay(50); // wait 50ms (20Hz update rate)
}
 
/*
// Graphing sketch for Processing
 
 
// This program takes ASCII-encoded strings containing floating point numbers
// from the serial port at 9600 baud and graphs them. It expects values in the
// range 0.0 to 3.3, followed by a newline, or newline and carriage return
 
// Created 20 Apr 2005
// Updated 18 Jan 2008 by Tom Igoe
// Adapted 16 Sep 2014 by Bjoern Hartmann for mbed
// Adapted 06 Sep 2016 by Bjoern Hartmann for RedBear Duo
// This example code is in the public domain.
 
import processing.serial.*;
 
Serial myPort;        // The serial port
int xPos = 1;         // horizontal position of the graph
 
float minVal=0.0;
float maxVal=3.3;
 
void setup () {
  // set the window size:
  size(400, 300);        
 
  // List all the available serial ports
  println(Serial.list());
  // Open whatever port is the one you're using.
  myPort = new Serial(this, "/dev/cu.usbmodem1421", 9600);
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
  // set inital background:
  background(0);
}
void draw () {
  // everything happens in the serialEvent()
}
 
void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');
 
  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);
    // convert to an int and map to the screen height:
    float inFloat = float(inString); 
    float screenY = map(inFloat, minVal, maxVal, 0, height);
 
    // draw the line from bottom of screen to desired height
    stroke(127, 34, 255);
    line(xPos, height, xPos, height - screenY);
 
    // at the edge of the screen, go back to the beginning:
    if (xPos >= width) {
      xPos = 0;
      background(0);
    } else {
      // increment the horizontal position:
      xPos++;
    }
  }
}
*/
