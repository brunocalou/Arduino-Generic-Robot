#include "robot.h"

#define BAUD_RATE		9600

#define R_ENABLE		4
#define R_MOTOR_1		5
#define R_MOTOR_2		6
#define R_MOTOR_MAX_PWM	255

#define L_ENABLE		9
#define L_MOTOR_1		11
#define L_MOTOR_2		10
#define L_MOTOR_MAX_PWM	255

#define VCC				12

#define COMMAND_DELAY	500

Robot robot(R_ENABLE,R_MOTOR_1,R_MOTOR_2,L_ENABLE,L_MOTOR_1,L_MOTOR_2,VCC);

unsigned long timer = 0;		//Stores the time when the last command was received

char command = 'S';
char last_command = 'S';

bool autonomous = false;		//Stores if the robot is on autonomous mode

////Ultrasonic test////

#define US_VCC		A2
#define US_TRIG		A4
#define US_ECHO		A3
#define US_GND		A5

////////////////////////

//Functions
void getCommand();
void useCommand();

void setup()
{
	/*
	 *Setting the PWM as a constant indicates that the method used to
	 *change the robot speed will be using the method setSpeed, that
	 *accepts a number between 0 and 100.
	 */

	robot.setMinPWM(80,80);
	robot.setPWM(R_MOTOR_MAX_PWM,L_MOTOR_MAX_PWM);
	robot.stop();

	Serial.begin(BAUD_RATE);

	////////////////Ultrasonic test////////////////

	pinMode(US_VCC, OUTPUT);
	pinMode(US_GND, OUTPUT);
	digitalWrite(US_VCC, HIGH);
	digitalWrite(US_GND, LOW);

	robot.setUltrasonic(US_TRIG, US_ECHO, FRONT);

	///////////////////////////////////////////////
}

void loop()
{
	bool read_sensors = true;

	if(Serial.available() > 0)
	{
		/*
		 * Read data from serial and control the robot
		 */
		getCommand();
		robot.useCommand(command);
	}
	else if(millis() - timer > COMMAND_DELAY && !autonomous)
	{
		/*
		 * If the last command received was greater than the command delay and
		 * the robot is not autonomous, stop it
		 */

		 robot.stop();
		 read_sensors = false;
	}

	if(autonomous)
	{
		/*
		 * Autonomous mode
		 * This piece of code was made just for testing
		 */

		float distance = robot.getUltrasonicDistance(FRONT, 1);
		if(distance < 40)
		{
			robot.moveBackwards();
		} else if (distance > 50)
		{
			robot.moveForward();
		} else {
			robot.stop();
		}
		delay(20);
	}
	else if(read_sensors)
	{
		Serial.println(robot.getUltrasonicDistance(FRONT, 1));
	}
}

void getCommand()
{
	last_command = command;
	command = Serial.read();
	timer = millis();
	Serial.println(command);
}
