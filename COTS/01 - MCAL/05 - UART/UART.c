/******************************************************************/
/*UART Driver                */
/* Target:STM32F401CC                       */
/* Yousef_Ahmed                              */
/* Date:2023-03-28                                       */
/******************************************************************/
#include "STD_TYPES.h"
#include "UART.h"

#define uart_TXE_READ_MASK                      0x00000080     // transmit register empty   
#define uart_TC_READ_MASK                       0x00000040     // transmition complete   
#define uart_RXNE_READ_MASK                     0x00000020     // reciever data register not empty  
#define uart_IDLE_READ_MASK                     0x00000010     // IDLE flag  
#define uart_ORE_READ_MASK                      0x00000008     // overrun flag (aka) some data got lost  
#define uart_FE_READ_MASK                       0x00000002     // framing error  
#define uart_PE_READ_MASK                       0x00000001     // parity error 


static u32 my_ciel(f32 val);

typedef struct{
    u32 SR;
    u32 DR;
    u32 BRR;
    u32 CR1;
    u32 CR2;
    u32 CR3;
    u32 GTPR;

}UART_t;

#define UART1                      ((volatile UART_t *const)UART1_BASEADDRESS)
#define UART2                      ((volatile UART_t *const)UART2_BASEADDRESS)
#define UART6                      ((volatile UART_t *const)UART6_BASEADDRESS)

typedef struct{
    u32 Transmit_Compelete;
    u32 Transmit_Reg_Empty_Int;
    u32 Recieve_Reg_Full_Int;

}Interrupt_State_t;


static u8  uart_TxBusyFlag[uart_ChannelNum];
static u8* uart_Txbuffer[uart_ChannelNum];
static u8  uart_TxSize[uart_ChannelNum];
static u8  uart_TxBufferindex[uart_ChannelNum];


static Uart_cbf TxCallBack[uart_ChannelNum];

static u8  uart_RxBusyFlag[uart_ChannelNum];
static u8* uart_Rxbuffer[uart_ChannelNum];
static u8  uart_RxSize[uart_ChannelNum];
static u8  uart_RxBufferindex[uart_ChannelNum];


static Uart_cbf RxCallBack[uart_ChannelNum];

static Interrupt_State_t Interrupt;

UART_enuError_t uart_voidInit(UART_cfg_t* UART_cfg )
{
    UART_enuError_t Local_enuRes = uart_Ok;

    u32 Local_u32TmpValue = 0;
    u16 Local_u16TmpMantissa = 0;
    u16 Local_u16TmpFraction = 0;
    u32 Local_u32TmpCr1 = 0;

    if(UART_cfg == NULL)
    {
        Local_enuRes = uart_NullPtr;
    
    }else{
        if(UART_cfg -> OverSampling){

            Local_u32TmpValue = ((u64)(F_CLK) * 1000UL)/(8UL * UART_cfg -> BaudRate);

            Local_u16TmpFraction = ((Local_u32TmpValue % 1000) * 8) ;

            Local_u16TmpFraction = (u16)(my_ciel((f32)(Local_u16TmpFraction / 1000)));

            Local_u16TmpMantissa = Local_u32TmpValue / 1000;

            if(Local_u16TmpFraction > 0xF){

                Local_u16TmpMantissa += (Local_u16TmpFraction & 0xF0);         
            }

        }else{

            Local_u32TmpValue = ((u64)(F_CLK) * 1000UL)/(16UL * UART_cfg -> BaudRate);

            Local_u16TmpFraction = ((Local_u32TmpValue % 1000) * 16) ;

            Local_u16TmpFraction = (u16)(my_ciel((f32)(Local_u16TmpFraction / 1000)));

            Local_u16TmpMantissa = Local_u32TmpValue / 1000;

            if(Local_u16TmpFraction > 0xF){

                Local_u16TmpMantissa += (Local_u16TmpFraction & 0xF0);         
            }            
        }
                    
            ((UART_t *)(UART_cfg ->uart_Channel)) -> BRR = ((Local_u16TmpMantissa << 4) | (Local_u16TmpFraction & 0x0F));

            Local_u32TmpCr1 = ((UART_t *)(UART_cfg ->uart_Channel))-> CR1; 

            Local_u32TmpCr1 = 0;

            Local_u32TmpCr1 = UART_cfg->OverSampling | UART_cfg->Parity | UART_cfg->Parity_Select | UART_cfg->RecieverEnable | UART_cfg->TrasmitterEnable | UART_cfg->Word_Length | UART_cfg->Uart_enable;

            ((UART_t *)(UART_cfg ->uart_Channel))-> CR1 = Local_u32TmpCr1;

            Interrupt.Transmit_Compelete = UART_cfg->TransmitionComplete_Int;

            Interrupt.Transmit_Reg_Empty_Int = UART_cfg->TransmitRegisterEmpty_Int;

            Interrupt.Recieve_Reg_Full_Int = UART_cfg->RecieverDataReisterNotEmpty_Int;

            ((UART_t *)(UART_cfg ->uart_Channel))-> SR = 0;  
    }
    return Local_enuRes;
    
}

