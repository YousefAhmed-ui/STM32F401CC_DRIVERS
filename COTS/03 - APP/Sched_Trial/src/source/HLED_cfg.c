/*************************************************************************************************************************/
/* author : yousef ahmed                                                                                                 */
/* date   : 21/2/2022                                                                                                    */
/* version: V01                                                                                                          */
/*************************************************************************************************************************/ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO.h"
#include "HLED.h"

const LEDCfg_t led_cfg[LED_count] = {
    [LED_Start] = {
        .led_Mode = led_ACTIVE_HIGH,
        .led_Otyper = gpio_OUPUT_PP_MODE,
        .led_Pin = gpio_PIN13,
        .led_Port = GPIO_PORTC,
		.LED_PORT = gpio_PORTC,
        .led_Speed = led_MEDIUM_SPEED
    },
    [LED_Buzzer] = {
        .led_Mode = led_ACTIVE_HIGH,
        .led_Otyper = gpio_OUPUT_PP_MODE,
        .led_Pin = gpio_PIN14,
        .led_Port = GPIO_PORTC,
        .LED_PORT = gpio_PORTC,
        .led_Speed = led_MEDIUM_SPEED
    },
	[LED_Notify] = {
	    .led_Mode = led_ACTIVE_HIGH,
	    .led_Otyper = gpio_OUPUT_PP_MODE,
	    .led_Pin = gpio_PIN15,
	    .led_Port = GPIO_PORTC,
	    .LED_PORT = gpio_PORTC,
	    .led_Speed = led_MEDIUM_SPEED
	}

};
