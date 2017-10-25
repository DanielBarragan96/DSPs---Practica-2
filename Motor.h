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
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function returns the value of the motor.
 	 \return the value of the current velocity of the motor.
 */
ufloat32 getMotorCurrentValue();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function modifies the motor status using the PWM.
 	 \param[in] val is the new value of motorCurrent, which controls the PWM.
 	 \return void
 */
void setMotorCurrentValue(ufloat32 val);

#endif
