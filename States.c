/**
 * @file    Status.c
 * @brief   Control the status of the system
 * autor: Daniel Barragán
 */

#include "DataTypeDefinitions.h"
#include "NVIC.h"
#include "GPIO.h"
#include "PIT.h"
#include "MK64F12.h"
#include "Motor.h"
#include "States.h"
#include "Screen.h"
#include "Alarm.h"
#include "ADC.h"
#include "FlexTimer.h"

static SystemStatus systemState = {//variable where we store the system states
		NO_BUTTON,
		MAIN_STATE,
		{OFF, 30, 30, 5, 5},
		{25, 77, CELSIUS, CELSIUS},
		{OFF, OFF, 80, 80},
		0	 //TODO check initial frequency
};

void initStates(){
		systemState.temperature.celsiusValue = convertRead();//Measured by the ADC
		systemState.temperature.fahrenheitValue = (systemState.temperature.celsiusValue*1.8)+32;//calculate the Fahrenheit value
		ufloat32 castingToFive = (5 + systemState.temperature.celsiusValue*(80/25));//calculate the velocity with initial condition: with 25°C Velocity = 80
		ufloat32 five = 5.0F;
		while(0 != ((uint16)castingToFive % (uint16)five)){//check if the velocity is a multiple of 5, or decrease its value until it is.
			castingToFive -=1;//decrease the velocity
		}
		systemState.motor.velocityValue = castingToFive;//Calculated with the temperature and a multiple of five
		systemState.motor.velocityMonitor = systemState.motor.velocityValue;//also update the monitor variable
		systemState.frecuency = GetFreq();
		//setMotorCurrentValue(systemState.motor.velocityValue);// update PWM value
}

void checkButtons(){
	GPIO_clearIRQStatus(GPIO_C);
	//if a button was pushed update the screen image.
	updateSystemState();
	Screen_Config(systemState.currentState);
	systemState.pressedButton = NO_BUTTON;//Clean the pressed button.
}

