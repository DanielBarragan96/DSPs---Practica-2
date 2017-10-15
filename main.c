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
#include "MK64F12.h"
#include "init.h"
#include "States.h"


int main(void) {

	initMain();//configure the Kinetis

    while(1) {

    	if(TRUE == GPIO_getIRQStatus(GPIO_C)) checkButtons();//check pressed buttons if there was an interruption.

    }
    return 0 ;
}
