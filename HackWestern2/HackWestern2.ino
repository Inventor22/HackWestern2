#include <Wire.h>
#include <rgb_lcd.h>
#include <Stepper.h>
#include <Servo.h>
#include <SoftwareSerial.h>

const int stepperIn1 = 9;
const int stepperIn2 = 10;
const int stepperIn3 = 11;
const int stepperIn4 = 12;

const int pinKillSwitch = 3;
const int pinPot = A5;

SoftwareSerial ss(2, 3); // rx, tx
rgb_lcd lcd;

const int stepsPerRev = 64 * 31.1;
Stepper stepper(stepsPerRev, 9, 11, 10, 12);


void setup()
{
  Serial.begin(115200);
  ss.begin(9600);

  lcd.begin(16, 2);
  lcd.setRGB(110, 0, 110);

  stepper.setSpeed(10); // rpm
}

void loop()
{

}

void serialEvent() {
  if (Serial.available() >= 3) {
    byte cmd = Serial.read();
    byte speed = Serial.read();
    byte terminator = Serial.read();

    if (terminator == '!') {
      switch (cmd) {
        case 'F':

        case 'B':
        case 'L':
        case 'R':
        case 'H':
      }
    }
  }
}
