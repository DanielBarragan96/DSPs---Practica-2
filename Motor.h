/**
 * @file    Motor.h
 * @brief   Control the motor of the system
 * autor: Daniel Barragán
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "DataTypeDefinitions.h"
#include "NVIC.h"
#include "GPIO.h"
#include "PIT.h"
#include "MK64F12.h"
#include "States.h"

/*Type for the motor limits*/
typedef enum{
	MOTOR_MIN_VEL = 5,
	MOTOR_MAX_VEL = 100
}MOTOR_LIMITS;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function modifies the motor status using the PWM.
 	 \return void
 */
void checkMotor();

#endif
