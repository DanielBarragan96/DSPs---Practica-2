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

static uint8 conversion_f[6];  // string value we're gonna inyect into the screen when transforming from float to string
static uint8 conversion[2];  // string value we're gonna inyect into the screen when transforming from float to string

void float_String(ufloat32 fl)
{
	uint16 entero = (int)fl;	//makes cast to get the integer part of the float given

	/*uint values created to hold each character of the number*/
	uint16 decenas = 0;
	uint16 unidades = 0;

	/*while eliminating the biggest value of the whole number and the decimal part of the float it stores the value in the variables created*/
	decenas = (uint16) entero/10;
	entero = entero-(decenas*10);
	unidades = entero;

	/*ascii convertion of the numbers*/
	decenas+=48;
	unidades+=48;

	/*saves the value of the numbers on the conversion array*/
	conversion[0] = decenas;
	conversion[1] = unidades;
}

void float_String_F(ufloat32 fl)
{
	uint16 entero = (int)fl;	//makes cast to get the integer part of the float given
	ufloat32 flotante = (fl-entero)*100;//multiplies by 100 the float decimal value
	uint16 helper = (int)flotante;// makes cast to get get the integer part of the float decimals

	uint16 centenas = 0;
	uint16 decenas = 0;
	uint16 unidades = 0;
	uint16 decimas = 0;
	uint16 centesimas = 0;

	/*while eliminating the biggest value of the whole number and the decimal part of the float it stores the value in the variables created*/
	centenas = (uint16) entero/100;
	entero = entero-(centenas*100);
	decenas = (uint16) entero/10;
	entero = entero-(decenas*10);
	unidades = entero;
	decimas = (uint16) helper/10;
	helper = helper-(decimas*10);
	centesimas = helper;

	/*ascii convertion of the numbers*/
	centenas+=48;
	decenas+=48;
	unidades+=48;
	decimas+=48;
	centesimas+=48;

	/*saves the value of the numbers on the conversion array*/
	conversion_f[0] = centenas;
	conversion_f[1] = decenas;
	conversion_f[2] = unidades;
	conversion_f[3] = '.';
	conversion_f[4] = decimas;
	conversion_f[5] = centesimas;
}



