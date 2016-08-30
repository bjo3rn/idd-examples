
// Sensor graphing sketch
// This program takes ASCII-encoded strings
// from the serial port at 9600 baud and graphs them. It expects float values in the
// range of -1.0 to 1.0, followed by a newline, or newline and carriage return

// Created 20 Apr 2005
// Updated 18 Jan 2008 by Tom Igoe
// Adapted 16 Sep 2014 by Bjoern Hartmann for mbed
// This example code is in the public domain.

import processing.serial.*;
import java.util.Scanner;

Serial myPort;        // The serial port
int xPos = 1;         // horizontal position of the graph

void setup () {
  // set the window size:
  size(400, 300);        

  // List all the available serial ports to help you find the one you need
  println(Serial.list());
  // Open whatever port is the one you're using.
  myPort = new Serial(this, "/dev/tty.usbmodem1412", 9600);
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
  // set inital background:
  background(236,240,241);
}
void draw () {
  // everything happens in the serialEvent()
}

void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  if (inString != null) {
    Scanner scanner = new Scanner(inString);
    
    // trim off any whitespace:
    inString = trim(inString);
    // convert to an int and map to the screen height:
    float inFloat =0.f;
    try{
     inFloat = scanner.nextFloat();//float(inString);
    } catch (Exception e) {
      print(e);
    }
    
    float screenY = map(inFloat, -1.0, 1.0, 0, height);

    // draw the line from bottom of screen to desired height
    stroke(61,126,155);
    line(xPos, height, xPos, height - screenY);

    // at the edge of the screen, go back to the beginning:
    if (xPos >= width) {
      xPos = 0;
      background(236,240,241);
    } else {
      // increment the horizontal position:
      xPos++;
    }
  }
}


