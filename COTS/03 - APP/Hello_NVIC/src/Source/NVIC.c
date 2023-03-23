/******************************************************************/
/*NVIC Driver                */
/* Target:STM32F401CC                       */
/* Yousef_Ahmed                              */
/* Date:2023-03-02                                       */
/******************************************************************/
#include "STD_TYPES.h"
#include "NVIC.h"

#define RegSize     32

typedef struct{
   volatile u32 ISER[32];
   volatile u32 ICER[32];
   volatile u32 ISPR[32];
   volatile u32 ICPR[32];
   volatile u32 IABR[32];
   volatile u32 Reserved[32];
   volatile u8 IPR[240];
}NVIC_t;

#define NVIC           ((volatile NVIC_t * const)0xE000E100)
#define NVIC_STIR     *((volatile u32 * const)0xE000EF00)
#define SCB_AIRCR     *((volatile u32 * const)0xE000ED0C)

NVIC_enuError_t nvic_EnableIRQ(NVIC_IRQenu_t IRQn)
{
    NVIC_enuError_t Local_enuErrorStatus = nvic_OK;

    u8 Local_u8Bit = 0;

    u8 Local_u8RegNum = 0;

    if( IRQn > nvic_IRQ_num)
    {
        Local_enuErrorStatus = nvic_NotOk;
    }
    else
    {
        Local_u8Bit = IRQn % RegSize;

        Local_u8RegNum = IRQn / RegSize;

        NVIC -> ISER[Local_u8RegNum] |=(1<<Local_u8Bit);
    }

    return Local_enuErrorStatus;
}
NVIC_enuError_t nvic_DisableIRQ(NVIC_IRQenu_t IRQn)
{
    NVIC_enuError_t Local_enuErrorStatus = nvic_OK;

    u8 Local_u8Bit = 0;

    u8 Local_u8RegNum = 0;

    if( IRQn > nvic_IRQ_num)
    {
        Local_enuErrorStatus = nvic_NotOk;
    }
    else
    {
        Local_u8Bit = IRQn % RegSize;

        Local_u8RegNum = IRQn / RegSize;

        NVIC -> ICER[Local_u8RegNum] |=(1<<Local_u8Bit);
    }

    return Local_enuErrorStatus;
}
NVIC_enuError_t nvic_SetPendingIRQ(NVIC_IRQenu_t IRQn)
{
    NVIC_enuError_t Local_enuErrorStatus = nvic_OK;

    u8 Local_u8Bit = 0;

    u8 Local_u8RegNum = 0;

    if( IRQn > nvic_IRQ_num)
    {
        Local_enuErrorStatus = nvic_NotOk;
    }
    else
    {
        Local_u8Bit = IRQn % RegSize;

        Local_u8RegNum = IRQn / RegSize;

        NVIC -> ISPR[Local_u8RegNum] |=(1<<Local_u8Bit);
    }

    return Local_enuErrorStatus;
}    
NVIC_enuError_t nvic_ClearPendingIRQ(NVIC_IRQenu_t IRQn)
{
    NVIC_enuError_t Local_enuErrorStatus = nvic_OK;

    u8 Local_u8Bit = 0;

    u8 Local_u8RegNum = 0;

    if( IRQn > nvic_IRQ_num)
    {
        Local_enuErrorStatus = nvic_NotOk;
    }
    else
    {
        Local_u8Bit = IRQn % RegSize;

        Local_u8RegNum = IRQn / RegSize;

        NVIC -> ICPR[Local_u8RegNum] |=(1<<Local_u8Bit);
    }

    return Local_enuErrorStatus;    
}
NVIC_enuError_t nvic_GetActive(NVIC_IRQenu_t IRQn , u8 * Addp_ActiveIrq)
{
    NVIC_enuError_t Local_enuErrorStatus = nvic_OK;

    u8 Local_u8Bit = 0;

    u8 Local_u8RegNum = 0;

    if( IRQn > nvic_IRQ_num)
    {
        Local_enuErrorStatus = nvic_NotOk;
    }
    else if(Addp_ActiveIrq == NULL)
    {
        Local_enuErrorStatus = nvic_NotOk;
    }
    else
    {
        Local_u8Bit = IRQn % RegSize;

        Local_u8RegNum = IRQn / RegSize;

        *Addp_ActiveIrq = (((NVIC -> IABR[Local_u8RegNum]) >> Local_u8Bit) & 1) ;
    }

    return Local_enuErrorStatus; 

}
NVIC_enuError_t nvic_SetPriorityGrouping(u32 priority_grouping)
{
    NVIC_enuError_t Local_enuErrorStatus = nvic_OK;
    if( (priority_grouping < PRIORITY_GROUP_4_Sub_0) && (priority_grouping > PRIORITY_GROUP_0_SUB_4))
    {
        Local_enuErrorStatus = nvic_NotOk;
    }
    else
    {
        SCB_AIRCR = priority_grouping;
    }

    return Local_enuErrorStatus;
}
NVIC_enuError_t nvic_SetPriority(NVIC_IRQenu_t IRQn, u8 priority)
{
    NVIC_enuError_t Local_enuErrorStatus = nvic_OK;

    u8 Local_u8RegNum = 0;

    if( IRQn > nvic_IRQ_num)
    {
        Local_enuErrorStatus = nvic_NotOk;
    }
    else
    {

        NVIC -> IPR[IRQn]|= priority;
        
    }

    return Local_enuErrorStatus;

}
void __Enable_Irq()
{
    asm("CPSIE I");
}
void __Disable_Irq()
{
    asm("CPSID I");
}
void __Enable_fault_irq(void)
{
    asm("CPSIE F");
}
void __Disable_fault_irq(void)
{
    asm("CPSID F");
}
void __Set_BasePri(u8 Copy_u8Priority)
{
    __set_BASEPRI(Copy_u8Priority);
} 
