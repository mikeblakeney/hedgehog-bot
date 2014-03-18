#include "GoToAngle.h"

#include "math.h"



GoToAngle::GoToAngle()
{
	Kp = 1;
}

float GoToAngle::execute(state_t est, float theta_goal)
{
	
	float theta_d = theta_goal;

	float x = est.x;
	float y = est.y;
	float theta = est.theta;

	float e_k = theta_d - theta;
	e_k = atan2(sin(e_k), cos(e_k));

	float w = Kp * e_k;
	return w;

}