/* Graph I2C Accelerometer On RedBear Duo over Serial Port
 * Adafruit Part 2809 LIS3DH - http://adafru.it/2809
 * This example shows how to program I2C manually
 * I2C Pins SDA1==D0, SCL1 == D1
 * Default address: 0x18
 */
 
// do not use the cloud functions - assume programming through Arduino IDE
#if defined(ARDUINO) 
SYSTEM_MODE(MANUAL); 
#endif
// Basic demo for accelerometer readings from Adafruit LIS3DH

#include "Adafruit_LIS3DH.h"
#include "Adafruit_Sensor.h"

// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();


void setup(void) {
  
  Serial.begin(9600);
  
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    //couldn't start
    while (1);
  }
  lis.setRange(LIS3DH_RANGE_2_G);   // 2, 4, 8 or 16 G!
}

void loop() {
  
  /* Or....get a new sensor event, normalized */ 
  sensors_event_t event; 
  lis.getEvent(&event);
  
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print(event.acceleration.x/(9.8*2));
  Serial.print(" "); 
  Serial.print(event.acceleration.y/(9.8*2)); 
  Serial.print(" "); 
  Serial.print(event.acceleration.z/(9.8*2)); 
  Serial.println();
 
  delay(33); //33Hz update rate
}


