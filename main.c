/**
 * @file    main.c
 * @brief   Application entry point.
 * Daniel Barragán Alvarez and Ávila Chavira Jorge Alejandro
 */

#include <stdio.h>
#include "DataTypeDefinitions.h"
#include "NVIC.h"
#include "GPIO.h"
#include "PIT.h"
#include "SPI.h"
#include "MK64F12.h"
#include "init.h"
#include "States.h"
#include "Alarm.h"

int main(void) {

	initMain();//configure the Kinetis
	SPI_init();

	updateScreen();

    while(1) {

    	if(TRUE == GPIO_getIRQStatus(GPIO_C)) checkButtons();//check pressed buttons if there was an interruption.

    	checkAlarm();
    }
    return 0 ;
}
