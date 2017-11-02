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
#include "FlexTimer.h"
#include "MCG.h"
#define CLK_FREQ_HZ 50000000  /* CLKIN0 frequency */
#define SLOW_IRC_FREQ 32768	/*This is the approximate value for the slow irc*/
#define FAST_IRC_FREQ 4000000 /*This is the approximate value for the fast irc*/
#define EXTERNAL_CLOCK 0 /*It defines an external clock*/
#define PLL_ENABLE 1 /**PLL is enabled*/
#define PLL_DISABLE 0 /**PLL is disabled*/
#define CRYSTAL_OSC 1  /*It defines an crystal oscillator*/
#define LOW_POWER 0     /* Set the oscillator for low power mode */
#define SLOW_IRC 0 		/* Set the slow IRC */
#define CLK0_TYPE 0     /* Crystal or canned oscillator clock input */
#define PLL0_PRDIV 25    /* PLL predivider value */
#define PLL0_VDIV 30    /* PLL multiplier value*/

int main(void) {
	 int mcg_clk_hz;
   unsigned char modeMCG = 0;


#ifndef PLL_DIRECT_INIT
   mcg_clk_hz = fei_fbi(SLOW_IRC_FREQ,SLOW_IRC);// 64 Hz ---> 32768
   mcg_clk_hz = fbi_fbe(CLK_FREQ_HZ,LOW_POWER,EXTERNAL_CLOCK); // 97.656KHz ---> 50000000
   mcg_clk_hz = fbe_pbe(CLK_FREQ_HZ,PLL0_PRDIV,PLL0_VDIV);	// 97.656KHz ---> 50000000 and PLL is configured to generate 60000000
   mcg_clk_hz =  pbe_pee(CLK_FREQ_HZ);// 117.18 KHz ---> 60000000
#else
      mcg_clk_hz = pll_init(CLK_FREQ_HZ, LOW_POWER, EXTERNAL_CLOCK, PLL0_PRDIV, PLL0_VDIV, PLL_ENABLE);
#endif

   modeMCG = what_mcg_mode();

	initMain();//configure the Kinetis
	/**the first init is for the pwm and the second one is for the input capture*/
	FlexTimer_Init();//init for ftm0
	FlexTimer2_Init();//init for ftm2
	initStates();//initialize the temperature dependencies (velocity & current temperature)

	Screen_Config(MAIN_STATE);//set initial image of the screen
	checkMotor();//Initialize the PWM for the motor

    while(1) {//the systemStatus variable is located in States.c, and stores the system information.

    	if(NO_BUTTON != (getSystemStatus())->pressedButton) checkButtons();//check pressed buttons, which are handled in the interruption of the GPIO_C.

    	checkAlarm();//update the alarm status according to systemStatus.

    	//if the motor has the current motor speed do nothing
    	if(getMotorCurrentValue() != getSystemStatus()->motor.velocityValue && NO_BUTTON == getSystemStatus()->pressedButton) checkMotor();//check motor and adjust to the desired value in systemStatus variable.

    }
    return 0 ;
}
