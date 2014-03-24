#ifndef DISKENCODER_H
#define DISKENCODER_H

class DiskEncoder
{
public:
	DiskEncoder(int pin, int ticks_per_rev);
	void initialize();
	long getEncoderCount();
	int getEncoderPin();
	void incrementEncoderCount();
	void decrementEncoderCount();

	int getTicksPerRev();

	float getVelocity();

	
private:
	void updateVelocity();

	long encoderCount;
	int encoderPin;

	int ticks_per_rev;

	long lastCount;
	long lastTime;
	float velocity;
};

#endif