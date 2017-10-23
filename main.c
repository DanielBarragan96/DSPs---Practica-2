/**
 * @file    main.c
 * @brief   Application entry point.
 * Daniel Barragán Alvarez and Ávila Chavira Jorge Alejandro
 */

#include <stdio.h>
#include "DataTypeDefinitions.h"
#include "GPIO.h"
#include "SPI.h"
#include "MK64F12.h"
#include "init.h"
#include "States.h"
#include "Alarm.h"

int main(void) {

	initMain();//configure the Kinetis
	SPI_init();//configure the SPI (screen)
	FlexTimer_Init();//configure the FlexTimer (motor)

	updateScreen();

    while(1) {

    	//if(TRUE == GPIO_getIRQStatus(GPIO_C))
    	checkButtons();//check pressed buttons, which are handled in the interruption of the GPIO_C.

    	checkAlarm();//update the alarm status.
    }
    return 0 ;
}