UART_enuError_t uart_SendBufferAsynchZeroCopy(const UART_Send_cfg_t * Send_cfg)
{
    UART_enuError_t Local_enuRes = uart_Busy;

    if(Send_cfg == NULL){

        Local_enuRes = uart_NotOk;
    
    }else{
        if(uart_TxBusyFlag == Tx_Idle)
        {
            uart_Txbuffer[Send_cfg->Uart_Channel] = Send_cfg->TxBuffer;

            uart_TxBufferindex[Send_cfg->Uart_Channel] = 0;

            uart_TxBusyFlag[Send_cfg->Uart_Channel] = uart_Busy;

            uart_TxSize[Send_cfg->Uart_Channel] = Send_cfg->TxSize;

            ((UART_t*)(Send_cfg->Uart))->DR = Send_cfg->TxBuffer[uart_TxBufferindex[Send_cfg->Uart_Channel]];

            ((UART_t*)(Send_cfg->Uart))->CR1 |= Interrupt.Transmit_Compelete;

            uart_TxBufferindex[Send_cfg->Uart_Channel]++;

            Local_enuRes = uart_Ok;

        }else{

            Local_enuRes = uart_Busy;
        }

    return Local_enuRes;

    }

 
}

UART_enuError_t uart_RecieveBufferAsych(UART_Reciever_cfg_t * Reciever_cfg)
{
    UART_enuError_t Local_enuRes = uart_Busy;

    if(Reciever_cfg == NULL)
    {
        Local_enuRes = uart_NullPtr;
    
    }else{

        if(uart_RxBusyFlag[Reciever_cfg->Uart_Channel] ==  uart_Idle){

            uart_Rxbuffer[Reciever_cfg->Uart_Channel] = Reciever_cfg->RxBuffer;

            uart_RxBufferindex[Reciever_cfg->Uart_Channel] = 0;

            uart_RxSize[Reciever_cfg->Uart_Channel] = 0;

            uart_RxBusyFlag[Reciever_cfg->Uart_Channel] = uart_Busy;

            ((UART_t*)(Reciever_cfg->Uart))->SR &= ~(uart_RXNE_READ_MASK) ;

            ((UART_t*)(Reciever_cfg->Uart))->CR1 |= Interrupt.Recieve_Reg_Full_Int;

            Local_enuRes = uart_Ok;

        }else{

            Local_enuRes = uart_Busy;

        }
        
        
    }

    return Local_enuRes;
}


UART_enuError_t uart_RegisterCallBackFunction(UART_channel_t Copy_enuChannel , UART_Mode_t Copy_enuMode  , Uart_cbf CallBackFunction)
{
    UART_enuError_t Local_enuRes = uart_Ok;

    if((Copy_enuChannel != uart1_Channel) && (Copy_enuChannel != uart2_Channel) && (Copy_enuChannel != uart6_Channel)){

        Local_enuRes = uart_NotOk;

    }else if(CallBackFunction == NULL){

        Local_enuRes = uart_NullPtr;

    }else{
        switch(Copy_enuMode){

        case uart_Transmit:
                          TxCallBack[Copy_enuChannel] = CallBackFunction;
        break;

        case uart_Recieve:
                          RxCallBack[Copy_enuChannel] = CallBackFunction;
        break;                                       

        }
    }

    return Local_enuRes;
}

