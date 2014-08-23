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

	setPWM(0,0);
	setMinPWM(0,0);

	setDigitalPin(this->enable, OUTPUT, HIGH);
	setDigitalPin(this->vcc_ref, OUTPUT, HIGH);
	setDigitalPin(this->gnd_ref, OUTPUT, LOW);
}

void SimpleDriver::setPWM1(byte pwm)
{
	pwm_1 = pwm;
	update();
}

void SimpleDriver::setPWM2(byte pwm)
{
	pwm_2 = pwm;
	update();
}

void SimpleDriver::setPWM(byte pwm_1, byte pwm_2)
{
	this->pwm_1 = pwm_1;
	this->pwm_2 = pwm_2;
	update();
}

void SimpleDriver::setMinPWM(byte pwm_1, byte pwm_2)
{
	this->pwm_min_1 = pwm_1;
	this->pwm_min_2 = pwm_2;
}
void SimpleDriver::setEnable(bool state)
{
	if(enable != UNUSED)
	{
		digitalWrite(enable, state);
	}
}

void SimpleDriver::stop()
{
	setPWM(0,0);
}

void SimpleDriver::update()
{
	byte current_pwm_1 = pwm_1;
	byte current_pwm_2 = pwm_2;

	if(pwm_1 <= pwm_min_1)
	{
		current_pwm_1 = 0;
	}

	if(pwm_2 <= pwm_min_2)
	{
		current_pwm_2 = 0;
	}

	analogWrite(input_1, current_pwm_1);
	analogWrite(input_2, current_pwm_2);
	
}

void SimpleDriver::setDigitalPin(byte pin, bool mode, bool state)
{
	if(pin != UNUSED)
	{
		pinMode(pin, mode);
		digitalWrite(pin, state);
	}
}