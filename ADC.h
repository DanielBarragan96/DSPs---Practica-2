/*
 * ADC.h
 *
 *  Created on: 22/10/2017
 *      Author: ALEX
 */

#ifndef ADC_H_
#define ADC_H_

#include "DataTypeDefinitions.h"

//To select low or normal power
typedef enum{
	NORMAL_POWER,
	LOW_POWER
}ADC_CFG1_DLPC;

//To select clk mode
typedef enum{
	CLOCK1,
	CLOCK2,
	CLOCK4,
	CLOCK8
}ADC_CFG1_ADIV;

//Type of sample time
typedef enum{
	S_SHORT,
	S_LONG
}ADC_CFG1_ADLSMP;

//to select bit mode
typedef enum{
	ADC_8Bits,
	ADC_12Bits,
	ADC_10Bits,
	ADC_16Bits
}ADC_CFG1_MODE;

typedef enum{
	BUS_CLOCK,
	AT_CLOCK_2,
	AT_CLOCK,
	AS_CLOCK
}ADC_CFG1_ADICLK;

void ADC_init(ADC_CFG1_DLPC power, ADC_CFG1_ADIV div, ADC_CFG1_ADLSMP sample, ADC_CFG1_MODE mode, ADC_CFG1_ADICLK clk);
uint16 ADC_Values();

#endif /* ADC_H_ */
