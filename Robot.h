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
	Robot(DifferentialDriver *diff);

	float getWheelRadius();
	float getWheelBaseLength();

	void setDistanceSensors(UltraSonicSensor* sensors);
	UltraSonicSensor getSonicSensor(int sensor);

	void setMotors(Motor* left, Motor* right);


	void setDiskEncoders(DiskEncoder* left, DiskEncoder* right);
	void incrementleftEncoderCount();
	void incrementRightEncoderCount();
	int getLeftEncoderCount();
	int getRightEncoderCount();
	int getTicksPerRev();

	void initialize();



private:
	UltraSonicSensor distance[5];
	Motor* motors[2];

	DiskEncoder* encoders[2];

	DifferentialDriver* driver;

	float position[2];
	float velocity[2];

	float phi;
	float omega[2];





};

#endif