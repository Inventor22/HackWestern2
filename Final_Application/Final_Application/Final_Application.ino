#include <Servo.h>
#include "MotorDriver.h"
#include <Wire.h>
#include "rgb_lcd.h"
#include <SoftwareSerial.h>
#include <MyoController.h>

SoftwareSerial ss(2, 3); // rx, tx

MyoController myo = MyoController(ss);

rgb_lcd lcd;

uint32_t tNow, tPrev;

Servo hammer;
const int pinHammer = 6;

void setup() {
	Serial.begin(115200);
	Serial.println("MyoKart");
	// standby, Ain1, Ain2, Apwm, Bin1, Bin2, Bpwm
	MotorDriver.init(4, 5, 12, 10, 7, 8, 11);

	MotorDriver.setDifferentialSpeed(20, 0);

	delay(3000);

	MotorDriver.setEnabled(false);

	hammer.attach(pinHammer);

	myo.initMyo();

	lcd.begin(16, 2);
	lcd.print("set color");
	lcd.setRGB(110, 0, 110);

	printMyoData();
	//Serial.println("init myo");
	tNow = tPrev = millis();
}

void printMyoData() {
	lcd.clear();
	lcd.print("R:");
	lcd.print(myo.roll);
	lcd.print(" P:");
	lcd.print(myo.pitch);
	lcd.print(" H:");
	lcd.print(myo.throwHammer);
}

void loop()
{
	if (myo.updateData()) {
		printMyoData();

		MotorDriver.setDifferentialSpeed(myo.pitch, myo.roll);
	}
}