void USART1_IRQHandler(void)
{
    if(UART1->SR & uart_TC_READ_MASK){
        if(uart_TxBufferindex[uart1_Channel] < uart_TxSize[uart1_Channel]){

            UART1->DR = uart_Txbuffer[uart_TxBufferindex[uart1_Channel]];

            uart_TxBufferindex[uart1_Channel]++;

            UART1->SR &= ~(uart_TC_READ_MASK);

        }else{

            uart_TxBusyFlag[uart1_Channel] = uart_Idle;

            uart_TxSize[uart1_Channel] = 0;

            if(TxCallBack[uart1_Channel]){

               TxCallBack[uart1_Channel]();
            }
            

            UART1->SR &= ~(uart_TC_READ_MASK);

        }
    }

    if((UART1->SR & uart_RXNE_READ_MASK) && (uart_RxBusyFlag == uart_Busy)){

        uart_Rxbuffer[uart_RxBufferindex[uart1_Channel]] = UART1->DR;

        uart_RxBufferindex[uart1_Channel]++;

        if(uart_RxBufferindex[uart1_Channel] == uart_RxSize[uart1_Channel])
        {
            uart_RxBusyFlag[uart1_Channel] = uart_Idle;

            UART1->CR1 &= ~(Interrupt.Recieve_Reg_Full_Int);

            UART1->SR &= ~(uart_RXNE_READ_MASK);

            uart_RxSize[uart1_Channel] = 0;

            if(RxCallBack[uart1_Channel]){

                RxCallBack[uart1_Channel]();
            }
        }


    }

}

void USART2_IRQHandler(void)
{
    if(UART2->SR & uart_TC_READ_MASK){
        if(uart_TxBufferindex[uart2_Channel] < uart_TxSize[uart2_Channel]){

            UART2->DR = uart_Txbuffer[uart_TxBufferindex[uart2_Channel]];

            uart_TxBufferindex[uart2_Channel]++;

            UART2->SR &= ~(uart_TC_READ_MASK);

        }else{

            uart_TxBusyFlag[uart2_Channel] = uart_Idle;

            uart_TxSize[uart2_Channel] = 0;

            if(TxCallBack[uart2_Channel]){

               TxCallBack[uart2_Channel]();
            }
            

            UART2->SR &= ~(uart_TC_READ_MASK);

        }
    }

    if((UART2->SR & uart_RXNE_READ_MASK) && (uart_RxBusyFlag[uart2_Channel] == uart_Busy)){

        uart_Rxbuffer[uart_RxBufferindex[uart2_Channel]] = UART2->DR;

        uart_RxBufferindex[uart2_Channel]++;

        if(uart_RxBufferindex[uart2_Channel] == uart_RxSize[uart2_Channel])
        {
            uart_RxBusyFlag[uart2_Channel] = uart_Idle;

            UART2->CR1 &= ~(Interrupt.Recieve_Reg_Full_Int);

            UART2->SR &= ~(uart_RXNE_READ_MASK);

            uart_RxSize[uart2_Channel] = 0;

            if(RxCallBack[uart2_Channel]){

                RxCallBack[uart2_Channel]();
            }
        }


    }    

}

void USART6_IRQHandler(void)
{
    if(UART6->SR & uart_TC_READ_MASK){
        if(uart_TxBufferindex[uart6_Channel] < uart_TxSize[uart6_Channel]){

            UART6->DR = uart_Txbuffer[uart_TxBufferindex[uart6_Channel]];

            uart_TxBufferindex[uart6_Channel]++;

            UART6->SR &= ~(uart_TC_READ_MASK);

        }else{

            uart_TxBusyFlag[uart6_Channel] = uart_Idle;

            uart_TxSize[uart6_Channel] = 0;

            if(TxCallBack[uart6_Channel]){

               TxCallBack[uart6_Channel]();
            }
            

            UART6->SR &= ~(uart_TC_READ_MASK);

        }
    }

    if((UART6->SR & uart_RXNE_READ_MASK) && (uart_RxBusyFlag[uart6_Channel] == uart_Busy)){

        uart_Rxbuffer[uart_RxBufferindex[uart6_Channel]] = UART6->DR;

        uart_RxBufferindex[uart6_Channel]++;

        if(uart_RxBufferindex[uart6_Channel] == uart_RxSize[uart6_Channel])
        {
            uart_RxBusyFlag[uart6_Channel] = uart_Idle;

            UART6->CR1 &= ~(Interrupt.Recieve_Reg_Full_Int);

            UART6->SR &= ~(uart_RXNE_READ_MASK);

            uart_RxSize[uart6_Channel] = 0;

            if(RxCallBack[uart6_Channel]){

                RxCallBack[uart6_Channel]();
            }
        }


    }
}
static u32 my_ciel(f32 val)
{
    u32 Local_u32Val = val;
    if((f32)Local_u32Val != val)
        return val+1;

    return val;   
}