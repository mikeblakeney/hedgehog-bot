
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
	
	vel.right = map(vel.right, min_vel, max_vel, 0, 255);
	vel.left =  map(vel.left , min_vel, max_vel, 0, 255);
	return vel;
}

void Robot::setVelocity(uni_velocity vel)
{	
	diff_velocity diff_vel;

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

void Robot::incrementleftEncoderCount()
{
	encoders[0]->incrementEncoderCount();
}

void Robot::incrementRightEncoderCount()
{
	encoders[1]->incrementEncoderCount();
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