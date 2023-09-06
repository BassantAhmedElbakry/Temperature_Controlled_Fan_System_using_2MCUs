/*************************************************************************************************************
 * Module : PWM
 *
 * File name : pwm.h
 *
 * Description: Source file for the AVR PWM driver
 *
 * Author: BASSANT AHMED
 ************************************************************************************************************/

#include<avr/io.h>
#include"pwm.h"
#include"gpio.h"

/*************************************************************************************************************
 *                                         Functions Definitions                                             *
*************************************************************************************************************/

void PWM_Timer0_Start(uint8 control_speed){

	uint8 speed = 0;

	if(control_speed >= 20 && control_speed < 25){
		speed = 25;
	}
	else if(control_speed >= 25 && control_speed < 30){
		speed = 50;
	}
	else if(control_speed >= 30 && control_speed < 35){
		speed = 75;
	}
	else if(control_speed >= 35 && control_speed < 40){
		speed = 75;
	}
	else if(control_speed >= 40){
		speed = 100;
	}
	else{
		speed = 0;
	}

	TCNT0 = 0; /*Set Timer Initial value*/

	OCR0  = (255.0*speed) / 100.0 ; /*Set Compare Value*/

	/*set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.*/
	GPIO_setupPinDirection(PORT_B, PIN_3, OUTPUT_PIN);

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */

	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01) ;


}
