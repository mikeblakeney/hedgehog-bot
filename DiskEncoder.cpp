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
}

void DiskEncoder::decrementEncoderCount()
{
	encoderCount--;
}

int DiskEncoder::getEncoderPin()
{
	return encoderPin;
}

int DiskEncoder::getTicksPerRev()
{
	return ticks_per_rev;
}

float DiskEncoder::getVelocity()
{
	long now = millis();
	long timeChange = (now - lastTime);
	long count = encoderCount - lastCount;
	
	
	Serial.print(encoderCount);
	Serial.print(",");
	Serial.println(lastCount);
	
	if(timeChange > 1000)
	{
		/*
		Serial.print(count);
		Serial.print(",");
		Serial.println(timeChange / 1000.0);
		*/

		timeChange = timeChange / 1000.0;
		velocity = (float)count/timeChange;
		
		lastTime = now;
		lastCount = encoderCount;
	}


	return velocity;
}