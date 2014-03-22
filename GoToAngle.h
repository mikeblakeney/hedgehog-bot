#ifndef GOTOANGLE_H
#define GOTOANGLE_H
#include "ADDRTypes.h"
#include "PIDController.h"

class GoToAngle
{
public:
	GoToAngle();

	void execute(state_t est, float theta_goal, float &w );
private:
	PIDController* pid;
};


#endif