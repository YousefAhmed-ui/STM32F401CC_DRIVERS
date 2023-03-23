/*************************************************************************************************************************/
/* author : yousef ahmed                                                                                                 */
/* date   : 21/2/2023                                                                                                     */
/* version: V01                                                                                                          */
/*************************************************************************************************************************/ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO.h"
#include "HLED.h"

extern const LEDCfg_t led_cfg[LED_count];

LEDErrorStatus_t led_Init(void)
{
    LEDErrorStatus_t Local_enuErrorStatus = LED_Ok;
    u8 Local_u8Index = 0;
    GPIO_strInit_t gpio_cfg;

    for( Local_u8Index = 0 ; Local_u8Index < LED_count ; Local_u8Index++)
    {
        if( led_cfg[Local_u8Index].led_Otyper == gpio_OUPUT_PP_MODE)
        {
            gpio_cfg.GPIO_Mode = gpio_OUPUT_PP_MODE;
        }
        else
        {
            gpio_cfg.GPIO_Mode = gpio_OUPUT_OD_MODE;
        }
        gpio_cfg.GPIO_Pin = led_cfg[Local_u8Index].led_Pin;
        gpio_cfg.GPIO_Port = led_cfg[Local_u8Index].led_Port;
        gpio_cfg.GPIO_Speed = led_cfg[Local_u8Index].led_Speed;

        gpio_Init(&gpio_cfg);
    }
    return Local_enuErrorStatus;

}
LEDErrorStatus_t led_SetState(u16 Copy_Led , u8 Copy_State)
{
    LEDErrorStatus_t Local_ErrorStatus = LED_Ok;
    if( Copy_Led > LED_count )
    {
        Local_ErrorStatus = LED_NotOk;
    }
    else if( (Copy_State != led_ACTIVE_HIGH ) && (Copy_State != led_ACTIVE_LOW) )
    {
        Local_ErrorStatus = LED_NotOk;
    }
    else
    {
        gpio_SetPinValue(led_cfg[Copy_Led].LED_PORT , led_cfg[Copy_Led].led_Pin , led_cfg[Copy_Led].led_Mode ^ Copy_State );
    }
    return Local_ErrorStatus;

}
