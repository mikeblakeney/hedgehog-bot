#include "PIDController.h"

#include <arduino.h>
#include <math.h>

PIDController::PIDController()
{
	Kp = 0;
	Ki = 0;
	Kd = 0;

	errSum = 0;
	prevErr = 0;

	dt = 200;

	isAngle = true;

	lastTime = millis();
}

void PIDController::compute(float state, float desired, float &output)
{
	
	long now = millis();
	long current_dt = now - lastTime;
	


	if( current_dt >= dt)
	{
		float error = desired - state;
		
		if(isAngle)
		{
			error = atan2(sin(error), cos(error));
		}
		/*
		Serial.print(state);
		Serial.print(",");
		Serial.print(desired);
		Serial.print(",");
		Serial.println(error);
	*/

		float e_P = error;

		float e_I = errSum + error * current_dt;

		float e_D = (error - prevErr)/current_dt;

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

void PIDController::setIsAngle(bool angle)
{
	this->isAngle = angle;
}