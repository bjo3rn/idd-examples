/*
 Serial Print Example for RedBear Duo
 Print a string character-by-character whenever a button is pressed.

 Bjoern Hartmann, 9/6/2016
 
 This example code is in the public domain.
 */

// do not use the cloud functions - assume programming through Arduino IDE
#if defined(ARDUINO) 
SYSTEM_MODE(MANUAL); 
#endif

const int buttonPin = D0;    // the number of the pushbutton pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 10;    // the debounce time; increase if the output flickers

String helloString = "Hello, World!"; // String to print 
int stringPos = 0; // current position in the string

void setup() {
  pinMode(buttonPin, INPUT_PULLDOWN); //connect buttonPin through switch to 3.3V
  Serial1.begin(9600);
}

void loop() {
  Serial1.print(1);
  delay(100);
  
}

