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

ProgrmaState currentState = MAIN_STATE;

void verifyState(){
	switch(currentState){
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
		default:  return;
	}
}
