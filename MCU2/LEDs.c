/*************************************************************************************************************
 * Module : LEDs
 *
 * File name : LEDs.c
 *
 * Description: source file for the AVR LEDs driver
 *
 * Author: BASSANT AHMED
 ************************************************************************************************************/

#include <util/delay.h>
#include"LEDs.h"
#include "gpio.h"

/**********************************************************************************************************
 *                                        Functions Definitions                                           *
 *********************************************************************************************************/

/*
 * Setup the direction for the led pin as output pin through the GPIO driver
 * Turn off the led through the GPIO
 */
void LEDs_initOneLed(LEDs_color led){
	if(led == Red){
		GPIO_setupPinDirection(RED_LED_PORT, RED_LED_PIN, OUTPUT_PIN);
	}
	else if(led == Yellow){
		GPIO_setupPinDirection(YELLOW_LED_PORT, YELLOW_LED_PIN, OUTPUT_PIN);
	}
	else if(led == Green){
		GPIO_setupPinDirection(GREEN_LED_PORT, GREEN_LED_PIN, OUTPUT_PIN);
	}
}

/*
 * Setup the direction for all LEDs pins as output pins through the GPIO driver
 * Turn off all LEDs through the GPIO
 */
void LEDs_init(void){
	GPIO_setupPinDirection(RED_LED_PORT, RED_LED_PIN, OUTPUT_PIN);
	GPIO_setupPinDirection(YELLOW_LED_PORT, YELLOW_LED_PIN, OUTPUT_PIN);
	GPIO_setupPinDirection(GREEN_LED_PORT, GREEN_LED_PIN, OUTPUT_PIN);
}

#if (LOGIC == 0)
/*
 * Function to turn on one led through the GPIO
 */
void LEDs_onOneLed(LEDs_color led){
	if(led == Red){
		GPIO_writePin(RED_LED_PORT, RED_LED_PIN, HIGH);
	}
	else if(led == Yellow){
		GPIO_writePin(YELLOW_LED_PORT, YELLOW_LED_PIN, HIGH);
	}
	else if(led == Green){
		GPIO_writePin(GREEN_LED_PORT, GREEN_LED_PIN, HIGH);
	}
}

/*
 * Function to turn off one led through the GPIO
 */
void LEDs_offOneLed(LEDs_color led){
	if(led == Red){
		GPIO_writePin(RED_LED_PORT, RED_LED_PIN, LOW);
	}
	else if(led == Yellow){
		GPIO_writePin(YELLOW_LED_PORT, YELLOW_LED_PIN, LOW);
	}
	else if(led == Green){
		GPIO_writePin(GREEN_LED_PORT, GREEN_LED_PIN, LOW);
	}
}

/*
 * Function to turn on all LEDs through the GPIO
 */
void LEDs_on(void){
	GPIO_writePin(RED_LED_PORT, RED_LED_PIN, HIGH);
	GPIO_writePin(YELLOW_LED_PORT, YELLOW_LED_PIN, HIGH);
	GPIO_writePin(GREEN_LED_PORT, GREEN_LED_PIN, HIGH);
}

/*
 * Function to turn off all LEDs through the GPIO
 */
void LEDs_off(void){
	GPIO_writePin(RED_LED_PORT, RED_LED_PIN, LOW);
	GPIO_writePin(YELLOW_LED_PORT, YELLOW_LED_PIN, LOW);
	GPIO_writePin(GREEN_LED_PORT, GREEN_LED_PIN, LOW);
}



#else
/*
 * Function to turn on one led through the GPIO
 */
void LEDs_onOneLed(LEDs_color led){
	if(led == Red){
		GPIO_writePin(RED_LED_PORT, RED_LED_PIN, LOW);
	}
	else if(led == Yellow){
		GPIO_writePin(YELLOW_LED_PORT, YELLOW_LED_PIN, LOW);
	}
	else if(led == Green){
		GPIO_writePin(GREEN_LED_PORT, GREEN_LED_PIN, LOW);
	}
}

/*
 * Function to turn off one led through the GPIO
 */
void LEDs_offOneLed(LEDs_color led){
	if(led == Red){
		GPIO_writePin(RED_LED_PORT, RED_LED_PIN, HIGH);
	}
	else if(led == Yellow){
		GPIO_writePin(YELLOW_LED_PORT, YELLOW_LED_PIN, HIGH);
	}
	else if(led == Green){
		GPIO_writePin(GREEN_LED_PORT, GREEN_LED_PIN, HIGH);
	}
}

/*
 * Function to turn on all LEDs through the GPIO
 */
void LEDs_on(void){
	GPIO_writePin(RED_LED_PORT, RED_LED_PIN, LOW);
	GPIO_writePin(YELLOW_LED_PORT, YELLOW_LED_PIN, LOW);
	GPIO_writePin(GREEN_LED_PORT, GREEN_LED_PIN, LOW);
}

/*
 * Function to turn off all LEDs through the GPIO
 */
void LEDs_off(void){
	GPIO_writePin(RED_LED_PORT, RED_LED_PIN, HIGH);
	GPIO_writePin(YELLOW_LED_PORT, YELLOW_LED_PIN, HIGH);
	GPIO_writePin(GREEN_LED_PORT, GREEN_LED_PIN, HIGH);
}

#endif

/*
 * Function to blink led through the GPIO till specified time in msec
 */
void LEDs_blinkOneLed(LEDs_color led,uint16 duration){
	LEDs_onOneLed(led);
	_delay_ms(duration);
	LEDs_offOneLed(led);
}

/*
 * Function to blink all LEDs through the GPIO till specified time in msec
 */
void LEDs_blink(uint16 duration){
	LEDs_on();
	_delay_ms(duration);
	LEDs_off();
}
