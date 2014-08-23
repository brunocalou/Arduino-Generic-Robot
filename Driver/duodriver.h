/*
	L298 based driverl_
*/
#ifndef DUODRIVER_H
#define DUORDRIVER_H

#include "simpledriver.h"

class DuoDriver
{

public:
	DuoDriver(
		byte r_enable, 
		byte r_motor_1, byte r_motor_2,

		byte l_enable,
		byte l_motor_1, byte l_motor_2,
		
		byte r_vcc_ref=UNUSED, byte r_gnd_ref=UNUSED,
		byte l_vcc_ref=UNUSED, byte l_gnd_ref=UNUSED);

	SimpleDriver	l_motor, r_motor;
	
	void stop();
};

#endif