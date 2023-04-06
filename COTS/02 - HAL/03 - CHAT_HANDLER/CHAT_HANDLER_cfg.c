/******************************************************************/
/*CHAT_HANDLER Driver                 */
/* Target:STM32F401CC                       */
/* Yousef_Ahmed                               */
/* Date:2023-04-04                                       */
/******************************************************************/
#include "CHAT_HANDLER.h"





const CHAT_HANDLER_cfg_t CHAT_cfg = {

    .UART = {
        
        .uart_cfg[uart2_Channel] = {
            .uart_voidPtr = UART2,
            .OverSampling = uart_OVERSAMPLING_MODE_BY_16,
            .Uart_enable = uart_ENABLE_MASK,
            .Word_Length = uart_WORD_LENGTH_8BIT,
            .Parity = uart_PARITY_CONTROL_DISABLE,
            .Parity_Select = uart_PARITY_SELECT_EVEN,
            .Parity_ErrorInt = uart_PARITY_ERROR_INT_DISABLE,
            .TransmitRegisterEmpty_Int = uart_TXE_INT_ENABLE,
            .TransmitionComplete_Int = uart_TC_INT_ENABLE,
            .RecieverDataReisterNotEmpty_Int = uart_RXNE_INT_ENABLE,
            .TrasmitterEnable = uart_TRANSMIT_ENABLE,
            .RecieverEnable = uart_RECIEVER_ENABLE,
            .BaudRate = (u32)9600,
            .StopBitsNumber = uart_STOP_BIT_1,
            .Uart_Channel = uart2_Channel
        },

        .uart_Rx_Pin[uart2_Channel] = {
            .GPIO_Mode = UART2_TX_MODE,
            .GPIO_Pin = UART2_TX_PIN,
            .GPIO_Port = UART2_TX_PORT,
            .GPIO_Speed = UART2_TX_SPEED,
            .GPIO_AlternateFunction = UART2_TX_ALTERNATEFUNC,
        },

        .uart_Rx_Pin[uart2_Channel] = {
            .GPIO_Mode = UART2_RX_MODE,
            .GPIO_Pin = UART2_RX_PIN,
            .GPIO_Port = UART2_RX_PORT,
            .GPIO_Speed = UART2_RX_SPEED,
            .GPIO_AlternateFunction = UART2_RX_ALTERNATEFUNC,
        }
    }
};