#ifndef ADDR_SUPERVISOR
#define ADDR_SUPERVISOR

#include "ADDRTypes.h"
#include "Robot.h"
#include "GoToGoal.h"

class ADDRSupervisor
{
public:
	ADDRSupervisor();
	ADDRSupervisor(float v, float d_stop, float d_at_obs, float d_unsafe, 
					  float init_x, float init_y, float init_theta,
					  float g_x, float g_y, float g_theta);
	
	void setRobot(Robot* rob);
	void setDifferentialDriver(DifferentialDriver* driver);

	void incrementleftEncoderCount();
	void incrementRightEncoderCount();

	
	void updateBehavior();

private:
	
	void updateOdometry();
	bool atGoal();
	void stop();




	Robot* robot;
	int prev_ticks_right;
	int prev_ticks_left;

	float v;
	float cur_w;

	float d_stop;
	float d_at_obs;
	float d_unsafe;

	state_t goal;

	state_t estimated_state;


	GoToGoal* goToGoal;


};

#endif