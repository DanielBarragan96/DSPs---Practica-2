/**
 * @file    Alarm.c
 * @brief   Control the alarm.
 * autor: Daniel Barragán
 */

#include "DataTypeDefinitions.h"
#include "GPIO.h"
#include "States.h"

ufloat32 decreaseQuantitie = 0;

void checkAlarm(){
	Alarm actualAlarm = (getSystemStatus())->alarm;
	ufloat32 measuredAlarm = 0;
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
		ufloat32 decreaseQuantitie2 = (alarmLimit-measuredAlarm)/2;
		if(decreaseQuantitie2 > decreaseQuantitie){
			decreaseQuantitie = decreaseQuantitie2 - decreaseQuantitie;
			for(ufloat32 i = decreaseQuantitie; i >= 1 ; i--){
				decreaseSpeed();
			}
		}
	}
}

void resetDecreaseQuantitie(){	decreaseQuantitie = 0;	}
