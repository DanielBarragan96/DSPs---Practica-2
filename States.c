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
		ALARM_OFF,
		{25, CELSIUS},
		80,
		0 //TODO check initial frecuency
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

		}
		case MAIN_MENU_STATE:{

		}
		case ALARMA_STATE:{

		}
		case FORMAT_STATE:{

		}
		case CHANGE_STATE:{

		}
		case MANUAL_STATE:{

		}
		case FRECUENCY_STATE:{

		}
		case ERROR_STATE:
		default: {
			systemState.currentState = MAIN_STATE;
			updateScreen();
		}
	}
}

void updateScreen(){
	//TODO change to SPI module
}

SystemStatus* getSystemStatus(){
	return &systemState;
}
