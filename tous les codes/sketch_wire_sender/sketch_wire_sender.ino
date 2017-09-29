// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
}

byte hello[10] = {1,2,3,4,5,6,7,8,9,1};

void loop() {
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(hello,10);
  Wire.endTransmission();    // stop transmitting
  delay(200);
  hello[8]++;
  hello[8]%=10;
  
}
