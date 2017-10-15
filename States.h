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
/*Type for the pressed button*/
typedef enum{ NO_BUTTON, B0, B1, B2, B3, B4, B5 }Buttons;
/*Type for the alarm status*/
typedef enum{ ALARM_OFF, ALARM_ON }AlarmStatus;
/*Type for the temperature type*/
typedef enum{ CELSIUS, FAHRENHEIT }DEGREES;
/*Type for the showed temperature*/
typedef struct{
	uint16 celsius;
	DEGREES typeDeegrees;
}Temperature;

/*Structure for the sytem status*/
typedef struct{
	Buttons pressedButton;
	ProgrmaState currentState;
	ProgrmaState screenState;
	AlarmStatus alarm;
	Temperature temperature;
	uint8 velocity;
	uint32 frecuency;
}SystemStatus;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This module checks the interruption of the pressed buttons.
 	 \return void
 */
void checkButtons();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This module changes the system status according to the pressed button and the current state.
 	 \return void
 */
void updateSystemState();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This module changes the screen information according to the currentState.
 	 \return void
 */
void updateScreen();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Used to receive the current system status.
 	 \return the current system status direction.
 */
SystemStatus* getSystemStatus();

#endif /* STATUS_H_ */
