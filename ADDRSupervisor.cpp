#include "ADDRSupervisor.h"

ADDRSupervisor::ADDRSupervisor()
{
	this->v = 0.30;
	
	this->cur_w = 0;

	this->estimated_state.x = 0;
	this->estimated_state.y = 0;
	this->estimated_state.theta = 0;

	this->goal.x = 0.70;
	this->goal.y = 0.80;
	this->goal.theta = 0.00;


	this->d_stop = 0.05;
	
	this->d_at_obs = 0.10;
	this->d_unsafe = 0.05;

	this->prev_ticks_right = 0;
	this->prev_ticks_left = 0;
	
	this->goToGoal = new GoToGoal();
	

	

}

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

	prev_ticks_right = 0;
	prev_ticks_left = 0;

	goToGoal = new GoToGoal();
}

bool ADDRSupervisor::updateBehavior()
{
	
	if( atGoal() )
	{
		robot->stop();
		Serial.println("GOAL!");
		return true;
	}else{
		goToGoal->execute(estimated_state, goal, cur_w);
		

		uni_velocity vel;
		vel.v = v;
		vel.w = cur_w;
		robot->setVelocity(vel);

		this->updateOdometry();
	}

	return false;
}

bool ADDRSupervisor::atGoal()
{
	float dist_to_goal = sqrt(pow(estimated_state.x - goal.x, 2) + pow(estimated_state.y - goal.y, 2));
	
	/*
	Serial.print("Distance to goal: ");
	Serial.println(dist_to_goal);
	*/

	if(dist_to_goal < d_stop )
		return true;
	else
		return false;
}

void ADDRSupervisor::updateOdometry()
{
	long right_ticks = robot->getRightEncoderCount();
	long left_ticks = robot->getLeftEncoderCount();

	float R = robot->getWheelRadius();
	float L = robot->getWheelBaseLength();

	float m_per_tick = (2 * PI * R)/robot->getTicksPerRev();

	float d_right = (right_ticks - prev_ticks_right) * m_per_tick;
	float d_left  = (left_ticks - prev_ticks_left) * m_per_tick;

	float d_center = (d_right + d_left) / 2;

	float phi = (d_right - d_left) / L;

	float theta_new = estimated_state.theta + phi;
	float x_new = estimated_state.x + d_center * cos(estimated_state.theta);;
	float y_new = estimated_state.y + d_center * sin(estimated_state.theta);;

	estimated_state.x = x_new;
	estimated_state.y = y_new;
	estimated_state.theta = theta_new;


	prev_ticks_left = left_ticks;
	prev_ticks_right = right_ticks;

	/*
	Serial.print(right_ticks);
	Serial.print(",");
	Serial.println(left_ticks);
	Serial.print(",");
*/
	
	
	Serial.print(estimated_state.x);
	Serial.print(",");
	Serial.print(estimated_state.y);
	Serial.print(",");

	Serial.println(estimated_state.theta * 180/PI);

}


void ADDRSupervisor::setRobot(Robot *rob)
{
	Serial.println("Goal is at: ");
	Serial.print(goal.x);
	Serial.print(",");
	Serial.println(goal.y);
	Serial.println("-------------");

	robot = rob;
}

void ADDRSupervisor::incrementEncoderCount(int encoder)
{
	robot->incrementEncoderCount(encoder);
}

void ADDRSupervisor::decrementEncoderCount(int encoder)
{
	robot->decrementEncoderCount(encoder);
}

