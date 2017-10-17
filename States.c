/**
 * @file    Status.c
 * @brief   Control the status of the system
 * autor: Daniel Barragán
 */

#include "DataTypeDefinitions.h"
#include "NVIC.h"
#include "GPIO.h"
#include "PIT.h"
#include "MK64F12.h"
#include "States.h"

SystemStatus systemState = {
		NO_BUTTON,
		MAIN_STATE,
		ERROR_STATE,
		{ALARM_OFF,30,30},
		{25, 0, CELSIUS},
		{80,80},
		0	 //TODO check initial frecuency
};

void checkButtons(){
	//TODO check buttons interruptions.


	//if the screen state is different than the current state, update the screen image.
	if(systemState.currentState == systemState.screenState) updateScreen();
	//if a button was pushed update the screen image.
	if(NO_BUTTON != systemState.pressedButton){
		updateSystemState();
		updateScreen();
	}

}

void updateSystemState(){
	//Depending on the pressed button and the state this switch will update the system information.
	switch(systemState.screenState){
		case MAIN_STATE:{
					if(B0 == systemState.pressedButton)
							 systemState.currentState = MAIN_MENU_STATE;;
					return;
				}
		case MAIN_MENU_STATE:{
			switch(systemState.pressedButton){
				case B0:{
					systemState.currentState = MAIN_STATE;
					return;
				}
				case B1:{
					systemState.currentState = ALARMA_STATE;
					return;
				}
				case B2:{
					systemState.currentState = FORMAT_STATE;
					return;
				}
				case B3:{
					systemState.currentState = CHANGE_STATE;
					return;
				}
				case B4:{
					systemState.currentState = MANUAL_STATE;
					return;
				}
				case B5:{
					systemState.currentState = FRECUENCY_STATE;
					return;
				}
				case NO_BUTTON:
				default:{
					systemState.currentState = MAIN_STATE;
					return;
				}
			}
		}
		case ALARMA_STATE:{
			switch(systemState.pressedButton){
				case B0:{
					systemState.currentState = MAIN_STATE;
					return;
				}
				case B1:{
					systemState.alarm.alarmMonitor -= 1;
					return;
				}
				case B2:{
					systemState.alarm.alarmMonitor += 1;
					return;
				}
				case B3:{
					systemState.alarm.alarmaValue = systemState.alarm.alarmMonitor;
					return;
				}
				case B4:
				case B5:
				case NO_BUTTON:
				default:
						return;
			}
		}
		case FORMAT_STATE:{
			switch(systemState.pressedButton){
				case B0:{
					systemState.currentState = MAIN_STATE;
					return;
				}
				case B1:{

					return;
				}
				case B2:{

					return;
				}
				case B3:{

					return;
				}
				case B4:
				case B5:
				case NO_BUTTON:
				default:
						return;
			}
		}
		case CHANGE_STATE:{
			switch(systemState.pressedButton){
				case B0:{
					systemState.currentState = MAIN_STATE;
					return;
				}
				case B1:{

					return;
				}
				case B2:{

					return;
				}
				case B3:{

					return;
				}
				case B4:
				case B5:
				case NO_BUTTON:
				default:
						return;
			}
		}
		case MANUAL_STATE:{

		}
		case FRECUENCY_STATE:{
			if(B0 == systemState.pressedButton)
					 systemState.currentState = MAIN_STATE;;
			return;
		}
		case ERROR_STATE:
		default: {
			systemState.currentState = MAIN_STATE;
			return;
		}
	}
}

void updateScreen(){
	//TODO change to SPI module
}

SystemStatus* getSystemStatus(){
	return &systemState;
}
