#ifndef SENSOR_H
#define SENSOR_H

#include "sensorproperties.h"

class Sensor
{
public:
	Sensor(int samples=10);
	virtual float getRawValue() = 0;
	virtual float getMeanValue();
	virtual float getMeanValue(int samples);
	virtual void setRange(float minimum, float maximum);
	virtual void setNumberOfSamples(int samples);


protected:
	int samples;
	float minimum_range;
	float maximum_range;
};

#endif