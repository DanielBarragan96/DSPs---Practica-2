/*
 * init.h
 *
 *  Created on: 17/09/2017
 *      Author: Daniel Barragán
 */

#include "DataTypeDefinitions.h"
#include "NVIC.h"
#include "GPIO.h"
#include "PIT.h"
#include "MK64F12.h"
#include "init.h"
#include "LCDNokia5110.h"
#include "ADC.h"
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

/** \brief This is the configuration structure to configure the LCD.
 * Note that is constants and it is because is only a variable used for configuration*/
const SPI_ConfigType SPI_Config = {
		SPI_DISABLE_FIFO,
		SPI_LOW_POLARITY,
		SPI_LOW_PHASE,
		SPI_MSB,
		SPI_0,
		SPI_MASTER,
		GPIO_MUX2,
		SPI_BAUD_RATE_2,
		SPI_FSIZE_8,
		{GPIO_D,BIT1,BIT2}};

void initMain(){

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

	/**Activating the clock gating of the GPIOs and the PIT*/
		GPIO_clockGating(GPIO_A);
		GPIO_clockGating(GPIO_B);
		GPIO_clockGating(GPIO_C);
		GPIO_clockGating(GPIO_D);
		GPIO_clockGating(GPIO_E);
		PIT_clockGating();

		/**configures both ptc1 and ptb18 in alt modes 3,4 respectively*/
		PORTC->PCR[1]   = PORT_PCR_MUX(0x4);
		PORTB->PCR[18]   = PORT_PCR_MUX(0x3);
		/**Selected configurations*/
		GPIO_pinControlRegisterType pinControlRegisterMux1 = GPIO_MUX1;
		GPIO_pinControlRegisterType pinControlRegisterInputInterrupt = GPIO_MUX1|GPIO_PE|INTR_RISING_EDGE;
		GPIO_pinControlRegisterType pinControlRegisterInputInterruptPSFE = GPIO_MUX1|GPIO_PE|GPIO_PS|INTR_FALLING_EDGE;

		/**Configure the characteristics in the GPIOs*/
		//LEDs
		GPIO_pinControlRegister(GPIO_B,BIT21,&pinControlRegisterMux1);
		GPIO_pinControlRegister(GPIO_B,BIT22,&pinControlRegisterMux1);
		GPIO_pinControlRegister(GPIO_E,BIT26,&pinControlRegisterMux1);
		//Buttons
		GPIO_pinControlRegister(GPIO_C,BIT5,&pinControlRegisterInputInterrupt);
		GPIO_pinControlRegister(GPIO_C,BIT7,&pinControlRegisterInputInterrupt);
		GPIO_pinControlRegister(GPIO_C,BIT0,&pinControlRegisterInputInterrupt);
		GPIO_pinControlRegister(GPIO_C,BIT9,&pinControlRegisterInputInterrupt);
		GPIO_pinControlRegister(GPIO_C,BIT3,&pinControlRegisterInputInterrupt);
		GPIO_pinControlRegister(GPIO_C,BIT2,&pinControlRegisterInputInterrupt);
		//Alarm
		GPIO_pinControlRegister(GPIO_C,BIT10,&pinControlRegisterMux1);
		//LM35
		GPIO_pinControlRegister(GPIO_B,BIT2,&pinControlRegisterMux1);

		/**Assigns a safe value to the output pin21 of the GPIOB*/
		GPIOB->PDOR |= 0x00200000;/**Blue led off*/
		GPIOB->PDOR |= 0x00400000;/**Red led off*/
		GPIOE->PDOR |= 0x04000000;/**Green led off*/

		/**Configure Port Pins as input/output*/
		//LEDs
		GPIO_dataDirectionPIN(GPIO_B,GPIO_OUTPUT,BIT21);
		GPIO_dataDirectionPIN(GPIO_B,GPIO_OUTPUT,BIT22);
		GPIO_dataDirectionPIN(GPIO_E,GPIO_OUTPUT,BIT26);
		//Buttons
		GPIO_dataDirectionPIN(GPIO_C,GPIO_INPUT,BIT5);
		GPIO_dataDirectionPIN(GPIO_C,GPIO_INPUT,BIT7);
		GPIO_dataDirectionPIN(GPIO_C,GPIO_INPUT,BIT0);
		GPIO_dataDirectionPIN(GPIO_C,GPIO_INPUT,BIT9);
		GPIO_dataDirectionPIN(GPIO_C,GPIO_INPUT,BIT3);
		GPIO_dataDirectionPIN(GPIO_C,GPIO_INPUT,BIT2);
		//Alarm
		GPIO_dataDirectionPIN(GPIO_C,GPIO_OUTPUT,BIT10);
		//LM35
		GPIO_dataDirectionPIN(GPIO_B,GPIO_INPUT,BIT2);

		/**Sets the threshold for interrupts, if the interrupt has higher priority constant that the BASEPRI, the interrupt will not be attended*/
		NVIC_setBASEPRI_threshold(PRIORITY_5);
		/**Enables and sets a particular interrupt and its priority*/
		NVIC_enableInterruptAndPriotity(PIT_CH0_IRQ, PRIORITY_3);
		/**Enables and sets a particular interrupt and its priority*/
		NVIC_enableInterruptAndPriotity(PORTC_IRQ,PRIORITY_4);

		/*! Configuration function for the LCD port*/
		SPI_init(&SPI_Config);
		/*! Configuration function for the LCD */
		LCDNokia_init();
		/*ADC initialize*/
		ADC_init(LOW_POWER, CLOCK1, S_LONG, ADC_16Bits, BUS_CLOCK);

		EnableInterrupts;
		/**the first init is for the pwm and the second one is for the input capture*/
		FlexTimer_Init();
		FlexTimer2_Init();

}

void initDAC(){
	PIT_clockGating();//enable usage of the PIT
	SIM->SCGC2 = DAC_SIM;//activates clock for use of PIT
	DAC0->C0 = 0xC0;//Resets DAC output value
}

