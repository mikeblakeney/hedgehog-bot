#include "Motor.h"
#include <arduino.h>



Motor::Motor()
{
	beta = 1;
}

Motor::Motor(int pwm, int dir)
{
	this->pwm_pin = pwm;
	this->dir_pin = dir;

	pinMode(dir_pin, OUTPUT);
	setDirection(FORWARD);

	beta = 1;
}


void Motor::setSpeed(int speed)
{
	if(speed > 0)
	{
		setDirection(FORWARD);
		analogWrite(pwm_pin, beta * speed);
	}else
	{
		setDirection(BACKWARD);
		analogWrite(pwm_pin, -1 * beta * speed);
	}
	
}

void Motor::setDirection(wheel_direction dir)
{
	if(dir == FORWARD)
	{
		digitalWrite(dir_pin, HIGH);
	}else if(dir == BACKWARD)
	{
		digitalWrite(dir_pin, LOW);
	}
}

void Motor::setBeta(float val)
{
	beta = val;
}

float Motor::getBeta()
{
	return beta;
}


void Motor::goForward()
{
	setDirection(FORWARD);
}

void Motor::goBackward()
{
	setDirection(BACKWARD);
}


