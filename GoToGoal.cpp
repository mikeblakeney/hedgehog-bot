#include "GoToGoal.h"
#include <math.h>

GoToGoal::GoToGoal()
{
	pid = new PIDController();
	pid->setTiming(200);
	pid->setTunings(100.0, 0.01, 0.01);
}

void GoToGoal::execute(state_t est, state_t goal, float &w)
{
	float u_x = goal.x - est.x;
	float u_y = goal.y - est.y;
	float theta_d = atan2(u_y, u_x);

	pid->compute(est.theta, theta_d, w);
}