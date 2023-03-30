/*******************************************************************/
/*         UART Driver        */
/* Target:STM32F401CC                       */
/*Author :Yousef_Ahmed                         */
/*Date   :2023-03-28                                      */
/*******************************************************************/

#ifndef _UART_H
#define _UART_H

#define UART1_BASEADDRESS                       0x40011000
#define UART2_BASEADDRESS                       0x40004400
#define UART6_BASEADDRESS                       0x40011400

#define UART1                                   (void*)UART1_BASEADDRESS    //uart_Channel1  
#define UART2                                   (void*)UART2_BASEADDRESS    //uart_Channel2
#define UART6                                   (void*)UART6_BASEADDRESS    //uart_Channel3    

/***************************************control registers masks************************************************************/

#define uart_OVERSAMPLING_MODE_BY_16             0x00000000
#define uart_OVERSAMPLING_MODE_BY_8              0x00008000

#define uart_ENABLE_MASK                         0x00002000
#define uart_DISABLE_MASK                        0x00000000

#define uart_WORD_LENGTH_8BIT                    0x00000000
#define uart_WORD_LENGTH_9BIT                    0x00001000

#define uart_PARITY_CONTROL_ENABLE               0x00000400
#define uart_PARITY_CONTROL_DISABLE              0x00000000

#define uart_PARITY_SELECT_ODD                   0x00000200
#define uart_PARITY_SELECT_EVEN                  0x00000000

#define uart_PARITY_ERROR_INT_ENABLE             0x00000100
#define uart_PARITY_ERROR_INT_DISABLE            0x00000000

#define uart_TXE_INT_ENABLE                      0x00000080
#define uart_TXE_INT_DISABLE                     0x00000000

#define uart_TC_INT_ENABLE                       0x00000040
#define uart_TC_INT_DISABLE                      0x00000000

#define uart_RXNE_INT_ENABLE                     0x00000020
#define uart_RXNE_INT_DISABLE                    0x00000000

#define uart_IDLE_INT_ENABLE                     0x00000010
#define uart_IDLE_INT_DISABLE                    0x00000000

#define uart_TRANSMIT_ENABLE                     0x00000008
#define uart_TRANSMIT_DISABLE                    0x00000000

#define uart_RECIEVER_ENABLE                     0x00000004
#define uart_RECIEVER_DISABLE                    0x00000000


#define F_CLK                                   (u32)16000000

typedef struct{
    void* uart_Channel;
    u32 OverSampling;
    u32 Uart_enable;
    u32 Word_Length;
    u32 Parity;
    u32 Parity_Select;
    u32 Parity_ErrorInt;
    u32 TransmitRegisterEmpty_Int;
    u32 TransmitionComplete_Int;
    u32 RecieverDataReisterNotEmpty_Int;
    u32 TrasmitterEnable;
    u32 RecieverEnable;
    u32 BaudRate;          
}UART_cfg_t;

typedef enum{
    uart_Ok,
    uart_NotOk,
    uart_NullPtr,
}UART_enuError_t;


typedef enum{
    uart1_Channel,
    uart2_Channel,
    uart6_Channel,
    uart_ChannelNum
}UART_channel_t;


typedef struct{
    u8 *TxBuffer;
    u32 TxSize;
    u32 TxIdx;
    UART_channel_t Uart_Channel;
    void* Uart;
}UART_Send_cfg_t;

typedef struct{
    u8 *RxBuffer;
    u32 RxSize;
    u32 RxIdx;
    UART_channel_t Uart_Channel;
    void* Uart;
}UART_Reciever_cfg_t;

typedef enum{
    uart_Idle,
    uart_Busy
}UART_enuState;


typedef enum{
    Tx_Idle,
    Tx_Busy
}TX_enuState;

typedef enum{
    Rx_Idle,
    Rx_Busy
}RX_enuState;

typedef enum{
    uart_Transmit,
    uart_Recieve
}UART_Mode_t;

typedef void (*Uart_cbf)(void);

/*************************************************************************************************************************/
/* FunctionDiscription  : Starts the the Systick                                                                         */
/* Inputs  : void                                                                                                        */
/* Return :  void                                                                                                        */
/*************************************************************************************************************************/ 
extern UART_enuError_t uart_voidInit(UART_cfg_t* UART_cfg );
/*************************************************************************************************************************/
/* FunctionDiscription  : Starts the the Systick                                                                         */
/* Inputs  : void                                                                                                        */
/* Return :  void                                                                                                        */
/*************************************************************************************************************************/ 
extern UART_enuError_t uart_SendBufferAsynchZeroCopy(const UART_Send_cfg_t * Send_cfg);
/*************************************************************************************************************************/
/* FunctionDiscription  : Starts the the Systick                                                                         */
/* Inputs  : void                                                                                                        */
/* Return :  void                                                                                                        */
/*************************************************************************************************************************/ 
extern UART_enuError_t uart_RecieveBufferAsych(UART_Reciever_cfg_t * Reciever_cfg);
/*************************************************************************************************************************/
/* FunctionDiscription  : Starts the the Systick                                                                         */
/* Inputs  : void                                                                                                        */
/* Return :  void                                                                                                        */
/*************************************************************************************************************************/
extern UART_enuError_t uart_RegisterCallBackFunction(UART_channel_t Copy_enuChannel , UART_Mode_t Copy_enuMode  , Uart_cbf CallBackFunction);



#endif /*UART_H*/
