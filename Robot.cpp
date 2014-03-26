
#include "Motor.h"
#include "Robot.h"


Robot::Robot(float rpm_max, float rpm_min )
{
	w_max = this->RPMToAngularVel(rpm_max);
	w_min = this->RPMToAngularVel(rpm_min);


	for(int i=0; i < 2; i++)
	{
		speedControllers[i] = new PIDController();
		speedControllers[i]->setTunings(4.0, 0.01, 0.01);
		speedControllers[i]->setTiming(0);
		speedControllers[i]->setIsAngle(false);
	}
}

void Robot::setMotors(Motor* left, Motor* right)
{
	motors[0] = left;
	motors[1] = right;
}

float Robot::RPMToAngularVel(float vel)
{
	return vel*2*PI/60;
}

void Robot::setDifferentialDriver(DifferentialDriver* driver)
{
	this->driver = driver;
}


diff_velocity Robot::velocityToPWM(diff_velocity vel)
{	
	/*
	Serial.print(vel.left);
	Serial.print(",");
	Serial.println(vel.right);
	*/

	float leftTarget = vel.left;
	float rightTarget = vel.right;


	float leftSpeed  = encoders[0]->getVelocity();
	float rightSpeed = encoders[1]->getVelocity();


	speedControllers[0]->compute(leftSpeed,  leftTarget, leftSpeed);
	speedControllers[1]->compute(rightSpeed, rightTarget, rightSpeed);
	
	
	if(leftSpeed  > 255 )	leftSpeed = 255;
	if(rightSpeed > 255)	rightSpeed = 255;
	if(leftSpeed  < -255)	leftSpeed = 255;
	if(rightSpeed < -255) 	rightSpeed = 255;

	
	
	/*
	Serial.print(leftSpeed);
	Serial.print(",");
	Serial.println(rightSpeed);
	
	
	Serial.print(encoders[0]->getVelocity());
	Serial.print(",");
	Serial.println(encoders[1]->getVelocity());
	*/

	vel.left = leftSpeed;
	vel.right = rightSpeed;

	return vel;
}

void Robot::setVelocity(uni_velocity vel)
{	


	diff_velocity diff_vel = this->ensure_w(vel);
	diff_vel = this->velocityToPWM(diff_vel);

/*
	Serial.print(diff_vel.left);
	Serial.print(",");
	Serial.println(diff_vel.right);
*/	
	motors[0]->setSpeed(diff_vel.left);
	motors[1]->setSpeed(diff_vel.right);
}

void Robot::stop()
{
	motors[0]->setSpeed(0);
	motors[1]->setSpeed(0);
}

void Robot::setDistanceSensors(UltraSonicSensor* sensors)
{
	for(int i = 0; i < 5; i++)
	{
		distance[i] = sensors[i];
	}
}

UltraSonicSensor Robot::getSonicSensor(int sensor)
{
	return distance[sensor];
}

void Robot::setDiskEncoders(DiskEncoder* left, DiskEncoder* right)
{
	encoders[0] = left;
	encoders[1] = right;
}

void Robot::incrementEncoderCount(int encoder)
{
	encoders[encoder]->incrementEncoderCount();
}

void Robot::decrementEncoderCount(int encoder)
{
	encoders[encoder]->decrementEncoderCount();
}

int Robot::getLeftEncoderCount()
{
	return encoders[0]->getEncoderCount();
}

int Robot::getRightEncoderCount()
{
	return encoders[1]->getEncoderCount();
}

int Robot::getTicksPerRev()
{
	return encoders[0]->getTicksPerRev();
}

float Robot::getWheelRadius()
{
	return driver->getWheelRadius();
}

float Robot::getWheelBaseLength()
{
	return driver->getWheelBaseLength();
}


diff_velocity Robot::ensure_w(uni_velocity uniVel)
{
/*
	float R = driver->getWheelRadius();
	float L = driver->getWheelBaseLength();

	float v_lim = fmax(fmin(abs(uniVel.v), (R/2)*(2*w_max)), (R/2) * (2 * w_min));
    float w_lim = fmax(fmin(abs(uniVel.w), (R/L)*(w_max - w_min)), 0);

	diff_velocity vel = driver->uniToDiff(v_lim, w_lim);
*/	

	diff_velocity vel = driver->uniToDiff(uniVel.v, uniVel.w);
	/*
	Serial.print(vel.left);
	Serial.print(",");
	Serial.println(vel.right);
	*/

	float left = vel.left;
	float right = vel.right;
	if(abs(uniVel.v) > 0)
	{
		float vel_rl_max = fmax(abs(vel.right), abs(vel.left));
		float vel_rl_min = fmin(abs(vel.right), abs(vel.left));

		if(vel_rl_max > w_max)
		{
			right = abs(vel.right) - (vel_rl_max - w_max);
			left  = abs(vel.left) -  (vel_rl_max - w_max);
		}else if(vel_rl_min < w_min)
		{
			right = abs(vel.right) + (w_min - vel_rl_min);
			left  = abs(vel.left)  + (w_min - vel_rl_min);
		}
	}
	else
	{
		if( abs(uniVel.w) > w_min )
		{
			uniVel.w = fmax( fmin( abs(uniVel.w), w_max), w_min);
			
			if(uniVel.w < 0)
				uniVel.w = -1 * uniVel.w;	
		}
		else
		{
			uniVel.w = 0;
		}
	}

/*
	uni_velocity shift = driver->diffToUni(vel.right, vel.left);

	if(uniVel.v < 0)
		shift.v = -1 * shift.v;

	if(uniVel.w < 0)
		shift.w = -1 * shift.w;

	vel = driver->uniToDiff(shift.v, shift.w);
*/

	if( vel.right < 0 )
		vel.right = -1 * right;

	if( vel.left < 0)
		vel.left = -1 * left;
	
/*
	Serial.print("Ensure: ");
	Serial.print(vel.left);
	Serial.print(",");
	Serial.println(vel.right);
*/
	return vel;
}
