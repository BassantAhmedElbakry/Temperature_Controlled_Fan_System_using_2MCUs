/************************************************************************************************************
 *
 * Module: MCU1
 *
 * File name : main.c
 *
 *  Author: BASSANT AHMED
 *
 ***********************************************************************************************************/

#include<avr/io.h>
#include <util/delay.h>
#include"common_macros.h"
#include"std_types.h"
#include"uart.h"
#include "external_eeprom.h"
#include "dc.h"
#include "twi.h"
#include "adc.h"
#include "lm35_sensor.h"

/**********************************************************************************************************
 *                                                Enums                                                   *
 *********************************************************************************************************/

typedef enum{
	Normal_state,
	Emergency_state
}States;

/*********************************************************************************************************
 *                                             Configurations                                            *
 *********************************************************************************************************/

UART_ConfigType UART_Config ={9600,Asynchronous,BITS_8,BIT_1,Disabled};
TWI_ConfigType  TWI_Ptr = {400000,0x01};
ADC_ConfigType ADC_Configure = {AVCC_Internal_2_56v,N8};

/**********************************************************************************************************
 *                                            main function                                               *
 *********************************************************************************************************/

int main(){

	/*******************************************************************************************************
	 *                                          Local Variables                                            *
	 *******************************************************************************************************/

	/* Temperature according to temperature sensor */
	uint8 temperature = 0;

	/* The state --> Initialize is: The Normal state*/
	uint8 state = Normal_state;

	/*******************************************************************************************************
	 *                                          Initializations                                            *
	 *******************************************************************************************************/

	/*Initialize the DC-Motor*/
	DcMotor_init();

	/*Initialize the UART*/
	UART_init(&UART_Config);

	/*Initialize the I2C*/
	TWI_init(&TWI_Ptr);

	/*Initializations*/
	ADC_init(&ADC_Configure);

	/*Initialize the state to Normal state*/
	EEPROM_writeByte(0x0311,Normal_state);
	_delay_ms(10);

	/*******************************************************************************************************
	 *                                            My System                                                *
	 *******************************************************************************************************/

	while(1){

		/* Check the state */
		EEPROM_readByte(0x0311,&state);
		_delay_ms(10);

		/* Sending the state to MUC2*/
		UART_sendByte(state);

		/* Reading the temperature */
		temperature = LM35_getTemperature();

		/* Sending the temperature to MUC2 */
		UART_sendByte(temperature);

		switch (state) {
			/*
		 	 * Normal state:
		 	 * Fan is off if temperature < 20
		 	 * else it is on and its speed increasing die to temperature increasing
		     */
		case Normal_state:
			if(temperature < 20){
				DcMotor_Rotate(Stop,0);
			}
			else if(temperature >=20 && temperature < 30){
				DcMotor_Rotate(Clockwise,temperature);
			}
			else if(temperature >=30 && temperature < 40){
				DcMotor_Rotate(Clockwise,temperature);
			}
			else if(temperature >=40 && temperature < 50){
				DcMotor_Rotate(Clockwise,temperature);
			}
			else if(temperature >= 50){
				DcMotor_Rotate(Clockwise,temperature);
				EEPROM_writeByte(0x0311,Emergency_state);
				_delay_ms(10);
			}
			break;
			/*
			 * Emergency state:
			 * Fan is on with max speed
			 */
		case Emergency_state:
			DcMotor_Rotate(Clockwise,temperature);
			if(temperature < 50) {
				EEPROM_writeByte(0x0311,Normal_state);
				_delay_ms(10);
			}
			else{
				EEPROM_writeByte(0x0311,Emergency_state);
				_delay_ms(10);
			}
			break;
		default:
			EEPROM_writeByte(0x0311,Normal_state);
			_delay_ms(10);
			break;
		}

	}

	return 0;
}
