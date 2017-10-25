/**
 * @file    Alarm.c
 * @brief   Control the alarm.
 * autor: Daniel Barragán
 */

#ifndef ALARM_H_
#define ALARM_H_

#include "DataTypeDefinitions.h"
#include "MK64F12.h"

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Verify if the alarm have to change it state, according to the read temperature.
 	 \return void
 */
void checkAlarm();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	reset the alarm decreased value.
 	 \return void
 */
void resetDecreaseQuantitie();

#endif
