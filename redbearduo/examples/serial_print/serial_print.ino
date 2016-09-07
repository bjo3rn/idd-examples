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
  Serial.begin(9600);
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // print the next character of our string if the button went HIGH (was pressed)
      if (buttonState == HIGH) {
        Serial.print(helloString.charAt(stringPos));
        stringPos++;
        if (stringPos >= helloString.length()) {
          stringPos=0;
        }
        
      }
    }
  }

  // save the reading.
  lastButtonState = reading;
}

