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

//  mod = #grande; chie

static BooleanType CNSC_FLAG = FALSE;
static uint16 CNSC_VAL = 0;
static BooleanType OF_FLAG = FALSE;
static uint32 OF_VAL = 0;

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
	if(FTM2->SC & FTM_SC_TOF_MASK)
	{
		if(TRUE == CNSC_FLAG)
		{
			OF_FLAG++;
		}
		FTM2->SC &= ~(FTM_SC_TOF_MASK);
	}

	if(FTM2->CONTROLS[0].CnSC & FTM_CnSC_CHF_MASK)
    {

		CNSC_FLAG = TRUE;
		CNSC_VAL = FTM2->CONTROLS[0].CnV;
	}
	if(FTM2->SC | FTM_SC_TOF_MASK)
	{
		if(FTM2->STATUS & FTM_STATUS_CH0F_MASK)
		{
			FTM2->STATUS &= ~(FTM_STATUS_CH0F_MASK);
		}
	}
	FTM2->CONTROLS[0].CnSC &= ~(FTM_CnSC_CHF_MASK);

}

void FlexTimer2_updateCHValue(sint16 channelValue)
{
	/**Assigns a new value for the duty cycle*/
	FTM2->CONTROLS[0].CnV = channelValue;
}

//  mod = #grande; chie

void FlexTimer2_Init()
{
		GPIO_clockGating(GPIO_B);
	/** Clock gating for the FlexTimer 0*/
		SIM->SCGC6 |= FLEX_TIMER_2_CLOCK_GATING;
		SIM->SCGC3 |= SIM_SCGC3_FTM2_MASK;
		/**When write protection is enabled (WPDIS = 0), write protected bits cannot be written.
		* When write protection is disabled (WPDIS = 1), write protected bits can be written.*/
		FTM2->MODE |= FLEX_TIMER_WPDIS |FTM_MODE_FAULTM_MASK| FTM_MODE_FTMEN_MASK;
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
		FTM2->MOD = 0x00FF;
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
		FTM0->CONTROLS[0].CnV = (0);//initial value at zero, wait for changes in the velocity of the motor
		/**Configure the times*/
		FTM0->SC = FLEX_TIMER_CLKS_1|FLEX_TIMER_PS_128;
}
