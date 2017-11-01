/**
	\file
	\brief
		This is the starter file of FlexTimer.
		In this file the FlexTimer is configured in overflow mode.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	    Add configuration structures.
 */

#include "FlexTimer.h"
#include "MK64F12.h"
#include "NVIC.h"
#include "GPIO.h"
#include "PIT.h"
#include "States.h"

//  mod = #grande; chie

//static BooleanType CNSC_FLAG = FALSE;
static uint16 CNV_old = 0;
static uint16 CNV_new = 0;
static BooleanType Rise_flag = FALSE;
static uint16 MOD_count = 0;
static uint16 MOD_new = 0;
static uint16 MOD_old = 0;
//static ufloat32 periodo = 0;
static ufloat32 frecuencia = 0;

void FTM0_ISR()
{
	FTM0->SC &= ~FLEX_TIMER_TOF;
	GPIOD->PDOR ^= 0xFF;
}

void FlexTimer_updateCHValue(sint16 channelValue)
{
	/**Assigns a new value for the duty cycle*/
	FTM0->CONTROLS[0].CnV = channelValue;
}

void FTM2_ISR()
{
	FTM2->SC &= ~FLEX_TIMER_TOF;
	GPIOD->PDOR ^= 0xFF;
}

void FTM2_IRQHandler()
{
	//if we overflow with mod
	if(FTM2->SC & FTM_SC_TOF_MASK)
	{
		MOD_count++;
		FTM2->SC &= ~(FTM_SC_TOF_MASK);
	}
	//if we have an edge on the signal
	if(FTM2->CONTROLS[0].CnSC & FTM_CnSC_CHF_MASK)
    {
		if(FALSE == Rise_flag)
		{
			MOD_old = MOD_count;
			CNV_old = FTM2->CONTROLS[0].CnV;
			Rise_flag = TRUE;
		}else if(TRUE == Rise_flag){
			MOD_new = MOD_count;
			CNV_new = FTM2->CONTROLS[0].CnV;
			Rise_flag = FALSE;
			Frequency_Calc();
		}
		FTM2->CONTROLS[0].CnSC &= ~(FTM_CnSC_CHF_MASK);
	}
}

void Frequency_Calc()
{
	ufloat32 Ts_difference = 0;
	Ts_difference = ((MOD_new)*(FTM2->MOD)+CNV_new)-((MOD_old)*(FTM2->MOD)+CNV_old);
	frecuencia = (SYSTEM_CLOCK/2)/(Ts_difference*22.5);
	setFrequency(frecuencia);//set the new frequency value
}

void FlexTimer2_updateCHValue(sint16 channelValue)
{
	/**Assigns a new value for the duty cycle*/
	FTM2->CONTROLS[0].CnV = channelValue;
}

//  mod = #grande; chie

void FlexTimer2_Init()
{
		//GPIO_clockGating(GPIO_B);
	/** Clock gating for the FlexTimer 0*/
		SIM->SCGC6 |= FLEX_TIMER_2_CLOCK_GATING;
		SIM->SCGC3 |= SIM_SCGC3_FTM2_MASK;
		/**When write protection is enabled (WPDIS = 0), write protected bits cannot be written.
		* When write protection is disabled (WPDIS = 1), write protected bits can be written.*/
		FTM2->MODE |= FLEX_TIMER_WPDIS |FTM_MODE_FAULTM_MASK;
		/**Enables the writing over all registers*/
		FTM2->MODE &= ~FLEX_TIMER_FTMEN;
		FTM2->SC = 0x00;
		/**Configure the times*/
		FTM2->SC |= FLEX_TIMER_TOIE | FLEX_TIMER_CLKS_1|FLEX_TIMER_PS_128;
		FTM2->CNTIN = 0;
		FTM2->CNT = 0;
		FTM2->CONF |= FTM_CONF_BDMMODE(3);
		/**Selects the Edge-Aligned PWM mode mode*/
		FTM2->CONTROLS[0].CnSC |= FLEX_TIMER_ELSA | FLEX_TIMER_CHIE;
		FTM2->COMBINE = 0x00;
		/**Assigning a default value for modulo register*/
		FTM2->MOD = 0xFFFF;
		NVIC_enableInterruptAndPriotity(FTM2_IRQ, PRIORITY_4);
}

void FlexTimer_Init()
{
	/** Clock gating for the FlexTimer 0*/
		SIM->SCGC6 |= FLEX_TIMER_0_CLOCK_GATING;
		/**When write protection is enabled (WPDIS = 0), write protected bits cannot be written.
		* When write protection is disabled (WPDIS = 1), write protected bits can be written.*/
		FTM0->MODE |= FLEX_TIMER_WPDIS;
		/**Enables the writing over all registers*/
		FTM0->MODE &= ~FLEX_TIMER_FTMEN;
		/**Assigning a default value for modulo register*/
		FTM0->MOD = 0x00FF;
		/**Selects the Edge-Aligned PWM mode mode*/
		FTM0->CONTROLS[0].CnSC = FLEX_TIMER_MSB | FLEX_TIMER_ELSB;
		/**Assign a duty cycle of 50%*/
		FTM0->CONTROLS[0].CnV = (0X00FF);//initial value at zero, wait for changes in the velocity of the motor
		/**Configure the times*/
		FTM0->SC = FLEX_TIMER_CLKS_1|FLEX_TIMER_PS_128;
}
