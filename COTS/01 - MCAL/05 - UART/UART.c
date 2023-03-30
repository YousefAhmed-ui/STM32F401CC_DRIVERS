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

            

            ((UART_t *)(UART_cfg ->uart_Channel)) -> BRR = ((Local_u16TmpMantissa << 4) | (Local_u16TmpFraction & 0x0F));

            Local_u32TmpCr1 = ((UART_t *)(UART_cfg ->uart_Channel))-> CR1; 
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