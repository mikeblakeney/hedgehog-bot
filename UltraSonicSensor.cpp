#include <arduino.h>
#include "UltraSonicSensor.h"

UltraSonicSensor::UltraSonicSensor()
{}

UltraSonicSensor::UltraSonicSensor(int pin)
{
	this->pin = pin;
}

float UltraSonicSensor::fireEcho()
{
	pinMode(pin, OUTPUT);
	digitalWrite(pin, HIGH);
	delay(10);
	digitalWrite(pin, LOW);

	pinMode(pin, INPUT);
	float time = pulseIn(pin, HIGH);

	// make sure pin is set to LOW for next time
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);

	return time;
}

float UltraSonicSensor::distance_cm()
{
	float time = fireEcho();
	return time / 58.0;
}

float UltraSonicSensor::distance_in()
{
	float time = fireEcho();
	return time / 148.0;
}