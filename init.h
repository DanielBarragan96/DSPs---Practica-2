/*
 * init.h
 *
 *  Created on: 16/09/2017
 *      Author: Daniel Barragán
 */

#ifndef INIT_H_
#define INIT_H_

#include "DataTypeDefinitions.h"
#include "SPI.h"

/** Constant that enable the clock of the DAC*/
#define DAC_SIM 0x1000U

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function initializes the necesary componentes of the Kinetis to start the program

 	 \return void
 */
void initMain();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function initializes the DAC so it can be used

 	 \return void
 */
void initDAC();


#endif /* INIT_H_ */
