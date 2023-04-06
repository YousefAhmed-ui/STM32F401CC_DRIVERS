/*******************************************************************/
/*         CHAT_HANDLER Driver         */
/* Target:STM32F401CC                       */
/*Author :Yousef_Ahmed                         */
/*Date   :2023-04-04                                      */
/*******************************************************************/

#ifndef _CHAT_HANDLER_CFG_H
#define _CHAT_HANDLER_CFG_H

#include "UART.h"
#include "GPIO.h"

#define UART1_TX_PIN                          gpio_PIN6  
#define UART1_TX_PORT                         GPIO_PORTB
#define UART1_TX_MODE                         gpio_AF_PP_MODE
#define UART1_TX_SPEED                        gpio_MEDIUM_SPEED
#define UART1_TX_ALTERNATEFUNC                gpio_AF7_USART1_2

#define UART1_RX_PIN                          gpio_PIN7  
#define UART1_RX_PORT                         GPIO_PORTB
#define UART1_RX_MODE                         gpio_AF_PP_MODE
#define UART1_RX_SPEED                        gpio_MEDIUM_SPEED
#define UART1_RX_ALTERNATEFUNC                gpio_AF7_USART1_2


#define UART2_TX_PIN                          gpio_PIN2  
#define UART2_TX_PORT                         GPIO_PORTA
#define UART2_TX_MODE                         gpio_AF_PP_MODE
#define UART2_TX_SPEED                        gpio_MEDIUM_SPEED
#define UART2_TX_ALTERNATEFUNC                gpio_AF7_USART1_2

#define UART2_RX_PIN                          gpio_PIN3  
#define UART2_RX_PORT                         GPIO_PORTA
#define UART2_RX_MODE                         gpio_AF_PP_MODE
#define UART2_RX_SPEED                        gpio_MEDIUM_SPEED
#define UART2_RX_ALTERNATEFUNC                gpio_AF7_USART1_2

#define UART6_TX_PIN                          gpio_PIN11  
#define UART6_TX_PORT                         GPIO_PORTA
#define UART6_TX_MODE                         gpio_AF_PP_MODE
#define UART6_TX_SPEED                        gpio_MEDIUM_SPEED
#define UART6_TX_ALTERNATEFUNC                gpio_AF8_USART6

#define UART6_RX_PIN                          gpio_PIN12  
#define UART6_RX_PORT                         GPIO_PORTA
#define UART6_RX_MODE                         gpio_AF_PP_MODE
#define UART6_RX_SPEED                        gpio_MEDIUM_SPEED
#define UART6_RX_ALTERNATEFUNC                gpio_AF8_USART6

typedef enum{
    UART,
    SPI,
    Number_Of_Channels
}CHAT_HANDLER_Channel_t;

typedef struct{

    struct{             
    UART_cfg_t uart_cfg[uart_ChannelNum];
    GPIO_strInit_t uart_Tx_Pin[uart_ChannelNum];
    GPIO_strInit_t uart_Rx_Pin[uart_ChannelNum];
    }UART;
}CHAT_HANDLER_cfg_t;

#define CHANNEL     UART

#endif /*CHAT_HANDLER_CFG_H*/
