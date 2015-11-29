// 
// 
// 

#include "MotorDriver.h"

MotorDriverClass::MotorDriverClass() : maxTurnRatio(3.0) {

}

void MotorDriverClass::init(int pinStandby, int pinAin1, int pinAin2, int pinPwmA, int pinBin1, int pinBin2, int pinPwmB)
{
	this->pinAin1 = pinAin1;
	this->pinAin2 = pinAin2;
	this->pinBin1 = pinBin1;
	this->pinBin2 = pinBin2;
	this->pinPwmA = pinPwmA;
	this->pinPwmB = pinPwmB;

	this->pinStandby = pinStandby;

	pinMode(this->pinAin1, OUTPUT);
	pinMode(this->pinAin2, OUTPUT);
	pinMode(this->pinBin1, OUTPUT);
	pinMode(this->pinBin2, OUTPUT);
	pinMode(this->pinStandby, OUTPUT);

	digitalWrite(this->pinStandby, LOW); // turn driver off
}

void MotorDriverClass::setDifferentialSpeed(int speed, int turn) {

	if (digitalRead(this->pinStandby) == LOW) {
		digitalWrite(this->pinStandby, HIGH);
	}

	if (speed < 0) {
		digitalWrite(this->pinAin1, LOW);
		digitalWrite(this->pinAin2, HIGH);
		digitalWrite(this->pinBin1, HIGH);
		digitalWrite(this->pinBin2, LOW);
	}
	else if (speed > 0) {
		digitalWrite(this->pinAin1, HIGH);
		digitalWrite(this->pinAin2, LOW);
		digitalWrite(this->pinBin1, LOW);
		digitalWrite(this->pinBin2, HIGH);
	}

	if (speed == 0) {
		analogWrite(this->pinPwmA, 0);
		analogWrite(this->pinPwmB, 0);
	}
	else {
		int mappedSpeed = map(abs(speed), 0, 50, 0, this->maxSpeed);

		if (turn == 0) {
			analogWrite(this->pinPwmA, mappedSpeed);
			analogWrite(this->pinPwmB, mappedSpeed);

			Serial.println(mappedSpeed);
		}
		else {
			int slowerWheel = mappedSpeed * (50 - abs(turn)) / 50;
			
			if (turn < 0) {
				analogWrite(this->pinPwmA, slowerWheel);
				analogWrite(this->pinPwmB, mappedSpeed);
			}
			else {
				analogWrite(this->pinPwmA, mappedSpeed);
				analogWrite(this->pinPwmB, slowerWheel);
			}
		}
	}
}

void MotorDriverClass::setEnabled(bool state) {
	digitalWrite(this->pinStandby, state);
}

MotorDriverClass MotorDriver;

