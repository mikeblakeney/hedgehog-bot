#ifndef ADDR_SUPERVISOR
#define ADDR_SUPERVISOR

#include "Robot.h"

struct state_t {
	float x;
	float y;
	float theta;
};

class ADDRSupervisor
{
public:
	ADDRSupervisor(float v, float d_stop, float d_at_obs, float d_unsafe, 
					  float init_x, float init_y, float init_theta);
	
	void process_MPU();
	bool imuPacketsAvailable();
	
	void setRobot(Robot* rob);

	void incrementleftEncoderCount();
	void incrementRightEncoderCount();

	void updateOdometry();

private:
	
	
	Robot* robot;
	int prev_ticks_right;
	int prev_ticks_left;

	float v;

	float d_stop;
	float d_at_obs;
	float d_unsafe;

	state_t estimated_state;
};

#endif