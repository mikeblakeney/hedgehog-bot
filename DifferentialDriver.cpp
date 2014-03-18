#include "DifferentialDriver.h"
#include <arduino.h>

DifferentialDriver::DifferentialDriver(float R, float L)
{
	wheel_radius = R;
	wheel_base_length = L;
}

diff_velocity DifferentialDriver::uniToDiff(float v, float w)
{
	float R = wheel_radius;
	float L = wheel_base_length;

	diff_velocity vel;

	vel.right = (2 * v + w * L)/(2 * R);
	vel.left  = (2 * v - w * L)/(2 * R);
	
	return vel;
}

uni_velocity DifferentialDriver::DiffToUni(float r, float l)
{
	float R = wheel_radius;
	float L = wheel_base_length;

	uni_velocity vel;

	vel.v = R/2*(r + l);
	vel.w = R/L*(r - l);

	return vel;
}

float DifferentialDriver::getWheelRadius()
{
	return wheel_radius;
}

float DifferentialDriver::getWheelBaseLength()
{
	return wheel_base_length;
}