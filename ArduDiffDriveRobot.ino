
#include "ADDRPinout.h"

#include <PinChangeInt.h>
#include "Motor.h"
#include "DiskEncoder.h"
#include "DifferentialDriver.h"
#include "Robot.h"
#include "ADDRSupervisor.h"

#define ENC_HIGH_DELAY 10

volatile long lastRiseTimeL = 0;
volatile long lastRiseTimeR = 0;

bool start = true;
bool atGoal = false;

ADDRSupervisor *supervisor = new ADDRSupervisor();

void updateLeftEncoderCountInterrupt()
{
	if(lastRiseTimeL + ENC_HIGH_DELAY < millis())
	{
		if(digitalRead(L_MOTOR_DIR) == HIGH)
			supervisor->incrementEncoderCount(0);
		else
			supervisor->decrementEncoderCount(0);
		lastRiseTimeL = millis();
	}
}

void updateRightEncoderCountInterrupt()
{
	if(lastRiseTimeR + ENC_HIGH_DELAY < millis())
	{

		if(digitalRead(R_MOTOR_DIR) == HIGH)
			supervisor->incrementEncoderCount(1);
		else
			supervisor->decrementEncoderCount(1);


		lastRiseTimeR = millis();
	}
}

void setup() {
	

	Serial.begin(9600);
	/*
		65mm diameter
		99.25mm base length
	*/
	
	Robot *robot = new Robot(130, 60);

	Motor *leftMotor =  new Motor(L_MOTOR_PWM, L_MOTOR_DIR);
	Motor *rightMotor = new Motor(R_MOTOR_PWM, R_MOTOR_DIR);
	//rightMotor->setBeta( 0.90 );

	robot->setMotors(leftMotor, rightMotor);
	
	UltraSonicSensor A = UltraSonicSensor(SONIC_0);
	UltraSonicSensor B = UltraSonicSensor(SONIC_1);
	UltraSonicSensor C = UltraSonicSensor(SONIC_2);
	UltraSonicSensor D = UltraSonicSensor(SONIC_3);
	UltraSonicSensor E = UltraSonicSensor(SONIC_4);
	UltraSonicSensor sensors[] = {A, B, C, D, E};

	robot->setDistanceSensors(sensors);

	
	DiskEncoder* leftEncoder =  new DiskEncoder(L_ENCODER, 16);
	DiskEncoder* rightEncoder = new DiskEncoder(R_ENCODER, 16);
	PCintPort::attachInterrupt(L_ENCODER, &updateLeftEncoderCountInterrupt, RISING);
	PCintPort::attachInterrupt(R_ENCODER, &updateRightEncoderCountInterrupt, RISING);

	robot->setDiskEncoders(leftEncoder, rightEncoder);

	Serial.println("Starting ADDR-1");
	
	DifferentialDriver *driver = new DifferentialDriver(0.0325, 0.09925);
	robot->setDifferentialDriver(driver);
	
	supervisor->setRobot(robot);
	
}

void loop() {


	if(Serial.available() > 0)
	{
		char input = Serial.read();
		if(input == 'g') start = true;
	}
	
	if(start && !atGoal)
	{
		atGoal = supervisor->updateBehavior();
	}

}
