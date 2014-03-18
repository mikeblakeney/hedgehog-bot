#include "PIDController.h"

#include <arduino.h>
#include <math.h>

PIDController::PIDController()
{
	Kp = 0;
	Ki = 0;
	Kd = 0;

	dt = 1000;
}

float PIDController::compute(float state, float goal, float &output)
{
	int now = millis();
	
	if(now - lastTime >= dt)
	{
		float error = goal - state;
		error = atan2(sin(error), cos(error));

		float e_P = error;

		float e_I = errSum + error * dt;

		float e_D = (error - prevErr)/dt;

		output = Kp * e_P + Ki * e_I + Kd * e_D;

		errSum = e_I;
		prevErr = error;
		lastTime = now;
	}
}

void PIDController::setTunings(float Kp, float Ki, float Kd)
{
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;
}

void PIDController::setTiming(int time)
{
	this->dt = time;
}