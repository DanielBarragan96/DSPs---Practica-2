/**
 * @file    main.c
 * @brief   Application entry point.
 * Daniel Barragán Alvarez and Ávila Chavira Jorge Alejandro
 */

#include <stdio.h>
#include "DataTypeDefinitions.h"
#include "GPIO.h"
#include "SPI.h"
#include "FlexTimer.h"
#include "MK64F12.h"
#include "init.h"
#include "States.h"
#include "Alarm.h"
#include "Motor.h"

int main(void) {

	initMain();//configure the Kinetis
	SPI_init();//configure the SPI (screen)
	FlexTimer_Init();//configure the FlexTimer (motor)

	updateScreen();//set initial image of the screen

    while(1) {//the systemStatus variable is located in States.c, and stores the system information.

    	if(NO_BUTTON != (getSystemStatus())->pressedButton) checkButtons();//check pressed buttons, which are handled in the interruption of the GPIO_C.

    	checkAlarm();//update the alarm status according to systemStatus.

    	checkMotor();//check motor and adjust to the desired value in systemStatus variable.
    }
    return 0 ;
}
//if(TRUE == GPIO_getIRQStatus(GPIO_C)) PORTC_IRQHandler();
