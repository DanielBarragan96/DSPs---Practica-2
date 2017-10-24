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

//physical actual value of the motor velocity
static ufloat32 motorCycle = 80;

void checkMotor(){
	//get current desired motor speed
	ufloat32 systemVel = (getSystemStatus())->motor.velocityValue;

	//if the motor has the current motor speed do nothing
	if(motorCycle == systemVel) return;

	//increase the motor velocity using the PWM
	if(motorCycle < systemVel){//if we need to increase the speed
		motorCycle += 5;
		if(MOTOR_MAX_VEL < motorCycle)	motorCycle = 100;//check speed limit
	}
	else if(motorCycle > systemVel){//if we need to decrease the speed
		motorCycle -= 5;
		if(MOTOR_MIN_VEL > motorCycle)	motorCycle = 5;//check speed limit
	}
	//Update the flex timer value
	FlexTimer_updateCHValue(FTM0->MOD*motorCycle/100);

	//TODO PIT for decelerate the motor
}
