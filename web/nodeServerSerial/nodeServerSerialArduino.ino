/*
  Arduino code:
  Example of sending and receiving data via serial to a web server.
  Works with node.js examples nodeSerialServer and nodeSerialServerSocket
*/

const int analogInPin = A0; 
int outputValue = 0;
int sensorValue = 0;

void setup()
{
  pinMode(13,OUTPUT); //set internal LED pin to output
  Serial.begin(57600);
  while (!Serial) {;}
}

void loop()
{
  // read the analog in value
  // send it out the serial port as ASCII encoded line if it changed
  sensorValue = analogRead(analogInPin);            
  if(sensorValue!=outputValue) {
    outputValue=sensorValue;
    Serial.println(outputValue,DEC);
  }

  // if data came in, read it and set the LED
  // expects ascii-encoded '0' or '1'
  while (Serial.available() > 0) {    
    // read the incoming byte:
    byte incomingByte = Serial.read();
    if(incomingByte=='1')
      digitalWrite(13,HIGH);
    else if(incomingByte=='0')
      digitalWrite(13,LOW);
  } 
  
  //wait 10ms
  delay(10);
}