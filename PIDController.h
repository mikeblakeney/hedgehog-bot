#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

class PIDController
{
public:
	PIDController();

	void compute(float state, float goal, float &output);
	void setTunings(float Kp, float Ki, float Kd);
	void setTiming(int time);
	void setIsAngle(bool angle);

private:
	float Kp;
	float Ki;
	float Kd;

	float errSum;
	float prevErr;

	long lastTime;
	int dt;

	bool isAngle;

};

#endif