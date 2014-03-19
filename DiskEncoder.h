#ifndef DISKENCODER_H
#define DISKENCODER_H

class DiskEncoder
{
public:
	DiskEncoder(int pin, int ticks_per_rev);
	void initialize();
	int getEncoderCount();
	int getEncoderPin();
	void incrementEncoderCount();
	void decrementEncoderCount();

	int getTicksPerRev();
	
private:
	unsigned long encoderCount;
	int encoderPin;

	int ticks_per_rev;
};

#endif