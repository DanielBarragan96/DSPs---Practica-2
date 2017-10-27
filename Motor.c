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
static ufloat32 motorCycle = 5;

void checkMotor(){
	if(TRUE == PIT_getIntrStutus(PIT_0)){
		//get current desired motor speed
		ufloat32 systemVel = (getSystemStatus())->motor.velocityValue;

		//increase the motor velocity using the PWM
		if(motorCycle < systemVel){//if we need to increase the speed
			motorCycle += 5;
			if(MOTOR_MAX_VEL < motorCycle)	motorCycle = 100;//check speed limit
		}
		else if(motorCycle > systemVel){//if we need to decrease the speed
			motorCycle -= 5;
			if(MOTOR_MIN_VEL > motorCycle)	motorCycle = 5;//check speed limit
		}
		FlexTimer_updateCHValue(250*motorCycle/100);//Update the flex timer value
		PIT_clear(PIT_0);
		PIT_delay(PIT_0, SYSTEM_CLOCK, 3.0);// delay until next function value
	}
}

ufloat32 getMotorCurrentValue(){
	return motorCycle;//get the PWM value
}

void setMotorCurrentValue(ufloat32 val){
		motorCycle = val;//set initial PWM value
}
