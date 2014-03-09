#ifndef MOTOR_H
#define MOTOR_H 

class Motor
{
public:
	Motor();
	Motor(int pwm, int dir);

	void setSpeed(int speed);
	
	void setDirection(int forward);
	void goForward();
	void goBackward();

	void setBeta(float val);
	float getBeta();

private:
	int speed;
	int pwm_pin;
	int dir_pin;

	float beta;
};

#endif