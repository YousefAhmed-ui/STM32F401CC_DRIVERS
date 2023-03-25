/******************************************************************/
/*HLCD Driver                 */
/* Target:STM32F401CC                       */
/* Yousef_Ahmed                               */
/* Date:2023-03-23                                       */
/******************************************************************/
#include "STD_TYPES.h"
#include "GPIO.h"
#include "HLCD.h"



const LCD_cfg_t LCD_Pins[LCD_PIN_NUMS] = {
    [LCD_RW_PIN] = {
        .LCD_u8Port = GPIO_PORTA,
        .LCD_u16Pin = gpio_PIN0,
        .LCD_Port = gpio_PORTA
    },
    [LCD_RS_PIN] = {
        .LCD_u8Port = GPIO_PORTA,
        .LCD_u16Pin = gpio_PIN1,
        .LCD_Port = gpio_PORTA
    },
    [LCD_ENABLE_PIN] = {
        .LCD_u8Port = GPIO_PORTA,
        .LCD_u16Pin = gpio_PIN2,
        .LCD_Port = gpio_PORTA
    },
    [LCD_D0_PIN] = {
        .LCD_u8Port = GPIO_PORTA,
        .LCD_u16Pin = gpio_PIN3,
        .LCD_Port = gpio_PORTA
    },
    [LCD_D1_PIN] = {
        .LCD_u8Port = GPIO_PORTA,
        .LCD_u16Pin = gpio_PIN4,
        .LCD_Port = gpio_PORTA
    },
    [LCD_D2_PIN] = {
        .LCD_u8Port = GPIO_PORTA,
        .LCD_u16Pin = gpio_PIN5,
        .LCD_Port = gpio_PORTA
    },
    [LCD_D3_PIN] = {
        .LCD_u8Port = GPIO_PORTA,
        .LCD_u16Pin = gpio_PIN6,
        .LCD_Port = gpio_PORTA
    },
    [LCD_D4_PIN] = {
        .LCD_u8Port = GPIO_PORTA,
        .LCD_u16Pin = gpio_PIN7,
        .LCD_Port = gpio_PORTA
    },
    [LCD_D5_PIN] = {
        .LCD_u8Port = GPIO_PORTA,
        .LCD_u16Pin = gpio_PIN8,
        .LCD_Port = gpio_PORTA
    },
    [LCD_D6_PIN] = {
        .LCD_u8Port = GPIO_PORTA,
        .LCD_u16Pin = gpio_PIN9,
        .LCD_Port = gpio_PORTA
    },
    [LCD_D7_PIN] = {
        .LCD_u8Port = GPIO_PORTA,
        .LCD_u16Pin = gpio_PIN10,
        .LCD_Port = gpio_PORTA
    },                    
};