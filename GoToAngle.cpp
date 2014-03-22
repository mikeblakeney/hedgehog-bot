#include "GoToAngle.h"

GoToAngle::GoToAngle()
{
	pid = new PIDController();
	pid->setTunings(1, 0, 0);
}

void GoToAngle::execute(state_t est, float theta_goal, float &w)
{
	pid->compute(est.theta, theta_goal, w);
}