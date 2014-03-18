#ifndef _ROBOT_H
#define _ROBOT_H

#include "Motor.h"
#include "UltraSonicSensor.h"
#include "DiskEncoder.h"
#include "DifferentialDriver.h"
#include <arduino.h>



class Robot 
{
public:
	Robot(float max_rpm, float min_rpm );

	float getWheelRadius();
	float getWheelBaseLength();

	void setDistanceSensors(UltraSonicSensor* sensors);
	UltraSonicSensor getSonicSensor(int sensor);

	void setMotors(Motor* left, Motor* right);
	void setVelocity(uni_velocity vel);
	void setDifferentialDriver(DifferentialDriver* driver);

	void setDiskEncoders(DiskEncoder* left, DiskEncoder* right);
	void incrementleftEncoderCount();
	void incrementRightEncoderCount();
	int getLeftEncoderCount();
	int getRightEncoderCount();
	int getTicksPerRev();

private:
	UltraSonicSensor distance[5];
	Motor* motors[2];
	DifferentialDriver* driver;

	DiskEncoder* encoders[2];

	

	float position[2];
	float velocity[2];

	float phi;
	float omega[2];

	float max_vel;
	float min_vel;


	float velocityToRPM(float vel);
	diff_velocity velocityToPWM(diff_velocity vel);
	diff_velocity ensure_w(uni_velocity vel);


};

#endif