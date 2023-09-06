/*************************************************************************************************************
 * Module : LEDs
 *
 * File name : LEDs.h
 *
 * Description: header file for the AVR LEDs driver
 *
 * Author: BASSANT AHMED
 ************************************************************************************************************/

#ifndef LEDS_H_
#define LEDS_H_

#include"std_types.h"

/************************************************************************************************************
 *                                           Definitions                                                    *
 ***********************************************************************************************************/

// 0 --> Positive logic & 1 --> Negative logic
#define LOGIC 0

#define RED_LED_PORT     PORT_C
#define YELLOW_LED_PORT  PORT_C
#define GREEN_LED_PORT   PORT_C

#define RED_LED_PIN      PIN_0
#define YELLOW_LED_PIN   PIN_1
#define GREEN_LED_PIN    PIN_2

/**********************************************************************************************************
 *                                                Enums                                                   *
 *********************************************************************************************************/

typedef enum{
	Red,
	Yellow,
	Green
}LEDs_color;

/************************************************************************************************************
 *                                        Functions Prototypes                                              *
 ***********************************************************************************************************/

/*
 * Setup the direction for the led pin as output pin through the GPIO driver
 * Turn off the led through the GPIO
 */
void LEDs_initOneLed(LEDs_color led);

/*
 * Setup the direction for all LEDs pins as output pins through the GPIO driver
 * Turn off all LEDs through the GPIO
 */
void LEDs_init(void);

/*
 * Function to turn on one led through the GPIO
 */
void LEDs_onOneLed(LEDs_color led);

/*
 * Function to turn off one led through the GPIO
 */
void LEDs_offOneLed(LEDs_color led);

/*
 * Function to turn on all LEDs through the GPIO
 */
void LEDs_on(void);

/*
 * Function to turn off all LEDs through the GPIO
 */
void LEDs_off(void);

/*
 * Function to blink led through the GPIO till specified time in msec
 */
void LEDs_blinkOneLed(LEDs_color led,uint16 duration);

/*
 * Function to blink all LEDs through the GPIO till specified time in msec
 */
void LEDs_blink(uint16 duration);

#endif /* LEDS_H_ */
