/* 
 * Modified for Trinket by MikataHara 
 * 2024.10.19
*/

#include <SoftwareSerial.h>
#include <TinyWireM.h>                  // I2C Master lib for ATTinys which use USI
#define __AVR_ATtiny85__

#include "Adafruit_MCP9808.h"

// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

SoftwareSerial mySerial(3, 1); // RX, TX

void setup() {
  uint8_t i=0;
  mySerial.begin(115200);
  
  // Make sure the sensor is found, you can also pass in a different i2c
  // address with tempsensor.begin(0x19) for example, also can be left in blank for default address use
  // Also there is a table with all addres possible for this sensor, you can connect multiple sensors
  // to the same i2c bus, just configure each sensor with a different address and define multiple objects for that
  //  A2 A1 A0 address
  //  0  0  0   0x18  this is the default address
  //  0  0  1   0x19
  //  0  1  0   0x1A
  //  0  1  1   0x1B
  //  1  0  0   0x1C
  //  1  0  1   0x1D
  //  1  1  0   0x1E
  //  1  1  1   0x1F
  if (!tempsensor.begin(0x18)) {
//    mySerial.println("Couldn't find MCP9808! Check your connections and verify the address is correct.");
    while (1){
      delay(500);
      tempsensor.begin(0x18);
    }
  }

  // sets the resolution mode of reading, the modes are defined in the table bellow:
  // Mode Resolution SampleTime
  //  0    0.5°C       30 ms
  //  1    0.25°C      65 ms
  //  2    0.125°C     130 ms
  //  3    0.0625°C    250 ms
  tempsensor.setResolution(3); 
}

void loop() {
//  mySerial.println("wake up MCP9808.... "); // wake up MCP9808 - power consumption ~200 mikro Ampere
  tempsensor.wake();   // wake up, ready to read!

// Read and print out the temperature, also shows the resolution mode used for reading.
//  mySerial.print("Resolution in mode: ");
//  mySerial.println (tempsensor.getResolution());
  float c = tempsensor.readTempC();
//  float f = tempsensor.readTempF();

  mySerial.print("Temp: "); 
  mySerial.print(c, 4); mySerial.println("*C"); 
//  mySerial.print(f, 4); mySerial.println("*F.");

  delay(1000);
// mySerial.println("Shutdown MCP9808.... ");
  tempsensor.shutdown_wake(1); // shutdown MSP9808 - power consumption ~0.1 mikro Ampere, stops temperature sampling
//  mySerial.println("");
  delay(4000);
}
