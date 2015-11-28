#include <Stepper.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

const int stepperIn1 = 9;
const int stepperIn2 = 10;
const int stepperIn3 = 11;
const int stepperIn4 = 12;

const int pinKillSwitch = 3;
const int pinPot = A5;

SoftwareSerial ss(2, 3); // rx, tx
LiquidCrystal lcd();


void setup()
{
	Serial.begin(115200);
	ss.begin(9600);

}

void loop()
{
	
}
