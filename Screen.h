/*
 * Screen.h
 *
 *  Created on: 23/10/2017
 *      Author: ALEX
 */

#ifndef SCREEN_H_
#define SCREEN_H_

static uint8 conversion[6]; // string value we're gonna inyect into the screen when transforming from float to string

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function changes a float variable into a string by decomposing the number and turning them to integers then converting them into their
 	 	 	 ascii equivalents and saving them into a string array
 	 \param[in]  float value thats gonna be converted into a string
 	 \return void
 */
void float_String(ufloat32 fl);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function updates the current strings shown in the nokia screen and switches between set menus
 	 \param[in]  current systemstatus state
 	 \return void
 */
void Screen_Config(ProgrmaState state);


#endif /* SCREEN_H_ */
