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
#include "ADC.h"
#include "Screen.h"
#include "Motor.h"

int main(void) {

	initMain();//configure the Kinetis
	FlexTimer_Init();//configure the FlexTimer (motor)
	initStates();//initialize the temperature dependencies (velocity & current temperature)

	//updateScreen();//set initial image of the screen
	Screen_Config(MAIN_STATE);
	checkMotor();

    while(1) {//the systemStatus variable is located in States.c, and stores the system information.

    	if(NO_BUTTON != (getSystemStatus())->pressedButton) checkButtons();//check pressed buttons, which are handled in the interruption of the GPIO_C.

    	checkAlarm();//update the alarm status according to systemStatus.

    	//if the motor has the current motor speed do nothing
    	if(getMotorCurrentValue() != getSystemStatus()->motor.velocityValue && NO_BUTTON == getSystemStatus()->pressedButton) checkMotor();//check motor and adjust to the desired value in systemStatus variable.

    	//ADC_Values();//check the LM35 temperature.
    }
    return 0 ;
}
