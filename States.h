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

typedef enum{
	MAIN_STATE = 0,
	MAIN_MENU_STATE,
	ALARMA_STATE,
	FORMAT_STATE,
	CHANGE_STATE,
	MANUAL_STATE,
	FRECUENCY_STATE
}ProgrmaState;

void verifyState();


#endif /* STATUS_H_ */
