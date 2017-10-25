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
	ADC0->CFG2 |= ADC_CFG2_ADHSC(1);// high speed configuration on the config register 2
	ADC0->SC3 =  ADC_SC3_AVGE_MASK|ADC_SC3_AVGS(3);//enables the hardware average function and sets it in its fourth mode where it samples 32 times and makes the average
}

uint16 ADC_Values()
{
	uint16 values;//variable created to save adc read values
	//PTB2
	ADC0->SC1[0] = ADC_SC1_ADCH(0);// configures the channel for the adc
	while(0 == (ADC0->SC1[0] & ADC_SC1_COCO_MASK));// comparison to see when the adc finished transmiting with its mask
	values = ADC0->R[0];//assigns the read values to values
	return values;
}

ufloat32 setMeasuredValue(){
	ufloat32 adjustment = 10;
	uint16		a= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		b= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		c= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		d= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		e= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		f= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		g= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		h= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		i= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		j= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		k= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		l= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		m= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		n= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		o= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		p= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		q= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		r= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		s= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		t= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		u= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		v= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		w= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		x= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		y= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		z= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		aa= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		bb= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		cc= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		dd= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		ee= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			uint16		ff= (adjustment+(ADC_Values()*40/65535));
			for(uint32 i=0;i<65000;i++);
			return (a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z+aa+bb+cc+dd+ee+ff)/32;
}
