/**
 * @file    Motor.c
 * @brief   Control the motor of the system
 * autor: Daniel Barragán
 */

#include "DataTypeDefinitions.h"
#include "NVIC.h"
#include "GPIO.h"
#include "PIT.h"
#include "MK64F12.h"
#include "FlexTimer.h"
#include "Motor.h"
#include "States.h"

static uint8 motorCycle = 80;

void checkMotor(){
	SystemStatus actualSystem = *(getSystemStatus());

	if(motorCycle == actualSystem.motor.velocityValue) return;

	if(motorCycle < actualSystem.motor.velocityValue){
		motorCycle += 5;
		if(MOTOR_MAX_VEL < motorCycle)	motorCycle = 100;
	}
	else if(motorCycle > actualSystem.motor.velocityValue){
		motorCycle -= 5;
		if(MOTOR_MIN_VEL > motorCycle)	motorCycle = 5;
	}
	FlexTimer_updateCHValue(motorCycle);

}
