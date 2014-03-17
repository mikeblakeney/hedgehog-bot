#ifndef DIFFERENTIAL_DRIVER
#define DIFFERENTIAL_DRIVER
#include "ADDRTypes.h"

class DifferentialDriver
{
public:
	DifferentialDriver(float R, float L);
	
	diff_velocity uniToDiff(float v, float w);
	uni_velocity DiffToUni(float r, float l); 

	float getWheelRadius();
	float getWheelBaseLength();

	
private:
	float wheel_radius;
	float wheel_base_length;


};

#endif