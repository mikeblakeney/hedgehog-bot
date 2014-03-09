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
	setDirection(1);

	beta = 1;
}


void Motor::setSpeed(int speed)
{
	analogWrite(pwm_pin, beta * speed);
}


void Motor::setDirection(int forward)
{
	if(forward)
	{
		digitalWrite(dir_pin, HIGH);
	}else
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
	setDirection(1);
}

void Motor::goBackward()
{
	setDirection(0);
}


