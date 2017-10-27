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
	/**Activating the clock gating of the GPIOs and the PIT*/
		GPIO_clockGating(GPIO_A);
		GPIO_clockGating(GPIO_B);
		GPIO_clockGating(GPIO_C);
		GPIO_clockGating(GPIO_D);
		GPIO_clockGating(GPIO_E);
		PIT_clockGating();

		//PWM output C1
		PORTC->PCR[1]   = PORT_PCR_MUX(0x4);
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
		ADC_init(LOW_POWER, CLOCK1, S_LONG, ADC_12Bits, BUS_CLOCK);

		EnableInterrupts;

}

void initDAC(){
	PIT_clockGating();//enable usage of the PIT
	SIM->SCGC2 = DAC_SIM;//activates clock for use of PIT
	DAC0->C0 = 0xC0;//Resets DAC output value
}