void Screen_Config(ProgrmaState state)
{

	/*strings that hold the strings that will be inyected into the screen*/
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

	/*switch with the current state of our systemstatus*/
	switch(state)
	{
	case MAIN_STATE:
		float_String(getSystemStatus()->motor.velocityValue); //converts current motor value into a string
        LCDNokia_clear(); //clears the screen
		LCDNokia_gotoXY(10,0); //goes to a specific position where we're gonna put the string
		LCDNokia_sendString(main_Vel); // introduces the string
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
		float_String(getSystemStatus()->temperature.celsiusValue);// converts current celsius value into a string
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
		if((B2 == getSystemStatus()->pressedButton) || (B1 == getSystemStatus()->pressedButton)) // if either the b1 or the b2 were pressed shows the value the alarm is gonna be switched to instead of its current value
		{
	        LCDNokia_clear();
			LCDNokia_gotoXY(20,1);
			LCDNokia_sendString(sub1_Al);
			delay(65000);
			float_String(getSystemStatus()->alarm.alarmMonitor); // converts the value the alarm is gonna be switched to into a string
			LCDNokia_gotoXY(25,2);
			LCDNokia_sendString(conversion);
			delay(65000);
			LCDNokia_gotoXY(40,2);
			LCDNokia_sendString(multi_Cel);
			delay(65000);
			LCDNokia_gotoXY(0,3);
			LCDNokia_sendString(multi_Change);
			delay(65000);
		}else{
	        LCDNokia_clear();
			LCDNokia_gotoXY(20,1);
			LCDNokia_sendString(sub1_Al);
			delay(65000);
			float_String(getSystemStatus()->alarm.alarmaValue); // converts the current alarm value into a string
			LCDNokia_gotoXY(25,2);
			LCDNokia_sendString(conversion);
			delay(65000);
			LCDNokia_gotoXY(40,2);
			LCDNokia_sendString(multi_Cel);
			delay(65000);
			LCDNokia_gotoXY(0,3);
			LCDNokia_sendString(multi_Change);
			delay(65000);
		}
	break;
	case FORMAT_STATE:
		if(CELSIUS == getSystemStatus()->temperature.typeDeegrees) // if the current system value is celcius shows the current celcius value and its sign
		{
			float_String(getSystemStatus()->temperature.celsiusValue); // converts the current celcius value into a string
			LCDNokia_clear();
			LCDNokia_gotoXY(0,1);
			LCDNokia_sendString(sub2_For_Temp);
			delay(65000);
			LCDNokia_gotoXY(5,2);
			LCDNokia_sendString(sub2_Temp);
			delay(65000);
			LCDNokia_gotoXY(45,2);
			LCDNokia_sendString(conversion);
			delay(65000);
			LCDNokia_gotoXY(62,2);
			LCDNokia_sendString(multi_Cel);
			delay(65000);
			LCDNokia_gotoXY(0,3);
			LCDNokia_sendString(sub2_Change);
			delay(65000);
		}
		else if(FAHRENHEIT == getSystemStatus()->temperature.typeDeegrees) // if the current system value is fahrenheit shows the current fahrenheit value and its sign
		{

			float_String_F(getSystemStatus()->temperature.fahrenheitValue); // converts the current fahrenheit value into a string
			LCDNokia_clear();
			LCDNokia_gotoXY(0,1);
			LCDNokia_sendString(sub2_For_Temp);
			delay(65000);
			LCDNokia_gotoXY(20,2);
			LCDNokia_sendString(sub2_Temp);
			delay(65000);
			LCDNokia_gotoXY(20,3);
			LCDNokia_sendString(conversion_f);
			delay(65000);
			LCDNokia_gotoXY(62,3);
			LCDNokia_sendString(sub2_Far);
			delay(65000);
			LCDNokia_gotoXY(0,4);
			LCDNokia_sendString(sub2_Change);
			delay(65000);
		}
	break;
	case CHANGE_STATE:
		if(B1 == getSystemStatus()->pressedButton) // checks if we're decreasing to show we're decreasing the treshold and shows the value it's gonna be switched to
		{
			float_String(getSystemStatus()->alarm.decrementMonitor); // converts the value its gonna be switched to into a string
			LCDNokia_clear();
			LCDNokia_gotoXY(10,1);
			LCDNokia_sendString(sub3_Decre);
			delay(65000);
			LCDNokia_gotoXY(25,2);
			LCDNokia_sendString(conversion);
			delay(65000);
			LCDNokia_gotoXY(45,2);
			LCDNokia_sendString(multi_perc);
			delay(65000);
			LCDNokia_gotoXY(0,3);
			LCDNokia_sendString(multi_Change);
			delay(65000);
		}else if(B2 == getSystemStatus()->pressedButton){ //checks if we're increasing to show we're increasing the treshold and shows the value it's gonna be switched to
			float_String(getSystemStatus()->alarm.decrementMonitor); // converts the value its gonna be switched to into a string
			LCDNokia_clear();
			LCDNokia_gotoXY(10,1);
			LCDNokia_sendString(sub3_Inc);
			delay(65000);
			LCDNokia_gotoXY(25,2);
			LCDNokia_sendString(conversion);
			delay(65000);
			LCDNokia_gotoXY(45,2);
			LCDNokia_sendString(multi_perc);
			delay(65000);
			LCDNokia_gotoXY(0,3);
			LCDNokia_sendString(multi_Change);
			delay(65000);
		}else{ 													//if we haven't pressed any buttons shows the current value of the treshold
			float_String(getSystemStatus()->alarm.decrementValue); //converts the current value of the treshold into a string
			LCDNokia_clear();
			LCDNokia_gotoXY(10,1);
			LCDNokia_sendString(sub3_Decre);
			delay(65000);
			LCDNokia_gotoXY(25,2);
			LCDNokia_sendString(conversion);
			delay(65000);
			LCDNokia_gotoXY(45,2);
			LCDNokia_sendString(multi_perc);
			delay(65000);
			LCDNokia_gotoXY(0,3);
			LCDNokia_sendString(multi_Change);
			delay(65000);
		}
	break;
	case MANUAL_STATE:
			if((B4 == getSystemStatus()->pressedButton) || (B5 == getSystemStatus()->pressedButton)) // if either B4 or B5 we're pressed shows the value the motor is gonna be switched to
			{
				LCDNokia_clear();
				LCDNokia_gotoXY(5,0);
				LCDNokia_sendString(sub4_Ctrl);
				delay(65000);
				float_String(getSystemStatus()->motor.velocityMonitor); // converts value the motor is gonna be switched to into a string
				LCDNokia_gotoXY(30,1);
				LCDNokia_sendString(conversion);
				delay(65000);
				LCDNokia_gotoXY(50,1);
				LCDNokia_sendString(multi_perc);
				delay(65000);
				LCDNokia_gotoXY(0,2);
				LCDNokia_sendString(sub4_Change);
				delay(65000);
				LCDNokia_gotoXY(5,5);
				LCDNokia_sendString(sub4_Change2);
				delay(65000);
			}else{	// if we havent pressed anything shows the current motor value
				LCDNokia_clear();
				LCDNokia_gotoXY(5,0);
				LCDNokia_sendString(sub4_Ctrl);
				delay(65000);
				float_String(getSystemStatus()->motor.velocityValue);  // converts current motor value into string
				LCDNokia_gotoXY(30,1);
				LCDNokia_sendString(conversion);
				delay(65000);
				LCDNokia_gotoXY(50,1);
				LCDNokia_sendString(multi_perc);
				delay(65000);
				LCDNokia_gotoXY(0,2);
				LCDNokia_sendString(sub4_Change);
				delay(65000);
				LCDNokia_gotoXY(5,5);
				LCDNokia_sendString(sub4_Change2);
				delay(65000);
			}
	break;
	case FRECUENCY_STATE:
		float_String(getSystemStatus()->frecuency); // converts the frequency value into a string
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
