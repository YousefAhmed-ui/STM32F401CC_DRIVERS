/******************************************************************/
/*CHAT_HANDLER Driver                */
/* Target:STM32F401CC                       */
/* Yousef_Ahmed                              */
/* Date:2023-04-04                                       */
/******************************************************************/


#include "STD_TYPES.h"
#include "CHAT_HANDLER.h"


static UART_Send_cfg_t Uart_Send_cfg[uart_ChannelNum];

static UART_channel_t Uart_Channel;

extern const CHAT_HANDLER_cfg_t CHAT_cfg[Number_Of_Channels];


void chat_handler_Init(void)
{
    u8 Local_u8Idx = 0;

    #if CHANNEL == UART

        for(Local_u8Idx = 0 ; Local_u8Idx < uart_ChannelNum ; Local_u8Idx++){

            uart_voidInit(&CHAT_cfg[UART].uart_cfg[Local_u8Idx]);

            gpio_Init(&CHAT_cfg[UART].uart_Rx_Pin[Local_u8Idx]);

            gpio_Init(&CHAT_cfg[UART].uart_Tx_Pin[Local_u8Idx]);

        }

    
    #endif

    #if CHANNEL == SPI

    #endif
}

CHAT_HANDLER_Error_t chat_handler_SendMessage(u8 *Addp_Message , u8 Channel , u8 Copy_u8ChannelNum , chat_handler_cbf Notify)
{

    #if CHANNEL == UART

        CHAT_HANDLER_Error_t Local_enuErrorStatus = chat_handler_Ok;

        u16 Local_u16Iterator = 0;

        if((Addp_Message == NULL) || (Notify == NULL)){

            Local_enuErrorStatus = chat_handler_NullPtr;

        }else if(Copy_u8ChannelNum > uart_ChannelNum){

            Local_enuErrorStatus = chat_handler_NotOk;

        }else{

            while(Addp_Message[Local_u16Iterator] != '\0'){

                Local_u16Iterator++;
            }

            Uart_Send_cfg[CHAT_cfg[Channel].uart_cfg[Copy_u8ChannelNum].uart_channel].TxBuffer = Addp_Message;

            Uart_Send_cfg[Copy_u8ChannelNum].TxIdx = 0;

            Uart_Send_cfg[Copy_u8ChannelNum].TxSize = (Local_u16Iterator+1);

            Uart_Send_cfg[Copy_u8ChannelNum].Uart = CHAT_cfg[Channel].uart_cfg[Copy_u8ChannelNum].uart_voidPtr;

            Uart_Send_cfg[Copy_u8ChannelNum].Uart_Channel = Copy_u8ChannelNum;

            uart_SendBufferAsynchZeroCopy(&Uart_Send_cfg);


        }

    #endif

    return Local_enuErrorStatus;    
}