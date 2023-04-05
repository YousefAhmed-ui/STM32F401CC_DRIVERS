/******************************************************************/
/*CHAT_HANDLER Driver                */
/* Target:STM32F401CC                       */
/* Yousef_Ahmed                              */
/* Date:2023-04-04                                       */
/******************************************************************/


#include "STD_TYPES.h"
#include "CHAT_HANDLER.h"

extern const CHAT_HANDLER_cfg_t CHAT_cfg[Number_Of_Channels];


void chat_handler_Init(void)
{
    #if CHANNEL == UART
        uart_voidInit(&CHAT_cfg[UART].uart_cfg);
        gpio_Init(&CHAT_cfg[UART].uart_Rx_Pin);
        gpio_Init(&CHAT_cfg[UART].uart_Tx_Pin);
    #endif
}

CHAT_HANDLER_Error_t chat_handler_SendMessage(u8 *Addp_Message)
{
    CHAT_HANDLER_Error_t Local_enuErrorStatus = chat_handler_Ok;

    u16 Local_u16Iterator = 0;

    if(Addp_Message == NULL){

        Local_enuErrorStatus = chat_handler_NullPtr;

    }else{

        while(Addp_Message[Local_u16Iterator] != '\0')
        {
            Local_u16Iterator++;
        }

        uart_SendBufferAsynchZeroCopy();


    }
}