/*************************************************************************************************************************/
/* author : yousef ahmed                                                                                                 */
/* date   : 14/1/2022                                                                                                     */
/* version: V01                                                                                                          */
/*************************************************************************************************************************/ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "BIT_BAND.h"
/*********************************************Masks******************************************************************/

#define GPIO_PORTA                               0
#define GPIO_PORTB                               1
#define GPIO_PORTC                               2
#define GPIO_PORTD                               3
#define GPIO_PORTE                               4
#define GPIO_PORTH                               5

#define GPIOA_BASE_ADD                           0x40020000
#define GPIOB_BASE_ADD                           0x40020400
#define GPIOC_BASE_ADD                           0x40020800
#define GPIOD_BASE_ADD                           0x40020C00
#define GPIOE_BASE_ADD                           0x40021000
#define GPIOH_BASE_ADD                           0x40021C00

#define gpio_PORTA                               (void *)GPIOA_BASE_ADD
#define gpio_PORTB                               (void *)GPIOB_BASE_ADD
#define gpio_PORTC                               (void *)GPIOC_BASE_ADD
#define gpio_PORTD                               (void *)GPIOD_BASE_ADD
#define gpio_PORTE                               (void *)GPIOE_BASE_ADD
#define gpio_PORTH                               (void *)GPIOH_BASE_ADD

#define gpio_OUPUT_PP_MODE                       0b01000     
#define gpio_OUPUT_PP_PU_MODE                    0b01001     
#define gpio_OUPUT_PP_PD_MODE                    0b01010     
#define gpio_OUPUT_OD_MODE                       0b01100     
#define gpio_OUPUT_OD_PU_MODE                    0b01101
#define gpio_OUPUT_OD_PD_MODE                    0b01110

#define gpio_AF_PP_MODE                          0b10000
#define gpio_AF_PP_PU_MODE                       0b10001
#define gpio_AF_PP_PD_MODE                       0b10010
#define gpio_AF_OD_MODE                          0b10100
#define gpio_AF_OD_PU_MODE                       0b10101
#define gpio_AF_OD_PD_MODE                       0b10110

#define gpio_INPUT_FLOATING                      0b00000
#define gpio_INPUT_PU                            0b00001
#define gpio_INPUT_PD                            0b00010

#define gpio_ANALOG                              0b11000

#define gpio_LOW_SPEED                           0b00
#define gpio_MEDIUM_SPEED                        0b01
#define gpio_HIGH_SPEED                          0b10
#define gpio_VERY_HIGH_SPEED                     0b11

#define gpio_PIN0                               (u16)(0x0001)
#define gpio_PIN1                               (u16)(0x0002)
#define gpio_PIN2                               (u16)(0x0004)
#define gpio_PIN3                               (u16)(0x0008)
#define gpio_PIN4                               (u16)(0x0010)
#define gpio_PIN5                               (u16)(0x0020)
#define gpio_PIN6                               (u16)(0x0040)
#define gpio_PIN7                               (u16)(0x0080)
#define gpio_PIN8                               (u16)(0x0100)
#define gpio_PIN9                               (u16)(0x0200)
#define gpio_PIN10                              (u16)(0x0400)
#define gpio_PIN11                              (u16)(0x0800)
#define gpio_PIN12                              (u16)(0x1000)
#define gpio_PIN13                              (u16)(0x2000)
#define gpio_PIN14                              (u16)(0x4000)
#define gpio_PIN15                              (u16)(0x8000)

#define gpio_AF0_System                         0b0000
#define gpio_AF1_TIM1_TIM2						0b0001
#define gpio_AF2_TIM3_4_5                       0b0010
#define gpio_AF3_TIM9_10_11                     0b0011
#define gpio_AF4_I2C1_2_3                       0b0100
#define gpio_AF5_SPI1_2_3_4                     0b0101
#define gpio_AF6_SPI3                           0b0110
#define gpio_AF7_USART1_2                       0b0111
#define gpio_AF8_USART6                         0b1000
#define gpio_AF9_I2C2_3                         0b1001
#define gpio_AF10_OTG_FS                        0b1010
#define gpio_AF12_SDIO                          0b1100
#define gpio_AF15_EVENTOUT                      0b1111

#define MAX_PORT_NUM                            5
#define MAX_PIN_COUNT                           65536
#define GPIO_PIN_NUM                            16 
#define GPIO_SET_VALUE                          1
#define GPIO_RESET_VALUE                        0

/*********************************************Types*****************************************************************/
typedef struct {
    u8 GPIO_Mode;
    u8 GPIO_Port;
    u8 GPIO_Speed;
    u16 GPIO_Pin;
    u8 GPIO_AlternateFunction;
}GPIO_strInit_t;


typedef enum{
    GPIO_Ok,
    GPIO_NotOk
}GPIO_enuErrorStatus_t;
/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/
GPIO_enuErrorStatus_t gpio_Init(GPIO_strInit_t * Addp_PortInit);
/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/
GPIO_enuErrorStatus_t gpio_SetPinValue( void * Copy_voidPtrPort , u16 Copy_u16Pin , u8 Copy_u8PinValue );
/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/
GPIO_enuErrorStatus_t gpio_GetPinValue( u8 Copy_u8Port , u16 Copy_u16Pin , u8 * Addp_GetVal );
/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/
GPIO_enuErrorStatus_t gpio_SetPort( u8 Copy_u8Port , u16 Copy_u16Value);
