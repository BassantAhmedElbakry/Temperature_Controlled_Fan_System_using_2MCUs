/************************************************************************************************************
 *
 * Module: HMI_ECU
 *
 * File name : main.c
 *
 *  Created on: ٠٢‏/١١‏/٢٠٢٢
 *
 *  Author: BASSANT AHMED
 *
 ***********************************************************************************************************/

#include<avr/io.h>
#include <util/delay.h>
#include"common_macros.h"
#include"std_types.h"
#include"uart.h"
#include"gpio.h"
#include"dc.h"
#include"buzzer.h"
#include "LEDs.h"

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

UART_ConfigType UART_Config  = {9600,Asynchronous,BITS_8,BIT_1,Disabled};

/**********************************************************************************************************
 *                                            main function                                               *
 *********************************************************************************************************/

int main(){

	/*****************************************************************************************************
	 *                                          Local Variables                                          *
	 *****************************************************************************************************/

	/* Temperature according to temperature sensor */
	uint8 temperature = 0;

	/* The state --> Initialize is: The Normal state*/
	uint8 state = Normal_state;

	/*******************************************************************************************************
	 *                                          Initializations                                            *
	 ******************************************************************************************************/

	/*Initialize the UART*/
	UART_init(&UART_Config);

	/* Initialize the Buzzer */
	Buzzer_init();

	/*Initialize the DC-Motor*/
	DcMotor_init();

	/* Set LEDs pins as output pins*/
	LEDs_init();


	/*******************************************************************************************************
	 *                                            My System                                                *
	 *******************************************************************************************************/

	while(1){

		/* Receive the state from MUC1 */
		state = UART_recieveByte();

		/* Receive the temperature from MUC1 */
		temperature = UART_recieveByte();

		switch (state) {
		/*
		 * Emergency state:
		 * Turn on the LEDs die to temperature
		 * Buzzer is off
		 * Machine is on
		 */
		case Normal_state:
			/*Machine On*/
			DcMotor_Rotate(Clockwise);

			/* Turn the buzzer off */
			Buzzer_off();

			if(temperature < 30){
				/* Turn on the green LED & Turn off others*/
				LEDs_onOneLed(Green);
				LEDs_offOneLed(Red);
				LEDs_offOneLed(Yellow);
			}
			else if(temperature >=30 && temperature < 40){
				/* Turn on the yellow LED & Turn off others*/
				LEDs_onOneLed(Yellow);
				LEDs_offOneLed(Red);
				LEDs_offOneLed(Green);
			}
			else if(temperature >=40 && temperature < 50){
				/* Turn on the red LED & Turn off others*/
				LEDs_onOneLed(Red);
				LEDs_offOneLed(Green);
				LEDs_offOneLed(Yellow);
			}
			break;
			/*
			 * Emergency state:
			 * Blink LEDs
			 * Buzzer is on
			 * Machine is off
			 */
		case Emergency_state:
			/* Turn on the red LED & Turn off others*/
			LEDs_onOneLed(Red);
			LEDs_offOneLed(Green);
			LEDs_offOneLed(Yellow);

			/* TURN THE BUZZER ON */
			Buzzer_on();

			/*Machine OFF*/
			DcMotor_Rotate(Stop);

			break;
		default:
			/*Machine On*/
			DcMotor_Rotate(Clockwise);

			/* Turn the buzzer off */
			Buzzer_off();
			break;
		}

	}
	return 0;
}
