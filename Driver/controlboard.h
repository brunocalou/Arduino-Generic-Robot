#ifndef CONTROLBOARD_H
#define CONTROLBOARD_H

#include "duodriver.h"

class ControlBoard
{
public:
	ControlBoard(byte r_enable, 
		byte r_motor_1, byte r_motor_2,

		byte l_enable,
		byte l_motor_1, byte l_motor_2,
		
		byte r_vcc_ref=UNUSED, byte r_gnd_ref=UNUSED,
		byte l_vcc_ref=UNUSED, byte l_gnd_ref=UNUSED);

	//Automatic control
	virtual void moveForward();
	virtual void moveForwardRight();
	virtual void moveForwardLeft();

	virtual void moveBackwards();
	virtual void moveBackwardsRight();
	virtual void moveBackwardsLeft();

	virtual void rotateClockwise();
	virtual void rotateAntiClockwise();
	virtual void stop();

	//Correction
	virtual void setRCorrection(unsigned int correction);
	virtual void setLCorrection(unsigned int correction);
	virtual void setCorrection(unsigned int r_correction, unsigned int l_correction);
	
	//Manual control
	virtual void setRPWM(byte pwm, bool reverse=false);
	virtual void setLPWM(byte pwm, bool reverse=false);
	virtual void setPWM(byte r_pwm, byte l_pwm, bool r_reverse=false, bool l_reverse=false);
	virtual void setMinPWM(byte r_min_pwm, byte l_min_pwm);
	virtual void setSpeed(unsigned int speed);
	virtual void setCurveFactor(byte factor);

protected:
	//Driver
	DuoDriver driver;

	byte r_pwm, l_pwm;
	float r_correction, l_correction;		//Corrects the motors pwm if they are not the same

	float curve_factor;						//Indicates how much a motor must rotate more than
											// the other motor to make a curve. It must be >= 1
	float speed;							//Multiplies every pwm
};
#endif