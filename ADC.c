/*
 * ADC.c
 *
 *  Created on: 22/10/2017
 *      Author: ALEX
 */

#include "MK64F12.h"
#include "ADC.h"
#include "DataTypeDefinitions.h"

void ADC_init(ADC_CFG1_DLPC power, ADC_CFG1_ADIV div, ADC_CFG1_ADLSMP sample, ADC_CFG1_MODE mode, ADC_CFG1_ADICLK clk)
{
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;//starts clock gating for adc0
	ADC0->CFG1 = ADC_CFG1_ADLPC(power)|ADC_CFG1_ADIV(div)|ADC_CFG1_ADLSMP(sample)| ADC_CFG1_MODE(mode)| ADC_CFG1_ADICLK(clk);//paramaetric setup of config register 1
	ADC0->CFG2 |= ADC_CFG2_ADHSC(1); // high speed configuration on the config register 2
	ADC0->SC3 =  ADC_SC3_AVGE_MASK|ADC_SC3_AVGS(3); //enables the hardware average function and sets it in its fourth mode where it samples 32 times and makes the average
}

uint16 ADC_Values()
{
	uint16 values; //variable created to save adc read values
	//PTB2
	ADC0->SC1[0] = ADC_SC1_ADCH(0); // configures the channel for the adc
	while(0 == (ADC0->SC1[0] & ADC_SC1_COCO_MASK)); // comparison to see when the adc finished transmiting with its mask
	values = ADC0->R[0]; //assigns the read values to values
	return values;
}

