#ifndef MOTOR_H
#define MOTOR_H 

#include "ADDRTypes.h"

class Motor
{
public:
	Motor();
	Motor(int pwm, int dir);

	void setSpeed(int speed);
	void setDirection(wheel_direction dir);
	void goForward();
	void goBackward();

	void setBeta(float val);
	float getBeta();

	wheel_direction getDirection();

private:
	int speed;
	int pwm_pin;
	int dir_pin;

	float beta;

	float max_speed;
	float min_speed;

	wheel_direction direction;
};

#endif