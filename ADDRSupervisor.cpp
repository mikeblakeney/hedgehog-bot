#include "ADDRSupervisor.h"

ADDRSupervisor::ADDRSupervisor(float v, float d_stop, float d_at_obs, float d_unsafe, 
									 float init_x, float init_y, float init_theta,
									 float g_x, float g_y, float g_theta
									 )
{
	this->v = v;

	this->goal.x = g_x;
	this->goal.y = g_y;
	this->goal.theta = g_theta;


	this->d_stop = d_stop;
	
	this->d_at_obs = d_at_obs;
	this->d_unsafe = d_unsafe;
	
	this->estimated_state.x = init_x;
	this->estimated_state.y = init_y;
	this->estimated_state.theta = init_theta;

	

	goToAngle = new GoToAngle();

}



void ADDRSupervisor::updateBehavior()
{
	float w = goToAngle->execute(estimated_state, goal.theta);
	
	Serial.print("GoToAngle: ");
	Serial.println(w);
	uni_velocity vel;
	vel.v = v;
	vel.w = w;
	robot->setVelocity(vel);

	this->updateOdometry();

}

void ADDRSupervisor::updateOdometry()
{
	int right_ticks = robot->getRightEncoderCount();
	int left_ticks = robot->getLeftEncoderCount();

	float R = robot->getWheelRadius();
	float L = robot->getWheelBaseLength();

	float m_per_tick = (2 * PI * R)/robot->getTicksPerRev();

	float d_right = (right_ticks - prev_ticks_right) * m_per_tick;
	float d_left  = (left_ticks - prev_ticks_left) * m_per_tick;

	float d_center = (d_right + d_left) / 2;

	float phi = (d_right - d_left) / L;

	float x_dt = d_center * cos(estimated_state.theta);
	float y_dt = d_center * sin(estimated_state.theta);
	float theta_dt = phi;

	float theta_new = estimated_state.theta + theta_dt;
	float x_new = estimated_state.x + x_dt;
	float y_new = estimated_state.y + y_dt;

	estimated_state.x = x_new;
	estimated_state.y = y_new;
	estimated_state.theta = atan2(sin(theta_new) , cos(theta_new) );


	prev_ticks_left = left_ticks;
	prev_ticks_right = right_ticks;


	Serial.print(estimated_state.x);
	Serial.print("\t\t");
	Serial.print(estimated_state.y);
	Serial.print("\t\t");
	Serial.println(estimated_state.theta * 180/PI);


}


void ADDRSupervisor::setRobot(Robot *rob)
{
	robot = rob;
}

void ADDRSupervisor::incrementleftEncoderCount()
{
	robot->incrementleftEncoderCount();
}

void ADDRSupervisor::incrementRightEncoderCount()
{
	robot->incrementRightEncoderCount();
}
