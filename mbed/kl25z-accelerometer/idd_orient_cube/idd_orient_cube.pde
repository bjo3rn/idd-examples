// Cube Orientation
// orient a 3D cube based on accelerometer data received from KL25Z over serial


// This program takes ASCII-encoded strings containing floating point numbers
// from the serial port at 9600 baud and graphs them. It expects values in the
// range -1.0g to 1.0g in the format "1.00 1.00 1.00", followed by a newline, or newline and carriage return

// Created 20 Apr 2005
// Updated 18 Jan 2008 by Tom Igoe
// Adapted 16 Sep 2014 by Bjoern Hartmann for mbed
// This example code is in the public domain.

import processing.serial.*;
import java.util.Scanner;

Serial myPort;        // The serial port
int xPos = 1;         // horizontal position of the graph
float xAcc=0.0,yAcc=0.0,zAcc=0.0;
float minVal=-1.0;
float maxVal=1.0;

void setup () {
  // set the window size:
  size(400, 300, P3D);        

  // List all the available serial ports
  println(Serial.list());
  // Open whatever port is the one you're using.
  myPort = new Serial(this, "/dev/tty.usbmodem1412", 9600);
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
  // set inital background:
  background(0);
}

//draw the 3d scene
void draw () {
  //http://stackoverflow.com/questions/3755059/3d-accelerometer-calculate-the-orientation
  float roll =(float) Math.atan2(yAcc, zAcc);// * 180.f/PI;
  float pitch = (float) Math.atan2(xAcc, Math.sqrt(yAcc*yAcc + zAcc*zAcc));// * 180.f/PI;
  background(0);
  lights();
  fill(128);
  stroke(255);
  translate(width/2.0, height/2.0); 
  
  rotateX(-1.0*pitch);
  rotateZ(roll);  
  box(200,20,100);
}

//parse a line of data that arrived
void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');
  
  if (inString != null) {
    //use the Scanner class to parse 3 floats on a line.
    Scanner scanner = new Scanner(inString);
    
    try{
      xAcc = constrain(scanner.nextFloat(),-1.0, 1.0);
      yAcc = constrain(scanner.nextFloat(), -1.0, 1.0);
      zAcc = constrain(scanner.nextFloat(), -1.0, 1.0);
      
    } catch (Exception e) {     
      print(e); //InputMismatchException
    } 
  }
}
