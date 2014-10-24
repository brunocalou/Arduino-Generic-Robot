#include "simpledriver.h"

SimpleDriver::SimpleDriver(
		byte enable,
		byte input_1, byte input_2,
		byte vcc_ref, byte gnd_ref)
{
	this->enable = enable;
	this->input_1 = input_1;
	this->input_2 = input_2;
	this->vcc_ref = vcc_ref;
	this->gnd_ref = gnd_ref;

	pwm_1 = 0;
	pwm_2 = 0;
	setMinPWM(0,0);

	setDigitalPin(this->enable, OUTPUT, HIGH);
	setDigitalPin(this->vcc_ref, OUTPUT, HIGH);
	setDigitalPin(this->gnd_ref, OUTPUT, LOW);
}

bool SimpleDriver::setPWM1(byte pwm)
{
	return setPWM(pwm, this->pwm_2);
}

bool SimpleDriver::setPWM2(byte pwm)
{
	return setPWM(this->pwm_1, pwm);
}

bool SimpleDriver::setPWM(byte pwm_1, byte pwm_2)
{
	/* If the pwm given is shorter than the minimum pwm
	 * this method will clamp it to 0
	 */

	if(pwm_1 <= pwm_min_1)
	{
		pwm_1 = 0;
	}

	if(pwm_2 <= pwm_min_2)
	{
		pwm_2 = 0;
	}

	if(pwm_1 == 0)
	{
		/* Writes the low level first to avoid short circuit */
		analogWrite(input_1, pwm_1);
		analogWrite(input_2, pwm_2);

	} else if(pwm_2 == 0){

		/* Writes the low level first to avoid short circuit */
		analogWrite(input_2, pwm_2);
		analogWrite(input_1, pwm_1);
	} else {
		
		/* If both are non-zero pwms, a short circuit will occur! */
		return 0;
	}
	
	/* If both pwms are valid, update them */
	this->pwm_1 = pwm_1;
	this->pwm_2 = pwm_2;

	return 1;
}

void SimpleDriver::setMinPWM(byte pwm_1, byte pwm_2)
{
	this->pwm_min_1 = pwm_1;
	this->pwm_min_2 = pwm_2;
	
	//Updates the pwms
	setPWM(this->pwm_1, this->pwm_2);
}

void SimpleDriver::setEnable(bool state)
{
	if(enable != UNUSED)
	{
		digitalWrite(enable, state);
	}
}

bool SimpleDriver::stop()
{
	return setPWM(0,0);
}

void SimpleDriver::setDigitalPin(byte pin, bool mode, bool state)
{
	if(pin != UNUSED)
	{
		pinMode(pin, mode);
		digitalWrite(pin, state);
	}
}