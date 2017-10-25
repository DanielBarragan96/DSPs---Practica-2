/**
 * @file    Status.h
 * @brief   Control the status of the system
 * autor: Daniel Barragán
 */

#ifndef STATES_H_
#define STATES_H_

#include "DataTypeDefinitions.h"
#include "NVIC.h"
#include "GPIO.h"
#include "PIT.h"
#include "MK64F12.h"

/*Type for the LCD screen state*/
typedef enum{
	MAIN_STATE = 0,
	MAIN_MENU_STATE,
	ALARMA_STATE,
	FORMAT_STATE,
	CHANGE_STATE,
	MANUAL_STATE,
	FRECUENCY_STATE,
	ERROR_STATE
}ProgrmaState;
/*Type for the alarm status*/
typedef enum{ OFF, ON }StatusTurn;
/*Type for the pressed button*/
typedef enum{ NO_BUTTON, B0, B1, B2, B3, B4, B5 }Buttons;
/*Type for the temperature type*/
typedef enum{ CELSIUS, FAHRENHEIT }DEGREES;
/*Type for the velocity limits*/
typedef enum{VEL_LOW = 5,VEL_MAX = 100}Velocity_Limits;
/*Type for the alarm settings*/
typedef struct{
	StatusTurn alarmStatus;//current value of the alarm
	ufloat32 alarmaValue;//value at which the alarm should sound
	ufloat32 alarmMonitor;//desired change of the value of alarmValue
	ufloat32 decrementValue;
	ufloat32 decrementMonitor;
}Alarm;
/*Type for the showed temperature*/
typedef struct{
	ufloat32 celsiusValue;//the temperature value in celsius
	DEGREES typeDeegreesMonitor;//desired change of calesiusValue
	DEGREES typeDeegrees;//The format of the temperature showed in the screen
}Temperature;
/*Type for the velocity of the motor*/
typedef struct{
	StatusTurn motorStatus;//current motor status
	StatusTurn motorStatusMonitor;//desired value of motorStatus
	ufloat32 velocityValue;//current motor velocity
	ufloat32 velocityMonitor;//desired velocity for the motor
}Motor;
/*Structure for the sytem status*/
typedef struct{
	Buttons pressedButton;
	ProgrmaState currentState;
	Alarm alarm;
	Temperature temperature;
	Motor motor;
	ufloat32 frecuency;
}SystemStatus;//this type of struct contents the required system information

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function checks the interruption of the pressed buttons.
 	 \return void
 */
void checkButtons();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function is used for cleaning the monitor variables.
 	 This should be used if there were no changes made to the value variables.
 	 \return void
 */
void resetMonitors();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function changes the system status according to the pressed button and the current state.
 	 \return void
 */
void updateSystemState();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Used to receive the current system status.
 	 \return the current system status direction.
 */
SystemStatus* getSystemStatus();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function changes pressed button in the systemState variable.
 	 \param[in]  pressed indicates the pressed button captured in the interruption.
 	 \return void
 */
void setPressedButton(Buttons pressed);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function updates the alarm state.
 	 \param[in]  status new alarm status value (ON/OFF).
 	 \return void
 */
void changeAlarm(StatusTurn status);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function updates the velocity value when the temperature exceeds the limit.
 	 \return void
 */
void decreaseSpeed();

#endif /* STATUS_H_ */
