#include "DiskEncoder.h"
#include <arduino.h>


DiskEncoder::DiskEncoder(int pin, int ticks_per_rev)
{
	encoderCount = 0;
	encoderPin = pin;
	pinMode(encoderPin, INPUT);
	digitalWrite(encoderPin, HIGH);
	this->ticks_per_rev = ticks_per_rev;


	lastCount = 0;
	lastTime = 0;
	velocity = 0;
}

long DiskEncoder::getEncoderCount()
{
	return encoderCount;
}
	
void DiskEncoder::incrementEncoderCount()
{
	encoderCount++;
	this->updateVelocity();
}

void DiskEncoder::decrementEncoderCount()
{
	encoderCount--;
	this->updateVelocity();
}

int DiskEncoder::getEncoderPin()
{
	return encoderPin;
}

int DiskEncoder::getTicksPerRev()
{
	return ticks_per_rev;
}

void DiskEncoder::updateVelocity()
{
	long now = millis();
	long timeChange = (now - lastTime);
	long count = encoderCount - lastCount;
	
	/*
	Serial.print(encoderCount);
	Serial.print(",");
	Serial.println(lastCount);
	*/
	if(timeChange > 50)
	{
		velocity = (float)count/timeChange * 1000 * (2 * PI) / ticks_per_rev;
		
		/*
		Serial.print(velocity);
		Serial.print(",");
		Serial.println(timeChange / 1000.0);
		*/
		lastTime = now;
		lastCount = encoderCount;
	}
}

float DiskEncoder::getVelocity()
{
	return velocity;
}