#ifndef GOTOANGLE_H
#define GOTOANGLE_H
#include "ADDRTypes.h"

class GoToAngle
{
public:
	GoToAngle();

	float execute(state_t est, float theta_goal );
private:
	float Kp;
	float Ki;
	float Kd;
};


#endif