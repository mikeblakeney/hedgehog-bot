
#include "ADDRPinout.h"

#include <PinChangeInt.h>
#include "Motor.h"
#include "DiskEncoder.h"
#include "DifferentialDriver.h"
#include "Robot.h"
#include "ADDRSupervisor.h"

ADDRSupervisor addrSupervisor = ADDRSupervisor();

void incrementLeftEncoderCountInterrupt()
{
	addrSupervisor.incrementleftEncoderCount();
}

void incrementRightEncoderCountInterrupt()
{
	addrSupervisor.incrementRightEncoderCount();
}

void setup() {
	

	Serial.begin(9600);
	/*
		65mm diameter
		99.25mm base length
	*/
	DifferentialDriver *driver = new DifferentialDriver(0.0325, 0.09925);
	Robot* rob = new Robot(130, 30);

	Motor *leftMotor =  new Motor(L_MOTOR_PWM, L_MOTOR_DIR);
	Motor *rightMotor = new Motor(R_MOTOR_PWM, R_MOTOR_DIR);
	//rightMotor->setBeta( 0.90 );

	rob->setMotors(leftMotor, rightMotor);
	
	UltraSonicSensor A = UltraSonicSensor(SONIC_0);
	UltraSonicSensor B = UltraSonicSensor(SONIC_1);
	UltraSonicSensor C = UltraSonicSensor(SONIC_2);
	UltraSonicSensor D = UltraSonicSensor(SONIC_3);
	UltraSonicSensor E = UltraSonicSensor(SONIC_4);

	Serial.println(A.distance_cm());

	UltraSonicSensor sensors[] = {A, B, C, D, E};

	rob->setDistanceSensors(sensors);

	
	DiskEncoder* leftEncoder =  new DiskEncoder(L_ENCODER, 16);
	DiskEncoder* rightEncoder = new DiskEncoder(R_ENCODER, 16);
	PCintPort::attachInterrupt(L_ENCODER, &incrementLeftEncoderCountInterrupt, FALLING);
	PCintPort::attachInterrupt(R_ENCODER, &incrementRightEncoderCountInterrupt, FALLING);

	rob->setDiskEncoders(leftEncoder, rightEncoder);

	Serial.println("Starting ADDR-1");

	rob->setDifferentialDriver(driver);
	addrSupervisor.setRobot(rob);

	
}

void loop() {

	addrSupervisor.updateBehavior();
	
	delay(100);
}

