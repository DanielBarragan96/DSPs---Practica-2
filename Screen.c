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
#include "Screen.h"
#include "GlobalFunctions.h"

void Screen_Config(ProgrmaState state)
{
	uint8 string1[]="ITESO"; /*! String to be printed in the LCD*/
	uint8 string2[]="uMs y DSPs"; /*! String to be printed in the LCD*/

	uint8 multi_perc[] = "%";
	uint8 multi_Cel[] = "'C";
	uint8 multi_Change[] = "(-)B1 (+)B2   (ok)B3";

	uint8 main_Vel[] = "Velocidad";
	uint8 main_Temp[] = "Temperatura";
	uint8 menu_Al[] = "1)Alarma";
	uint8 menu_For_Temp[] = "2)FormatoTemp";
	uint8 menu_Inc[] = "3)% de inc";
	uint8 menu_Ctrl[] = "4)Ctrl man";
	uint8 menu_Freq[] = "5)Frecuencimetro";
	uint8 sub1_Al[] = "Alarma";
	uint8 sub2_For_Temp[] = "Formato temp";
	uint8 sub2_Temp[] = "Temp=";
	uint8 sub2_Far[] = "'F";
	uint8 sub2_Change[] = "(C)B1 (F)B2 (ok)B3";
	uint8 sub3_Decre[] = "% de decre";
	uint8 sub3_Inc[] = "% de inc";
	uint8 sub4_Ctrl[] = "Ctrl manual";
	uint8 sub4_Change[] = "(on)B1      (off)B2     (ok)B3";
	uint8 sub4_Change2[] = "(-)B4 (+)B5";
	uint8 sub5_Freq[] = "Frecuencia";
	uint8 sub5_Hz[] = "(Hz)";

	switch(state)
	{
	case MAIN_STATE:
        LCDNokia_clear();
		LCDNokia_gotoXY(10,0);
		LCDNokia_sendString(main_Vel);
		delay(65000);
		LCDNokia_gotoXY(38,1);
		LCDNokia_sendString(multi_perc);
		delay(65000);
		LCDNokia_gotoXY(7,2);
		LCDNokia_sendString(main_Temp);
		delay(65000);
		LCDNokia_gotoXY(38,3);
		LCDNokia_sendString(multi_Cel);
		delay(65000);
	break;
	case MAIN_MENU_STATE:
		LCDNokia_clear();
		LCDNokia_gotoXY(0,0);
		LCDNokia_sendString(menu_Al);
		delay(65000);
		LCDNokia_gotoXY(0,1);
		LCDNokia_sendString(menu_For_Temp);
		delay(65000);
		LCDNokia_gotoXY(0,2);
		LCDNokia_sendString(menu_Inc);
		delay(65000);
		LCDNokia_gotoXY(0,3);
		LCDNokia_sendString(menu_Ctrl);
		delay(65000);
		LCDNokia_gotoXY(0,4);
		LCDNokia_sendString(menu_Freq);
		delay(65000);
	break;
	case ALARMA_STATE:
        LCDNokia_clear();
		LCDNokia_gotoXY(20,1);
		LCDNokia_sendString(sub1_Al);
		delay(65000);
		LCDNokia_gotoXY(40,2);
		LCDNokia_sendString(multi_Cel);
		delay(65000);
		LCDNokia_gotoXY(0,3);
		LCDNokia_sendString(multi_Change);
		delay(65000);
	break;
	case FORMAT_STATE:
		LCDNokia_clear();
		LCDNokia_gotoXY(0,1);
		LCDNokia_sendString(sub2_For_Temp);
		delay(65000);
		LCDNokia_gotoXY(5,2);
		LCDNokia_sendString(sub2_Temp);
		delay(65000);
		LCDNokia_gotoXY(62,2);
		LCDNokia_sendString(multi_Cel);
		delay(65000);
		LCDNokia_gotoXY(0,3);
		LCDNokia_sendString(sub2_Change);
		delay(65000);
	break;
	case CHANGE_STATE:
		LCDNokia_clear();
		LCDNokia_gotoXY(15,1);
		LCDNokia_sendString(sub3_Decre);
		delay(65000);
		LCDNokia_gotoXY(30,2);
		LCDNokia_sendString(multi_perc);
		delay(65000);
		LCDNokia_gotoXY(10,3);
		LCDNokia_sendString(multi_Change);
		delay(65000);
	break;
	case MANUAL_STATE:
		LCDNokia_clear();
		LCDNokia_gotoXY(20,0);
		LCDNokia_sendString(sub4_Ctrl);
		delay(65000);
		LCDNokia_gotoXY(30,1);
		LCDNokia_sendString(multi_perc);
		delay(65000);
		LCDNokia_gotoXY(7,2);
		LCDNokia_sendString(sub4_Change);
		delay(65000);
		LCDNokia_gotoXY(20,3);
		LCDNokia_sendString(sub4_Change2);
		delay(65000);
	break;
	case FRECUENCY_STATE:
		LCDNokia_clear();
		LCDNokia_gotoXY(20,1);
		LCDNokia_sendString(sub5_Freq);
		delay(65000);
		LCDNokia_gotoXY(25,2);
		LCDNokia_sendString(sub5_Hz);
		delay(65000);
	break;
	case ERROR_STATE:
		LCDNokia_clear();
	break;
	}
}
