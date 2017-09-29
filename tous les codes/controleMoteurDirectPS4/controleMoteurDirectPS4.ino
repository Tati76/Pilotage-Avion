/*
 Example sketch for the PS4 USB library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <PS4USB.h>
#include <Servo.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
PS4USB PS4(&Usb);

bool printAngle, printTouch;

int value, valeurPS4;
Servo esc1;

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 USB Library Started"));
  esc1.attach(2);
}

void loop() {
  Usb.Task();

  if (PS4.connected()) {
    valeurPS4 = PS4.getAnalogButton(R2);
    value = map(valeurPS4,0,255,400,2400);
    
    value = pow(2.71828182846,valeurPS4*0.02548051)+2.5*valeurPS4+699;

    esc1.writeMicroseconds(value);

    Serial.println(value);

    
  }
}