void updateSystemState(){
	//Depending on the pressed button and the state this switch will update the system information.
	switch(systemState.currentState){//TODO SCREENfirst check in which menu we are, then handle the input
		case MAIN_STATE:{
					if(B0 == systemState.pressedButton)//in the first case only if B0 was pressed...
							 systemState.currentState = MAIN_MENU_STATE;;//enter the MAIN_MENU_STATE
					return;
				}
		case MAIN_MENU_STATE:{
			//in this case we change the menu depending on the pressed switch
			switch(systemState.pressedButton){
				case B0:{//return to initial menu and resets the monitor
					systemState.currentState = MAIN_STATE;
					return;
				}
				case B1:{
					systemState.currentState = ALARMA_STATE;
					return;
				}
				case B2:{
					systemState.currentState = FORMAT_STATE;
					return;
				}
				case B3:{
					systemState.currentState = CHANGE_STATE;
					return;
				}
				case B4:{
					systemState.currentState = MANUAL_STATE;
					return;
				}
				case B5:{
					systemState.currentState = FRECUENCY_STATE;
					return;
				}
				case NO_BUTTON:
				default:{
					systemState.currentState = MAIN_STATE;
					return;
				}
			}
		}
		case ALARMA_STATE:{
			switch(systemState.pressedButton){
				case B0:{//return to initial menu and resets the monitor
					systemState.alarm.alarmMonitor= systemState.alarm.alarmaValue;;
					systemState.currentState = MAIN_MENU_STATE;
					return;
				}
				case B1:{//this decreases the alarm trigger by 1 degree (Celsius)
					systemState.alarm.alarmMonitor -= 1;
					return;
				}
				case B2:{//this decreases the alarm trigger by 1 degree (Fahrenheit)
					systemState.alarm.alarmMonitor += 1;
					return;
				}
				case B3:{//this updates the current alarm triggered value
					systemState.alarm.alarmaValue = systemState.alarm.alarmMonitor;
					resetDecreaseQuantitie();
					return;
				}
				case B4:
				case B5:
				case NO_BUTTON:
				default://if other buttons were press just return without making any changes
						return;
			}
		}
		case FORMAT_STATE:{
			switch(systemState.pressedButton){
				case B0:{//return to initial menu and resets the monitor
					systemState.temperature.typeDeegreesMonitor = systemState.temperature.typeDeegrees;
					systemState.currentState = MAIN_MENU_STATE;
					return;
				}
				case B1:{//change the Monitor value, which will set the actual value if B3 is pressed
					systemState.temperature.typeDeegreesMonitor = CELSIUS;
					return;
				}
				case B2:{//change the Monitor value, which will set the actual value if B3 is pressed
					systemState.temperature.typeDeegreesMonitor = FAHRENHEIT;
					systemState.temperature.fahrenheitValue = (1.8*systemState.temperature.fahrenheitValue)+32;
					return;
				}
				case B3:{//change the actual temperature format, which will be used in the screen module
					systemState.temperature.typeDeegrees = systemState.temperature.typeDeegreesMonitor;
					return;
				}
				case B4:
				case B5:
				case NO_BUTTON:
				default://if other buttons were press just return without making any changes
						return;
			}
		}
		case CHANGE_STATE:{
			switch(systemState.pressedButton){
				case B0:{//return to initial menu and resets the monitor
					systemState.alarm.decrementMonitor= systemState.alarm.decrementValue;
					systemState.currentState = MAIN_MENU_STATE;
					return;
				}
				case B1:{//this decreases the motor velocity motor by 5%
					systemState.alarm.decrementMonitor -= 5;
					if(VEL_LOW > systemState.alarm.decrementMonitor) systemState.alarm.decrementMonitor = 5;
					return;
				}
				case B2:{//this increases the motor velocity motor by 5%
					systemState.alarm.decrementMonitor += 5;
					if(VEL_MAX < systemState.alarm.decrementMonitor) systemState.alarm.decrementMonitor = 100;
					return;
				}
				case B3:{//sets the new velocity of the motor
					systemState.alarm.decrementValue = systemState.alarm.decrementMonitor;
					return;
				}
				case B4:
				case B5:
				case NO_BUTTON:
				default://if other buttons were press just return without making any changes
						return;
			}
		}
		case MANUAL_STATE:{
			switch(systemState.pressedButton){
							case B0:{//return to initial menu and resets the monitors
								resetMonitors();
								systemState.currentState = MAIN_MENU_STATE;
								return;
							}
							case B1:{//this sets to ON the state of the motor monitor
								systemState.motor.motorStatusMonitor = ON;
								return;
							}
							case B2:{//this sets to OFF the state of the motor monitor
								systemState.motor.motorStatusMonitor = OFF;
								return;
							}
							case B3:{//this updates the state of the motor using the monitor
								systemState.motor.motorStatus = systemState.motor.motorStatusMonitor;
								if(ON == systemState.motor.motorStatus)//If the motor is ON
									systemState.motor.velocityValue = systemState.motor.velocityMonitor;//update the velocity
								return;
							}
							case B4:{//this decreases the motor velocity motor by 5%
								if(!systemState.motor.motorStatusMonitor)
									return;
								systemState.motor.velocityMonitor -= 5;
								if(VEL_LOW > systemState.motor.velocityMonitor) systemState.motor.velocityMonitor = 5;
								return;
							}
							case B5:{//this increases the motor velocity motor by 5%
								if(!systemState.motor.motorStatusMonitor)
									return;
								systemState.motor.velocityMonitor += 5;
								if(VEL_MAX < systemState.motor.velocityMonitor) systemState.motor.velocityMonitor = 100;
								return;
							}
							case NO_BUTTON:
							default://if other buttons were press just return without making any changes
								return;
						}
		}
		case FRECUENCY_STATE:{
			if(B0 == systemState.pressedButton)//return to initial menu only if B0 was pressed
					 systemState.currentState = MAIN_MENU_STATE;
			return;
		}
		case ERROR_STATE:
		default: {//this cases meant there was a problem with the system, with this we can reset the screen
			systemState.currentState = MAIN_STATE;
			return;
		}
	}
}

void resetMonitors(){//resets all the monitors with the current states
	systemState.alarm.alarmMonitor = systemState.alarm.alarmaValue;
	systemState.temperature.typeDeegreesMonitor = systemState.temperature.typeDeegrees;
	systemState.motor.motorStatusMonitor = systemState.motor.motorStatus;
	systemState.motor.velocityMonitor = systemState.motor.velocityValue;
}

SystemStatus* getSystemStatus(){
	return &systemState;//get the direction of the system state variable
}

void setPressedButton(Buttons pressedBttn){
	systemState.pressedButton = pressedBttn;//set the currently pressed button
}
void changeAlarm(StatusTurn status){
	systemState.alarm.alarmStatus = status;//update alarm state
}
void decreaseSpeed(){
	systemState.motor.velocityValue -= systemState.alarm.decrementValue;//decreases motor speed
	if(VEL_LOW > systemState.motor.velocityValue) systemState.motor.velocityValue = 5;//if the velocity is minor than the limit reset
}
