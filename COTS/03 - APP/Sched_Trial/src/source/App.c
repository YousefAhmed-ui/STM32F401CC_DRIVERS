/*
 * App.c
 *
 *  Created on: ??�/??�/????
 *      Author: El-Wattaneya
 */

#include "App.h"
#include "GPIO.h"
#include "HLED.h"


void Led1(void)
{
	led_Toggle(LED_Start);

}

void Led2(void)
{
	led_Toggle(LED_Buzzer);
}

void Led3(void)
{
	led_Toggle(LED_Notify);
}
