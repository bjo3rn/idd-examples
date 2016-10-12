/***
 * IDD Bluetooth LE Example: Toggle the on-board LED with a one-byte characterisic.
 */
 
/* Original Code:
 * Copyright (c) 2016 RedBear
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 */
 
#if defined(ARDUINO) 
SYSTEM_MODE(SEMI_MANUAL); 
#endif

#include "ble_config.h"

#define CHARACTERISTIC1_MAX_LEN    1
#define DIGITAL_OUT_PIN            D7

/* UUIDS FOR CUSTOM SERVICE AND CHARACTERISTIC */
static uint8_t service1_uuid[16]    = { 0x71,0x3d,0x00,0x00,0x50,0x3e,0x4c,0x75,0xba,0x94,0x31,0x48,0xf1,0x8d,0x94,0x1e };
static uint8_t characteristic1_uuid[16] = { 0x71,0x3d,0x00,0x03,0x50,0x3e,0x4c,0x75,0xba,0x94,0x31,0x48,0xf1,0x8d,0x94,0x1e };

static uint16_t character1_handle = 0x0000;
static uint8_t characteristic1_data[CHARACTERISTIC1_MAX_LEN] = { 0x01 };


/**
 * @brief Callback for writing event.
 *
 * @param[in]  value_handle  
 * @param[in]  *buffer       The buffer pointer of writting data.
 * @param[in]  size          The length of writting data.   
 *
 * @retval 
 */
int bleWriteCallback(uint16_t value_handle, uint8_t *buffer, uint16_t size) {
  Serial.print("Write value handler: ");
  Serial.println(value_handle, HEX);

  //always check if the write is actually for you - could be for some other characteristic
  if (character1_handle == value_handle) {
    memcpy(characteristic1_data, buffer, CHARACTERISTIC1_MAX_LEN);
    Serial.print("Characteristic1 write value: ");
    Serial.println(characteristic1_data[0], HEX);
    //Process the data
    if (characteristic1_data[0] == 0x01) { // Command is to control digital out pin
        digitalWrite(DIGITAL_OUT_PIN, HIGH);
    }  else {
        digitalWrite(DIGITAL_OUT_PIN, LOW);
    }
  } else {
    //received a write that's not for characteristic1, we don't know what to do with it
  }
  return 0;
}


/**
 * @brief Setup.
 */
void setup() {
  WiFi.off();
  Serial.begin(115200);
  delay(5000);
  Serial.println("ble_led demo.");
  
  ble.init(); // Initialize ble_stack.
  configureBLE(); //lots of standard initialization hidden in here - see ble_config tabs
  
  // Add our custom service and characteristic
  ble.onDataWriteCallback(bleWriteCallback);
  ble.addService(service1_uuid);
  character1_handle = ble.addCharacteristicDynamic(characteristic1_uuid, ATT_PROPERTY_NOTIFY|ATT_PROPERTY_WRITE|ATT_PROPERTY_WRITE_WITHOUT_RESPONSE, characteristic1_data, CHARACTERISTIC1_MAX_LEN);

  
  // BLE peripheral starts advertising now.
  ble.startAdvertising();
  Serial.println("BLE start advertising.");

  // Initialize all peripheral.
  pinMode(DIGITAL_OUT_PIN, OUTPUT);
  
}

/**
 * @brief Loop.
 */
void loop() {
    
}
