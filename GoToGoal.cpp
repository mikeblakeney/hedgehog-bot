#include "GoToGoal.h"


GoToGoal::GoToGoal()
{
	pid = new PIDController();
	pid->setTunings(4, 0.01, 0.01);
}

void GoToGoal::execute(state_t est, state_t goal, float &w)
{
	pid->compute(est.theta, goal.theta, w);
}