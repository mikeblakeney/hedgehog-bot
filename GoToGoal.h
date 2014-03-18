#ifndef GOTOGOAL_H
#define GOTOGOAL_H

#include "PIDController.h"
#include "ADDRTypes.h"

class GoToGoal
{
public:
	GoToGoal();
	void execute(state_t est, state_t goal, float &w);
private:
	PIDController* pid;
};

#endif