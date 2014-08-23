#ifndef SIMPLEENCODER_H
#define SIMPLEENCODER_H

class SimpleEncoder
{
public:
	SimpleEncoder(int pulses_per_rotation=1);
	void add();
	void subtract();
	void reset();
	long int getPulses();
	void setPulsesPerRotation(int value);
	float getRotation();

private:
	volatile long int pulses;
	int pulses_per_rotation;
};

#endif