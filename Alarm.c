/**
 * @file    Alarm.c
 * @brief   Control the alarm.
 * autor: Daniel Barragán
 */

#include "DataTypeDefinitions.h"
#include "States.h"

void checkAlarm(){
	SystemStatus actualStatus = *(getSystemStatus());
	//Verify if the alarm has to turn off
	//TODO Change to read the measurement of temperature
	if(ON == actualStatus.alarm.alarmStatus && actualStatus.alarm.alarmaValue >= actualStatus.alarm.alarmaValue)
		changeAlarm(OFF);
	//TODO Change to read the measurement of temperature
	else if(OFF == actualStatus.alarm.alarmStatus && actualStatus.alarm.alarmaValue <= actualStatus.alarm.alarmaValue)
		changeAlarm(ON);
}
