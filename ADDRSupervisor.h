#ifndef ADDR_SUPERVISOR
#define ADDR_SUPERVISOR

#include "ADDRTypes.h"
#include "Robot.h"
#include "GoToAngle.h"

class ADDRSupervisor
{
public:
	ADDRSupervisor(float v, float d_stop, float d_at_obs, float d_unsafe, 
					  float init_x, float init_y, float init_theta);
	
	void setRobot(Robot* rob);

	void incrementleftEncoderCount();
	void incrementRightEncoderCount();

	
	void updateBehavior();

private:
	
	void updateOdometry();
	
	Robot* robot;
	int prev_ticks_right;
	int prev_ticks_left;

	float v;

	float d_stop;
	float d_at_obs;
	float d_unsafe;

	state_t estimated_state;

	GoToAngle* goToAngle;
};

#endif