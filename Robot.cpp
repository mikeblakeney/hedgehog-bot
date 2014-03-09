
#include "Motor.h"
#include "Robot.h"


Robot::Robot(DifferentialDriver *diff)
{
	//imu = new IMUSensor();
	driver = diff;
}

void Robot::setMotors(Motor* left, Motor* right)
{
	motors[0] = left;
	motors[1] = right;


}

Motor* Robot::getLeftMotor()
{
	return motors[0];
}

Motor* Robot::getRightMotor()
{
	return motors[1];
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

float Robot::getWheelRadius()
{
	return driver->getWheelRadius();
}

float Robot::getWheelBaseLength()
{
	return driver->getWheelBaseLength();
}

int Robot::getTicksPerRev()
{
	return encoders[0]->getTicksPerRev();
}

void Robot::initialize()
{
	
	//	imu->initialize();
}

/*
void Robot::calibrateIMU()
{
	imu->calibrate();
}

imu_int_status_t Robot::getMPUIntStatus()
{
	return imu->getIntStatus();
}

bool Robot::imuPacketsAvailable()
{
	return imu->packetsAvailable();
}

VectorInt16 Robot::getAcceleration()
{
	return imu->getAcceleration();
}

ypr_t Robot::getOrientation()
{
	return imu->getOrientation();
}

bool Robot::testIMUConnection()
{
	return imu->testConnection();
}
*/
