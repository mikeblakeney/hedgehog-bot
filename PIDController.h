#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

class PIDController
{
public:
	PIDController();

	void compute(float state, float goal, float &output);
	void setTunings(float Kp, float Ki, float Kd);
	void setTiming(int time);

private:
	float Kp;
	float Ki;
	float Kd;

	float errSum;
	float prevErr;

	int lastTime;
	int dt;

};

#endif