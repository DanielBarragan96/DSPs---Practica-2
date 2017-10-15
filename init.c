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

void initMain(){
	/**Activating the clock gating of the GPIOs and the PIT*/
		GPIO_clockGating(GPIO_A);
		GPIO_clockGating(GPIO_B);
		GPIO_clockGating(GPIO_C);
		GPIO_clockGating(GPIO_D);
		GPIO_clockGating(GPIO_E);
		PIT_clockGating();

		/**Selected configurations*/
		GPIO_pinControlRegisterType pinControlRegisterMux1 = GPIO_MUX1;
		GPIO_pinControlRegisterType pinControlRegisterInputInterrupt = GPIO_MUX1|GPIO_PE|INTR_RISING_EDGE;
		GPIO_pinControlRegisterType pinControlRegisterInputInterruptPSFE = GPIO_MUX1|GPIO_PE|GPIO_PS|INTR_FALLING_EDGE;

		/**Configure the characteristics in the GPIOs*/
		GPIO_pinControlRegister(GPIO_B,BIT21,&pinControlRegisterMux1);
		GPIO_pinControlRegister(GPIO_B,BIT22,&pinControlRegisterMux1);
		GPIO_pinControlRegister(GPIO_E,BIT26,&pinControlRegisterMux1);
		GPIO_pinControlRegister(GPIO_C,BIT3,&pinControlRegisterInputInterrupt);
		GPIO_pinControlRegister(GPIO_D,BIT0,&pinControlRegisterMux1);
		GPIO_pinControlRegister(GPIO_D,BIT1,&pinControlRegisterMux1);
		GPIO_pinControlRegister(GPIO_D,BIT2,&pinControlRegisterMux1);
		GPIO_pinControlRegister(GPIO_D,BIT3,&pinControlRegisterMux1);
		GPIO_pinControlRegister(GPIO_C,BIT2,&pinControlRegisterMux1);
		GPIO_pinControlRegister(GPIO_A,BIT4,&pinControlRegisterInputInterruptPSFE);
		GPIO_pinControlRegister(GPIO_C,BIT6,&pinControlRegisterInputInterruptPSFE);
		GPIO_pinControlRegister(GPIO_A,BIT2,&pinControlRegisterMux1);
		GPIO_pinControlRegister(GPIO_A,BIT2,&pinControlRegisterMux1);
		GPIO_pinControlRegister(GPIO_C,BIT5,&pinControlRegisterMux1);
		GPIO_pinControlRegister(GPIO_C,BIT7,&pinControlRegisterMux1);
		GPIO_pinControlRegister(GPIO_C,BIT8,&pinControlRegisterMux1);
		GPIO_pinControlRegister(GPIO_C,BIT9,&pinControlRegisterMux1);


		/**Assigns a safe value to the output pin21 of the GPIOB*/
		GPIOB->PDOR |= 0x00200000;/**Blue led off*/
		GPIOB->PDOR |= 0x00400000;/**Read led off*/

		/**Configure Port Pins as input/output*/
		GPIO_dataDirectionPIN(GPIO_B,GPIO_OUTPUT,BIT21);
		GPIO_dataDirectionPIN(GPIO_B,GPIO_OUTPUT,BIT22);
		GPIO_dataDirectionPIN(GPIO_E,GPIO_OUTPUT,BIT26);
		GPIO_dataDirectionPIN(GPIO_C,GPIO_INPUT,BIT3);
		GPIO_dataDirectionPIN(GPIO_D,GPIO_INPUT,BIT0);
		GPIO_dataDirectionPIN(GPIO_D,GPIO_INPUT,BIT1);
		GPIO_dataDirectionPIN(GPIO_D,GPIO_INPUT,BIT2);
		GPIO_dataDirectionPIN(GPIO_D,GPIO_INPUT,BIT3);
		GPIO_dataDirectionPIN(GPIO_C,GPIO_OUTPUT,BIT2);
		GPIO_dataDirectionPIN(GPIO_C,GPIO_INPUT,BIT6);
		GPIO_dataDirectionPIN(GPIO_A,GPIO_INPUT,BIT4);
		GPIO_dataDirectionPIN(GPIO_A,GPIO_OUTPUT,BIT2);
		GPIO_dataDirectionPIN(GPIO_C,GPIO_OUTPUT,BIT5);
		GPIO_dataDirectionPIN(GPIO_C,GPIO_OUTPUT,BIT7);
		GPIO_dataDirectionPIN(GPIO_C,GPIO_OUTPUT,BIT8);
		GPIO_dataDirectionPIN(GPIO_C,GPIO_OUTPUT,BIT9);

		/**Sets the threshold for interrupts, if the interrupt has higher priority constant that the BASEPRI, the interrupt will not be attended*/
		NVIC_setBASEPRI_threshold(PRIORITY_5);
		/**Enables and sets a particular interrupt and its priority*/
		NVIC_enableInterruptAndPriotity(PIT_CH0_IRQ, PRIORITY_3);
		NVIC_enableInterruptAndPriotity(PIT_CH1_IRQ, PRIORITY_3);
		NVIC_enableInterruptAndPriotity(PIT_CH2_IRQ, PRIORITY_3);
		/**Enables and sets a particular interrupt and its priority*/
		NVIC_enableInterruptAndPriotity(PORTA_IRQ,PRIORITY_4);
		/**Enables and sets a particular interrupt and its priority*/
		NVIC_enableInterruptAndPriotity(PORTC_IRQ,PRIORITY_4);
		/**Enables and sets a particular interrupt and its priority*/
		NVIC_enableInterruptAndPriotity(PORTB_IRQ,PRIORITY_4);

		EnableInterrupts;
}

void initDAC(){
	PIT_clockGating();//enable usage of the PIT
	SIM->SCGC2 = DAC_SIM;//activates clock for use of PIT
	DAC0->C0 = 0xC0;//Resets DAC output value
}

