// Sensor graphing sketch with threshold
// This program takes ASCII-encoded strings
// from the serial port at 9600 baud and graphs them. It expects float values in the
// range of -1.0 to 1.0, followed by a newline, or newline and carriage return

// based on Tom Igoe's Arduino sensor graphing sketch, created 20 Apr 2005
// Adapted 16 Sep 2014 by Bjoern Hartmann for mbed
// This example code is in the public domain.

import processing.serial.*;
import java.util.Scanner;

Serial myPort;        // The serial port
int xPos = 1;         // horizontal position of the graph
float threshold=0.0;
float tWidth=0.1;
boolean below = true;
boolean smooth = false;

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
  redrawThreshold();
}

void draw () {
  // everything happens in the serialEvent()
}

//keyboard control UP/DOWN - move threshold; LEFT/RIGHT - split double threshold
void keyPressed() {
if (key == CODED) {
    if (keyCode == UP) {
      threshold+=0.05;
    } else if (keyCode == DOWN) {
      threshold-=0.05;
    } else if (keyCode == LEFT) {
      tWidth= constrain(tWidth-0.01,0.0,1.0);
    } else if (keyCode == RIGHT) {
      tWidth= constrain(tWidth+0.01,0.0,1.0);
    }
    redrawThreshold();  
  } else {
    if(key=='s') {
      smooth=!smooth;
    }
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
    // choose color based on side of threshold we're on
    if(below) { //we were last below      
      if(inFloat>threshold+tWidth/2.0) {
        stroke(231,76,70);
        below=false;
      } else {
        // in hysteresis zone - stay below
        stroke(61,126,155);
      }
    } else { //above
      if(inFloat<threshold-tWidth/2.0) {
        stroke(61,126,155); //change state
        below=true;
      } else {
        stroke(231,76,70); //stay above
      }
    }
    
    line(xPos, height, xPos, height - screenY);

    // at the edge of the screen, go back to the beginning:
    if (xPos >= width) {
      xPos = 0;
      redrawThreshold();
    } else {
      // increment the horizontal position:
      xPos++;
    }
  }
}

void redrawThreshold() {
      background(236,240,241);
      stroke(52,73,94);
      float ty = height-map(threshold-tWidth/2.0,-1.0,1.0,0,height);
      line(0,ty,width,ty);
      ty = height-map(threshold+tWidth/2.0,-1.0,1.0,0,height);
      line(0,ty,width,ty);
}
