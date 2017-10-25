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

static uint8 conversion[6];

void float_String(ufloat32 fl)
{
	uint16 entero = (int)fl;
	ufloat32 flotante = (fl-entero)*100;
	uint16 helper = (int)flotante;
	uint16 centenas = 0;
	uint16 decenas = 0;
	uint16 unidades = 0;
	uint16 decimas = 0;
	uint16 centesimas = 0;

	centenas = (uint16) entero/100;
	entero = entero-(centenas*100);
	decenas = (uint16) entero/10;
	entero = entero-(decenas*10);
	unidades = entero;
	decimas = (uint16) helper/10;
	helper = helper-(decimas*10);
	centesimas = helper;

	centenas+=48;
	decenas+=48;
	unidades+=48;
	decimas+=48;
	centesimas+=48;

	conversion[0] = centenas;
	conversion[1] = decenas;
	conversion[2] = unidades;
	conversion[3] = '.';
	conversion[4] = decimas;
	conversion[5] = centesimas;
}

void Screen_Config(ProgrmaState state)
{

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
		float_String(getSystemStatus()->motor.velocityValue);
        LCDNokia_clear();
		LCDNokia_gotoXY(10,0);
		LCDNokia_sendString(main_Vel);
		delay(65000);
		LCDNokia_gotoXY(25,1);
		LCDNokia_sendString(conversion);
		delay(65000);
		LCDNokia_gotoXY(38,1);
		LCDNokia_sendString(multi_perc);
		delay(65000);
		LCDNokia_gotoXY(7,2);
		LCDNokia_sendString(main_Temp);
		delay(65000);
		float_String(getSystemStatus()->temperature.celsiusValue);
		LCDNokia_gotoXY(25,3);
		LCDNokia_sendString(conversion);
		delay(65000);
		LCDNokia_gotoXY(40,3);
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
		if((B2 | B1) == getSystemStatus()->pressedButton)
		{
			float_String(getSystemStatus()->alarm.alarmMonitor);
			LCDNokia_gotoXY(25,2);
			LCDNokia_sendString(conversion);
			delay(65000);
		}else{
			float_String(getSystemStatus()->alarm.alarmaValue);
			LCDNokia_gotoXY(25,2);
			LCDNokia_sendString(conversion);
			delay(65000);
		}
		LCDNokia_gotoXY(40,2);
		LCDNokia_sendString(multi_Cel);
		delay(65000);
		LCDNokia_gotoXY(0,3);
		LCDNokia_sendString(multi_Change);
		delay(65000);
	break;
	case FORMAT_STATE:
		if(CELSIUS == getSystemStatus()->temperature.typeDeegrees)
		{
			float_String(getSystemStatus()->temperature.celsiusValue);
			LCDNokia_clear();
			LCDNokia_gotoXY(0,1);
			LCDNokia_sendString(sub2_For_Temp);
			delay(65000);
			LCDNokia_gotoXY(5,2);
			LCDNokia_sendString(sub2_Temp);
			delay(65000);
			LCDNokia_gotoXY(40,2);
			LCDNokia_sendString(conversion);
			delay(65000);
			LCDNokia_gotoXY(62,2);
			LCDNokia_sendString(multi_Cel);
			delay(65000);
			LCDNokia_gotoXY(0,3);
			LCDNokia_sendString(sub2_Change);
			delay(65000);
		}
		else if(FAHRENHEIT == getSystemStatus()->temperature.typeDeegrees)
		{
			float_String(getSystemStatus()->temperature.fahrenheitValue);
			LCDNokia_clear();
			LCDNokia_gotoXY(0,1);
			LCDNokia_sendString(sub2_For_Temp);
			delay(65000);
			LCDNokia_gotoXY(5,2);
			LCDNokia_sendString(sub2_Temp);
			delay(65000);
			LCDNokia_gotoXY(40,2);
			LCDNokia_sendString(conversion);
			delay(65000);
			LCDNokia_gotoXY(62,2);
			LCDNokia_sendString(sub2_Far);
			delay(65000);
			LCDNokia_gotoXY(0,3);
			LCDNokia_sendString(sub2_Change);
			delay(65000);
		}
	break;
	case CHANGE_STATE:
		if(B1 == getSystemStatus()->pressedButton)
		{
			float_String(getSystemStatus()->alarm.decrementMonitor);
			LCDNokia_clear();
			LCDNokia_gotoXY(10,1);
			LCDNokia_sendString(sub3_Decre);
			delay(65000);
			LCDNokia_gotoXY(25,2);
			LCDNokia_sendString(conversion);
			delay(65000);
		}else if(B2 == getSystemStatus()->pressedButton){
			float_String(getSystemStatus()->alarm.decrementMonitor);
			LCDNokia_clear();
			LCDNokia_gotoXY(10,1);
			LCDNokia_sendString(sub3_Inc);
			delay(65000);
			LCDNokia_gotoXY(25,2);
			LCDNokia_sendString(conversion);
			delay(65000);
		}else{
			float_String(getSystemStatus()->alarm.decrementValue);
			LCDNokia_clear();
			LCDNokia_gotoXY(10,1);
			LCDNokia_sendString(sub3_Decre);
			delay(65000);
			LCDNokia_gotoXY(25,2);
			LCDNokia_sendString(conversion);
			delay(65000);
		}
			LCDNokia_gotoXY(45,2);
			LCDNokia_sendString(multi_perc);
			delay(65000);
			LCDNokia_gotoXY(0,3);
			LCDNokia_sendString(multi_Change);
			delay(65000);
	break;
	case MANUAL_STATE:
			LCDNokia_clear();
			LCDNokia_gotoXY(5,0);
			LCDNokia_sendString(sub4_Ctrl);
			delay(65000);
			if((B4|B5) == getSystemStatus()->pressedButton)
			{
			float_String(getSystemStatus()->motor.velocityMonitor);
			LCDNokia_gotoXY(30,1);
			LCDNokia_sendString(conversion);
			delay(65000);
			}else{
				float_String(getSystemStatus()->motor.velocityValue);
				LCDNokia_gotoXY(30,1);
				LCDNokia_sendString(conversion);
				delay(65000);
			}
		LCDNokia_gotoXY(50,1);
		LCDNokia_sendString(multi_perc);
		delay(65000);
		LCDNokia_gotoXY(0,2);
		LCDNokia_sendString(sub4_Change);
		delay(65000);
		LCDNokia_gotoXY(5,5);
		LCDNokia_sendString(sub4_Change2);
		delay(65000);
	break;
	case FRECUENCY_STATE:
		float_String(getSystemStatus()->frecuency);
		LCDNokia_clear();
		LCDNokia_gotoXY(10,1);
		LCDNokia_sendString(sub5_Freq);
		delay(65000);
		LCDNokia_gotoXY(28,2);
		LCDNokia_sendString(sub5_Hz);
		delay(65000);
		LCDNokia_gotoXY(20,3);
		LCDNokia_sendString(conversion);
		delay(65000);
	break;
	case ERROR_STATE:
		LCDNokia_clear();
	break;
	}
}
