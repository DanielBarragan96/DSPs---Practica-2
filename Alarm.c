/**
 * @file    Alarm.c
 * @brief   Control the alarm.
 * autor: Daniel Barragán
 */

#include "DataTypeDefinitions.h"
#include "GPIO.h"
#include "States.h"
#include "ADC.h"

ufloat32 decreaseQuantitie = 0;

void checkAlarm(){
	Alarm actualAlarm = (getSystemStatus())->alarm;
	ufloat32 measuredAlarm = setMeasuredValue();
	ufloat32 alarmLimit = getSystemStatus()->alarm.alarmaValue;
	//Verify if the alarm has to turn off
	//TODO Change to read the measurement of temperature
	if(alarmLimit > measuredAlarm){//actualStatus.alarm.alarmaValue >= (actualStatus.alarm.alarmaValue -1)
		if(ON == actualAlarm.alarmStatus){
			GPIO_clearPIN(GPIO_C, BIT10);
			changeAlarm(OFF);
		}
	}
	//TODO Change to read the measurement of temperature
	else if(alarmLimit <= measuredAlarm){
		if(OFF == actualAlarm.alarmStatus){
			GPIO_setPIN(GPIO_C, BIT10);
			changeAlarm(ON);
		}
		ufloat32 decreaseQuantitie2 = (uint32) (measuredAlarm-alarmLimit)/2;
		if(decreaseQuantitie2 > decreaseQuantitie){
			ufloat32 deltaQuantitie = decreaseQuantitie2 - decreaseQuantitie;
			decreaseQuantitie += deltaQuantitie;
			for(ufloat32 i = deltaQuantitie; i >= 1 ; i--){
				decreaseSpeed();
			}
		}
	}
}

void resetDecreaseQuantitie(){	decreaseQuantitie = 0;	}
