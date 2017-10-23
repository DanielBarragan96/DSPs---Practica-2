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
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;
	ADC0->CFG1 = ADC_CFG1_ADLPC(power)|ADC_CFG1_ADIV(div)|ADC_CFG1_ADLSMP(sample), ADC_CFG1_MODE(mode), ADC_CFG1_ADICLK(clk);
	ADC0->CFG2 |= ADC_CFG2_ADHSC(1);
	ADC0->SC3 =  ADC_SC3_AVGE_MASK|ADC_SC3_AVGS(3);
}

uint16 ADC_Values()
{
	uint16 values;
	//PTB2
	ADC0->SC1[0] = ADC_SC1_ADCH(0);
	while(0 == (ADC0->SC1[0] & ADC_SC1_COCO_MASK));
	values = ADC0->R[0];
	return values;
}

