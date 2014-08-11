#ifndef ROBOT_H
#define ROBOT_H

#include "controlboard.h"
#include "sensorboard.h"

class Robot: public SensorBoard, public ControlBoard
{

public:
	Robot(byte r_enable, 
		byte r_motor_1, byte r_motor_2,

		byte l_enable,
		byte l_motor_1, byte l_motor_2,
		
		byte r_vcc_ref=UNUSED, byte r_gnd_ref=UNUSED,
		byte l_vcc_ref=UNUSED, byte l_gnd_ref=UNUSED);

	void useCommand(char command);
};

#endif