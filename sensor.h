#ifndef SENSOR_H
#define SENSOR_H

#include "sensorproperties.h"

class Sensor
{
public:
	Sensor(int samples=10);
	virtual data_t getRawValue() = 0;
	virtual data_t getMeanValue();
	virtual data_t getMeanValue(int samples);
	virtual void setRange(data_t minimum, data_t maximum);
	virtual void setNumberOfSamples(int samples);


protected:
	int samples;
	data_t minimum_range;
	data_t maximum_range;
};

#endif