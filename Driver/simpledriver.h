/*
	1 DC motor based driver
*/
#ifndef SIMPLEDRIVER_H
#define SIMPLEDRIVER_H

#include <inttypes.h>
#include <Arduino.h>

#define UNUSED	255

class SimpleDriver
{

public:
	SimpleDriver(byte enable,
		byte input_1, byte input_2,
		byte vcc_ref = UNUSED, byte gnd_ref = UNUSED);

	bool setPWM1(byte pwm);
	bool setPWM2(byte pwm);
	bool setPWM(byte pwm_1, byte pwm_2);
	void setMinPWM(byte pwm_1, byte pwm_2);
	void setEnable(bool state);
	bool stop();

private:

	//Pins
	byte enable;
	byte input_1, input_2;		
	byte vcc_ref, gnd_ref;

	byte pwm_1, pwm_2;
	byte pwm_min_1, pwm_min_2;

	void setDigitalPin(byte pin, bool mode, bool state);
};

#endif
