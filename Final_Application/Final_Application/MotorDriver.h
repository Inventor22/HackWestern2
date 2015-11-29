// MotorDriver.h

#ifndef _MOTORDRIVER_h
#define _MOTORDRIVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MotorDriverClass
{
private:
	static const int maxSpeed = 255;
	float maxTurnRatio;

 protected:
	 int pinStandby;
	 int pinAin1;
	 int pinAin2;
	 int pinBin1;
	 int pinBin2;

	 int pinPwmA;
	 int pinPwmB;

 public:
	 MotorDriverClass();

	 void init(int pinStandby, int pinAin1, int pinAin2, int pinPwmA, int pinBin1, int pinBin2, int pinPwmB);

	 void setDifferentialSpeed(int speed, int turn);

	 void setEnabled(bool state);
};

extern MotorDriverClass MotorDriver;

#endif

