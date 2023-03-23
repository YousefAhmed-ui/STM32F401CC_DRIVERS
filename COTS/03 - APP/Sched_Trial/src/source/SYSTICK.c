/******************************************************************/
/*SYSTICK Driver                */
/* Target:STM32F401CC                       */
/* Yousef_Ahmed                              */
/* Date:2023-03-09                                       */
/******************************************************************/
#include "STD_TYPES.h"
#include "SYSTICK.h"
/********************************Registers****************************************/

typedef struct{
    volatile u32 CTRL;
    volatile u32 LOAD;
    volatile u32 VAL;
    volatile u32 CALIB;
}STK_t;

#define   STK         ((volatile STK_t * const)0xE000E010)


/************************************************************************************/

#define MAX_TICKS                65536

/*************************************************************************************/
static STK_cbf stk_CallBabk;

void stk_Start(void)
{
    STK -> VAL = 0; 
    STK -> CTRL |= stk_ENABLE_MASK;
}

void stk_Stop(void)
{
    STK -> CTRL &= stk_DISABLE_MASK;
}

STKError_t stk_GetCurrentValue(u32 * Addp_CurrentValue)
{
    STKError_t Local_enuErrorStatus = stk_Ok;
    if(Addp_CurrentValue)
    {
        *Addp_CurrentValue = STK -> VAL;
    }
    else
    {
        Local_enuErrorStatus = stk_NullPtr;
    }
    return Local_enuErrorStatus;
}
STKError_t stk_SetPeriod_ms(u16 Copy_u16Period , u32 Copy_AHBClock)
{
    STKError_t Local_enuErrorStatus = stk_Ok;

    u32 Local_u32LoadReg = 0;

    if( Copy_u16Period > MAX_TICKS )
    {
        Local_enuErrorStatus = stk_NotOk;
    }
    else if( Copy_AHBClock > stk_AHB_CLOCK_PLL)
    {
        Local_enuErrorStatus = stk_NotOk;
    }
    else
    {
        if(STK -> CTRL & stk_CLOCK_SOURCE_AHB )
        {
            Local_u32LoadReg = (((u64)Copy_u16Period * (u64)Copy_AHBClock))/1000UL;
        }
        else
        {
            Local_u32LoadReg = (((u64)Copy_u16Period * (u64)Copy_AHBClock))/8000UL;
        }
    }
    STK -> LOAD = Local_u32LoadReg;

    return Local_enuErrorStatus;
}
STKError_t stk_SetTickTime(u32 Copy_u32Prescalar)
{
    STKError_t Local_enuErrorStatus = stk_Ok;

    u32 Local_u32Ctrl = 0;

    if( (Copy_u32Prescalar != stk_CLOCK_SOURCE_AHB) && (Copy_u32Prescalar != stk_CLOCK_SOURCE_AHB_DIVIDED_BY_8))
    {
        Local_enuErrorStatus = stk_NotOk;
    }
    else
    {
        Local_u32Ctrl = STK -> CTRL;
        Local_u32Ctrl &= stk_CLOCK_SOURCE_AHB_DIVIDED_BY_8;
        Local_u32Ctrl |= Copy_u32Prescalar;
        STK -> CTRL = Local_u32Ctrl;
    }
    return Local_enuErrorStatus;
}
STKError_t stk_SetCbf(STK_cbf STK_CallBackFunction)
{
	STKError_t Local_enuErrorStatus = stk_Ok;

    if(STK_CallBackFunction)
    {
        stk_CallBabk = STK_CallBackFunction;
    }
    else
    {
    	Local_enuErrorStatus = stk_NullPtr;
    }
    return Local_enuErrorStatus;
}
STKError_t stk_SetInterrupt(u8 Copy_u8Status)
{
    STKError_t Local_enuErrorStatus = stk_Ok;
    if((Copy_u8Status != stk_INT_ON) && (Copy_u8Status != stk_INT_OFF))
    {
        Local_enuErrorStatus = stk_NotOk;
    }
    else
    {
    	if(Copy_u8Status == stk_INT_ON)
    	{
    		STK -> CTRL |= stk_ENABLE_INT;
    	}
    	else
    	{
    		STK -> CTRL &= stk_DISABLE_INT;
    	}
    }
    return Local_enuErrorStatus;
}


void SysTick_Handler (void)
{
    if(stk_CallBabk)
    {
        stk_CallBabk();
    }
}
