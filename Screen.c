/*
 * Screen.c
 *
 *  Created on: 23/10/2017
 *      Author: ALEX
 */

#include "SPI.h"
#include "GPIO.h"
#include "DatatypeDefinitions.h"
#include "LCDNokia5110.h"
#include "States.h"

const SPI_ConfigType SPI_Config={SPI_DISABLE_FIFO,
							SPI_LOW_POLARITY,
							SPI_LOW_PHASE,
							SPI_MSB,
							SPI_0,
							SPI_MASTER,
							GPIO_MUX2,
							SPI_BAUD_RATE_2,
							SPI_FSIZE_8,
							{GPIO_D,BIT1,BIT2}};

void Screen_Config()
{
	const uint8 multi_perc[] = "%";
	const uint8 multi_Cel[] = "'C";
	const uint8 multi_Change[] = "(-)B1 (+)B2 (ok)B3";

	const uint8 main_Vel[] = "Velocidad";
	const uint8 main_Temp[] = "Temperatura";
	const uint8 menu_Al[] = "1) Alarma";
	const uint8 menu_For_Temp[] = "2) Formato temp";
	const uint8 menu_Inc[] = "3) % de inc";
	const uint8 menu_Ctrl[] = "4) Ctrl manual";
	const uint8 menu_Freq[] = "5) Frecuencímetro";
	const uint8 sub1_Al[] = "Alarma";
	const uint8 sub2_For_Temp[] = "Formato temp";
	const uint8 sub2_Temp[] = "Temp =";
	const uint8 sub2_Far[] = "'F";
	const uint8 sub2_Change[] = "(C)B1 (F)B2 (ok)B3";
	const uint8 sub3_Decre[] = "% de decre";
	const uint8 sub3_Inc[] = "% de inc";
	const uint8 sub4_Ctrl[] = "Ctrl manual";
	const uint8 sub4_Change[] = "(on)B1 (off)B2 (ok)B3";
	const uint8 sub4_Change2[] = "(-)B1 (+)B2";
	const uint8 sub4_Ctrl[] = "Ctrl manual";
	const uint8 sub5_Freq[] = "Frequencia";
	const uint8 sub5_Hz[] = "(Hz)";
}
