
#include "Motor.h"
#include "Robot.h"


Robot::Robot(float max_rpm, float min_rpm )
{
	max_vel = this->velocityToRPM(max_rpm);
	min_vel = this->velocityToRPM(min_rpm);
}

void Robot::setMotors(Motor* left, Motor* right)
{
	motors[0] = left;
	motors[1] = right;
}

float Robot::velocityToRPM(float vel)
{
	return vel*2*PI/60;
}

void Robot::setDifferentialDriver(DifferentialDriver* driver)
{
	this->driver = driver;
}


diff_velocity Robot::velocityToPWM(diff_velocity vel)
{	
	float vel_rl_max = fmax(vel.right, vel.left);
	float vel_rl_min = fmin(vel.right, vel.left);
	
	if(vel_rl_max > max_vel)
	{
		vel.right = vel.right - (vel_rl_max - max_vel);
		vel.left  = vel.left - (vel_rl_max - max_vel);
	}else if(vel_rl_min < min_vel)
	{
		vel.right = vel.right + (min_vel - vel_rl_min);
		vel.left  = vel.left  + (min_vel - vel_rl_min);
	}


	vel.right = map(vel.right, min_vel, max_vel, 90, 255);
	vel.left  = map(vel.left , min_vel, max_vel, 90, 255);

	return vel;
}

void Robot::setVelocity(uni_velocity vel)
{	
	diff_velocity diff_vel = driver->uniToDiff(vel.v, vel.w);
	if(abs(vel.v) > 0)
	{
		diff_vel = velocityToPWM(diff_vel);
	}
	else
	{
		diff_vel.right = 0;
		diff_vel.left = 0;
	}


	
	motors[0]->setSpeed(diff_vel.right);
	motors[1]->setSpeed(diff_vel.left);
}

void Robot::setDistanceSensors(UltraSonicSensor* sensors)
{
	for(int i = 0; i < 5; i++)
	{
		distance[i] = sensors[i];
	}
}

UltraSonicSensor Robot::getSonicSensor(int sensor)
{
	return distance[sensor];
}

void Robot::setDiskEncoders(DiskEncoder* left, DiskEncoder* right)
{
	encoders[0] = left;
	encoders[1] = right;
}

void Robot::updateLeftEncoderCount()
{

	switch(motors[0]->getDirection())
	{
	case FORWARD:
		encoders[0]->incrementEncoderCount();
		break;
	case BACKWARD:
		encoders[0]->decrementEncoderCount();
		break;
	default:
		break;
	}
}

void Robot::updateRightEncoderCount()
{
	switch(motors[1]->getDirection())
	{
	case FORWARD:
		encoders[1]->incrementEncoderCount();
		break;
	case BACKWARD:
		encoders[1]->decrementEncoderCount();
		break;
	default:
		break;
	}
}

int Robot::getLeftEncoderCount()
{
	return encoders[0]->getEncoderCount();
}

int Robot::getRightEncoderCount()
{
	return encoders[1]->getEncoderCount();
}

int Robot::getTicksPerRev()
{
	return encoders[0]->getTicksPerRev();
}

float Robot::getWheelRadius()
{
	driver->getWheelRadius();
}

float Robot::getWheelBaseLength()
{
	driver->getWheelBaseLength();
}


diff_velocity Robot::ensure_w(uni_velocity vel)
{
	diff_velocity diff_vel;

	float R = driver->getWheelRadius();
	float L = driver->getWheelBaseLength();

/*

	if(abs(vel.v) > 0)
	{
		float v_lim  = fmax(fmin(abs(vel.v), R/2 * 2 * max_vel), R/2 * 2 * min_vel);
		float w_lim  = fmax(fmin(abs(vel.w), R/L * (max_vel - min_vel)), 0);

		diff_velocity vel_d = driver->uniToDiff(v_lim, w_lim);

		float vel_rl_max = fmax(vel_d.right, vel_d.left);
		float vel_rl_min = fmin(vel_d.right, vel_d.left);

		if(vel_rl_max > max_vel)
		{
			diff_vel.right = vel_d.right - (vel_rl_max - max_vel);
			diff_vel.left  = vel_d.left  - (vel_rl_max - max_vel);
		}else if(vel_rl_min < min_vel)
		{
			diff_vel.right = vel_d.right + (vel_rl_min - min_vel);
			diff_vel.left  = vel_d.left  + (vel_rl_min - min_vel);
		}else
		{
			diff_vel.right = vel_d.right;
			diff_vel.left  = vel_d.left;
		}
	}else
	{
		diff_vel.right = 0;
		diff_vel.left  = 0;
	}

*/

	diff_velocity vel_d = driver->uniToDiff(vel.v , vel.w );




	return diff_vel;
}
