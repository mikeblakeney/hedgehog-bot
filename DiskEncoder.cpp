#include "DiskEncoder.h"
#include <arduino.h>


DiskEncoder::DiskEncoder(int pin, int ticks_per_rev)
{
	encoderCount = 0;
	encoderPin = pin;
	pinMode(encoderPin, INPUT);
	digitalWrite(encoderPin, HIGH);
	this->ticks_per_rev = ticks_per_rev;
}

int DiskEncoder::getEncoderCount()
{
	return encoderCount;
}
	
void DiskEncoder::incrementEncoderCount()
{
	encoderCount++;
}

int DiskEncoder::getEncoderPin()
{
	return encoderPin;
}

int DiskEncoder::getTicksPerRev()
{
	return ticks_per_rev;
}