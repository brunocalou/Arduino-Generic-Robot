#include "controlboard.h"

ControlBoard::ControlBoard(byte r_enable, 
		byte r_motor_1, byte r_motor_2,

		byte l_enable,
		byte l_motor_1, byte l_motor_2,
		
		byte r_vcc_ref, byte r_gnd_ref,
		byte l_vcc_ref, byte l_gnd_ref):

	driver(r_enable, r_motor_1, r_motor_2,
		l_enable, l_motor_1, l_motor_2,
		r_vcc_ref, r_gnd_ref,
		l_vcc_ref, l_gnd_ref)
{
	setPWM(0,0);
	setMinPWM(0,0);
	setCorrection(100,100);
	setCurveFactor(3);
	setSpeed(100);
}

//Automatic control
void ControlBoard::moveForward()
{
	driver.r_motor.setPWM(r_pwm*r_correction*speed,0);
	driver.l_motor.setPWM(l_pwm*l_correction*speed,0);
}
void ControlBoard::moveForwardRight()
{
	driver.r_motor.setPWM(r_pwm*r_correction*speed/curve_factor,0);
	driver.l_motor.setPWM(l_pwm*l_correction*speed,0);
}
void ControlBoard::moveForwardLeft()
{
	driver.r_motor.setPWM(r_pwm*r_correction*speed,0);
	driver.l_motor.setPWM(l_pwm*l_correction*speed/curve_factor,0);
}

void ControlBoard::moveBackwards()
{
	driver.r_motor.setPWM(0, r_pwm*r_correction*speed);
	driver.l_motor.setPWM(0, l_pwm*l_correction*speed);
}

void ControlBoard::moveBackwardsRight()
{
	driver.r_motor.setPWM(0, r_pwm*r_correction*speed/curve_factor);
	driver.l_motor.setPWM(0, l_pwm*l_correction*speed);
}

void ControlBoard::moveBackwardsLeft()
{
	driver.r_motor.setPWM(0, r_pwm*r_correction*speed);
	driver.l_motor.setPWM(0, l_pwm*l_correction*speed/curve_factor);
}

void ControlBoard::rotateClockwise()
{
	driver.r_motor.setPWM(0,r_pwm*r_correction*speed);
	driver.l_motor.setPWM(l_pwm*l_correction*speed,0);
}

void ControlBoard::rotateAntiClockwise()
{
	driver.r_motor.setPWM(r_pwm*r_correction*speed,0);
	driver.l_motor.setPWM(0,l_pwm*l_correction*speed);
}

void ControlBoard::stop()
{
	driver.stop();
}

//Correction
void ControlBoard::setRCorrection(unsigned int correction)
{
	r_correction = correction/100.0;
}

void ControlBoard::setLCorrection(unsigned int correction)
{
	l_correction = correction/100.0;
}

void ControlBoard::setCorrection(unsigned int r_correction, unsigned int l_correction)
{
	/*
	 * The correction is applied to each motor individually.
	 * It is used when the motors have different speeds using 
	 * the same pwm
	 */
	setRCorrection(r_correction);
	setLCorrection(l_correction);
}

void ControlBoard::setRPWM(byte pwm, bool reverse)
{
	if(!reverse)
	{
		driver.r_motor.setPWM(pwm, 0);
	} else {
		driver.r_motor.setPWM(0, pwm);
	}
	r_pwm = pwm;
}

void ControlBoard::setLPWM(byte pwm, bool reverse)
{
	if(!reverse)
	{
		driver.l_motor.setPWM(pwm, 0);
	} else {
		driver.l_motor.setPWM(0, pwm);
	}
	l_pwm = pwm;
}

void ControlBoard::setPWM(byte r_pwm, byte l_pwm, bool r_reverse, bool l_reverse)
{
	/*
	 * Set the pwm manually. Actually, this value is the maximum pwm that the
	 * motor is subjected, considering the speed and the correction variables
	 * in a range of 0 to 1. If the speed and the correction are the default (1)
	 * and the minimum pwm is 0, this method will truly set the pwm
	 */
	setRPWM(r_pwm, r_reverse);
	setLPWM(l_pwm, l_reverse);
}

void ControlBoard::setMinPWM(byte r_min_pwm, byte l_min_pwm)
{
	/*
	 * The minimum pwm is a value used to avoid motor stall
	 * at low pwms. As soon as the pwm is below this value, 
	 * the program will write zero on the motor input
	 */
	driver.r_motor.setMinPWM(r_min_pwm, r_min_pwm);
	driver.l_motor.setMinPWM(l_min_pwm, l_min_pwm);
}
void ControlBoard::setSpeed(unsigned int speed)
{
	/*
	 * Speed as an argument is on the range 0 to 100.
	 * The real speed will be a number between 0 and 1 and
	 * it will multiply all the pwms
	 */

    if(speed > 100) {speed = 100;}
	this->speed = speed/100.0;
}

void ControlBoard::setCurveFactor(byte factor)
{
	/*
	 * The curve factor is a number that multiplies the PWM of a motor
	 * when the methods moveForwardRight, moveForwardLeft, moveBackwardsRight
	 * and moveBackwardsLeft are called. E.g, when the robot turns right using
	 * the method moveForwardRight, the left motor rotates X times faster then
	 * the right motor. This X is the factor and it must be greater than 1
	 */

	if(factor == 0)
	{
		factor = 255;
	}
	curve_factor = factor;
}