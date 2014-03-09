#ifndef _ULTRASONICSENSOR_H
#define _ULTRASONICSENSOR_H

class UltraSonicSensor
{
	public:
		UltraSonicSensor();
		UltraSonicSensor(int pin);
		float fireEcho();
		float distance_cm();
		float distance_in();

	private:		
		int pin;
};

#endif