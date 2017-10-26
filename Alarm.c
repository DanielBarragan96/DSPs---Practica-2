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
uint8 measureLimiter = 0;

void checkAlarm(){
	//current values of alarm
	Alarm actualAlarm = (getSystemStatus())->alarm;
	ufloat32 measuredAlarm = setMeasuredValue();
	ufloat32 alarmLimit = getSystemStatus()->alarm.alarmaValue;
	//Verify if the alarm has to turn off
	if(alarmLimit > measuredAlarm){//actualStatus.alarm.alarmaValue >= (actualStatus.alarm.alarmaValue -1)
		if(ON == actualAlarm.alarmStatus){
			GPIO_clearPIN(GPIO_C, BIT10);//Turn off the alarm
			changeAlarm(OFF);
		}
	}
	else if(alarmLimit <= measuredAlarm){
		if(OFF == actualAlarm.alarmStatus){
			GPIO_setPIN(GPIO_C, BIT10);//Turn on the alarm
			changeAlarm(ON);
		}
		ufloat32 decreaseQuantitie2 = (uint32) (measuredAlarm-alarmLimit)/2;
		if(decreaseQuantitie2 > decreaseQuantitie){
			ufloat32 deltaQuantitie = decreaseQuantitie2 - decreaseQuantitie;//Difference with the current times that we decreased the motor speed
			decreaseQuantitie += deltaQuantitie;
			for(ufloat32 i = deltaQuantitie; i >= 1 ; i--){
				decreaseSpeed();//decrease the speed according to the motor
			}
		}
	}
	getSystemStatus()->temperature.celsiusValue = measuredAlarm;//update the measured value in the systemState
}

void resetDecreaseQuantitie(){	decreaseQuantitie = 0;	}//reset the decreased motor speed from the measured tempreature
