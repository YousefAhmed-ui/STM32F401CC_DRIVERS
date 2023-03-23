#include "RCC.h"


/**********************Register******************************/
#define     RCC_CR              *((volatile u32 * )0x40023800)
#define     RCC_PLLCFGR         *((volatile u32 * )0x40023804)
#define     RCC_CFGR            *((volatile u32 * )0x40023808)
#define     RCC_CIR             *((volatile u32 * )0x4002380C)
#define     RCC_AHB1RSTR        *((volatile u32 * )0x40023810)
#define     RCC_AHB2RSTR        *((volatile u32 * )0x40023814)
#define     RCC_APB1RSTR        *((volatile u32 * )0x40023820)
#define     RCC_APB2RSTR        *((volatile u32 * )0x40023824)
#define     RCC_AHB1ENR         *((volatile u32 * )0x40023830)
#define     RCC_AHB2ENR         *((volatile u32 * )0x40023834)
#define     RCC_APB1ENR         *((volatile u32 * )0x40023840)
#define     RCC_APB2ENR         *((volatile u32 * )0x40023844)
#define     RCC_AHB1LPENR       *((volatile u32 * )0x40023850)
#define     RCC_AHB2LPENR       *((volatile u32 * )0x40023854)
#define     RCC_APB1LPENR       *((volatile u32 * )0x40023860)
#define     RCC_APB2LPENR       *((volatile u32 * )0x40023864)
#define     RCC_BDCR            *((volatile u32 * )0x40023870)
#define     RCC_CSR             *((volatile u32 * )0x40023874)
#define     RCC_SSCGR           *((volatile u32 * )0x40023880)
#define     RCC_PLLI2SCFGR      *((volatile u32 * )0x40023884)
#define     RCC_DCKCFGR         *((volatile u32 * )0x4002388C)


/************************************MASKS*****************************/




#define GET_SYS_CLOCK_MASK       0x0000000C
#define HSI_ON_MASK              0x00000001
#define HSE_ON_MASK              0x00010000
#define PLL_ON_MASK              0x01000000
 
#define HSI_RDY_MASK             0x00000002
#define HSE_RDY_MASK             0x00020000
#define PLL_RDY_MASK             0x02000000


#define SW_CLEAR_MASK            0xFFFFFFFC
#define SWS_GET_MASK             0x0000000C
#define SWS_HSI_MASK             0x00000000
#define SWS_HSE_MASK             0x00000004
#define SWS_PLL_MASK             0x00000008

#define SET_PLL_M_MASK           0x0000003F
#define SET_PLL_N_MASK           0x00007FC0
#define SET_PLL_P_MASK           0x00030000
#define SET_PLL_Q_MASK           0x0F000000
#define SET_PLL_SRC_MASK         0x00400000

#define AHB_SET_MASK             0x000000F0
#define APB1_SET_MASK            0x00001C00
#define APB2_SET_MASK            0x0000E000

#define PLL_M_SHIFT              0
#define PLL_N_SHIFT              6
#define PLL_P_SHIFT              16
#define PLL_Q_SHIFT              24
#define PLL_PLLSRC_SHIFT         22

#define AHB_SHIFT                4
#define APB1_SHIFT               10
#define APB2_SHIFT               13


ret_enuErrorStatus_t rcc_selectSysClock( u8 Copy_u8ClockSystem )
{
    ret_enuErrorStatus_t Local_ErrorStatus = ret_Ok;
    u32 Local_u32CFGR;
    u32 Local_u32TimeOut = 0;
    if( Copy_u8ClockSystem >= rcc_HSI && Copy_u8ClockSystem <= rcc_PLL )
    {
        switch(Copy_u8ClockSystem)
        {
            case rcc_HSI :
                if( RCC_CR & HSI_ON_MASK == HSI_ON_MASK )
                {
                    if ( RCC_CR & HSI_RDY_MASK == HSI_RDY_MASK)
                    {
                        Local_u32CFGR = RCC_CFGR;
                        Local_u32CFGR &= SW_CLEAR_MASK;
                        Local_u32CFGR |= (rcc_HSI<<0);
                        RCC_CFGR = Local_u32CFGR;
                        while( (( RCC_CFGR & SWS_GET_MASK ) != SWS_HSI_MASK) && Local_u32TimeOut < 1000)
                        {
                            Local_u32TimeOut++;
                            if(Local_u32TimeOut == 1000)
                            {
                                Local_ErrorStatus = ret_NotOk;
                            }
                        }
                    }
                    else
                    {
                        Local_ErrorStatus = ret_NotOk;
                    }

                }
                else
                {
                    Local_ErrorStatus = ret_NotOk;
                }
            break;

            case rcc_HSE :
                if( (RCC_CR & HSE_ON_MASK) == HSE_ON_MASK )
                {
                    if ( (RCC_CR & HSE_RDY_MASK) == HSE_RDY_MASK)
                    {
                        Local_u32CFGR = RCC_CFGR;
                        Local_u32CFGR &= (SW_CLEAR_MASK);
                        Local_u32CFGR |= (rcc_HSE<<0);
                        RCC_CFGR = Local_u32CFGR;
                        while( (( RCC_CFGR & SWS_GET_MASK ) != SWS_HSE_MASK) && Local_u32TimeOut < 1000)
                        {
                            Local_u32TimeOut++;
                            if(Local_u32TimeOut >= 1000)
                            {
                                Local_ErrorStatus = ret_NotOk;
                            }
                        }
                    }
                    else
                    {
                        Local_ErrorStatus = ret_NotOk;
                    }

                }
                else
                {
                    Local_ErrorStatus = ret_NotOk;
                }
            break;

            case rcc_PLL :
                if( RCC_CR & PLL_ON_MASK == PLL_ON_MASK )
                {
                    if ( RCC_CR & PLL_RDY_MASK == PLL_RDY_MASK)
                    {
                        Local_u32CFGR = RCC_CFGR;
                        Local_u32CFGR &= SW_CLEAR_MASK;
                        Local_u32CFGR |= (rcc_PLL<<0);
                        RCC_CFGR = Local_u32CFGR;
                        while( (( RCC_CFGR & SWS_GET_MASK ) != SWS_PLL_MASK) && Local_u32TimeOut < 1000)
                        {
                            Local_u32TimeOut++;
                            if(Local_u32TimeOut == 1000)
                            {
                                Local_ErrorStatus = ret_NotOk;
                            }
                        }
                    }
                    else
                    {
                        Local_ErrorStatus = ret_NotOk;
                    }

                }
                else
                {
                    Local_ErrorStatus = ret_NotOk;
                }
            break;                                
        };

    }
    return Local_ErrorStatus;
}
ret_enuErrorStatus_t rcc_controlSysClock( u8 Copy_u8ClockSystem , RCC_enuClockStatus_t Copy_enuClkStatus )
{
    u32 Local_u32SysClock = (RCC_CFGR & (GET_SYS_CLOCK_MASK>>2));
    ret_enuErrorStatus_t Local_enuErrorStatus = ret_Ok;
    u32 Local_u32TimeOut = 0;
    u32 Local_u32CR;
    if( Local_u32SysClock == Copy_u8ClockSystem )
    {
        Local_enuErrorStatus = ret_NotOk;
    }
    if( Copy_u8ClockSystem >= rcc_HSI && Copy_u8ClockSystem <= rcc_PLL )
    {
        switch(Copy_u8ClockSystem)
        {
            case rcc_HSI :
                if(Copy_enuClkStatus == clock_OFF)
                {
                    Local_u32CR = RCC_CR;
                    Local_u32CR &= ~(HSI_ON_MASK);
                    RCC_CR = Local_u32CR;
                }
                else
                {
                    Local_u32CR = RCC_CR;
                    Local_u32CR |= HSI_ON_MASK;
                    RCC_CR = Local_u32CR;
                    while ( ((RCC_CR & HSI_RDY_MASK) != HSI_RDY_MASK ) && Local_u32TimeOut < 1000)
                    {
                    	Local_u32TimeOut++;
                        if(Local_u32TimeOut >= 1000)
                        {
                            Local_enuErrorStatus = ret_NotOk;
                        }
                    }
                    

                }
                break;
            case rcc_HSE :
                if(Copy_enuClkStatus == clock_OFF)
                {
                    Local_u32CR = RCC_CR;
                    Local_u32CR &= ~(HSE_ON_MASK);
                    RCC_CR = Local_u32CR;
                }
                else
                {
                    Local_u32CR = RCC_CR;
                    Local_u32CR |= HSE_ON_MASK;
                    RCC_CR = Local_u32CR;
                    while ( ((RCC_CR & HSE_RDY_MASK) != HSE_RDY_MASK ) && Local_u32TimeOut < 1000)
                    {
                    	Local_u32TimeOut++;
                        if(Local_u32TimeOut >= 1000)
                        {
                            Local_enuErrorStatus = ret_NotOk;
                        }
                    }
                    

                }
                break;
            case rcc_PLL :
                if(Copy_enuClkStatus == clock_OFF)
                {
                    Local_u32CR = RCC_CR;
                    Local_u32CR &= ~(PLL_ON_MASK);
                    RCC_CR = Local_u32CR;
                }
                else
                {
                    Local_u32CR = RCC_CR;
                    Local_u32CR |= PLL_ON_MASK;
                    RCC_CR = Local_u32CR;
                    while ( ((RCC_CR & PLL_RDY_MASK) != PLL_RDY_MASK ) && Local_u32TimeOut < 1000)
                    {
                    	Local_u32TimeOut++;
                        if(Local_u32TimeOut >= 1000)
                        {
                            Local_enuErrorStatus = ret_NotOk;
                        }
                    }
                    

                }
                break;                                
        };
    }
    else
    {
        Local_enuErrorStatus = ret_NotOk;
    }

    return Local_enuErrorStatus;

}


ret_enuErrorStatus_t rcc_checkReady(u8 Copy_u8ClockSystem, u8* Add_pu8ReadyStatus)
{
    ret_enuErrorStatus_t Local_enuErrorStatus = ret_Ok;
    if( Copy_u8ClockSystem <= rcc_HSI && Copy_u8ClockSystem >= rcc_PLL )
    {
        switch(Copy_u8ClockSystem)
        {
            case rcc_HSI :
                if(RCC_CR & HSI_RDY_MASK == HSI_RDY_MASK)
                {
                    *Add_pu8ReadyStatus = RCC_RDY_STATUS;
                }
                else
                {
                    *Add_pu8ReadyStatus = RCC_NOT_RDY_STATUS;
                }
                break;
            case rcc_HSE :
                if(RCC_CR & HSE_RDY_MASK == HSE_RDY_MASK)
                {
                    *Add_pu8ReadyStatus = RCC_RDY_STATUS;
                }
                else
                {
                    *Add_pu8ReadyStatus = RCC_NOT_RDY_STATUS;
                }
                break;
            case rcc_PLL :
                if(RCC_CR & PLL_RDY_MASK == PLL_RDY_MASK)
                {
                    *Add_pu8ReadyStatus = RCC_RDY_STATUS;
                }
                else
                {
                    *Add_pu8ReadyStatus = RCC_NOT_RDY_STATUS;
                }
                break;                                
        };
    }
    else
    {
        Local_enuErrorStatus = ret_NotOk;
    }
    return Local_enuErrorStatus;

}
ret_enuErrorStatus_t rcc_configPLL(RCC_PllConfigParams_t Copy_structPLLConfig)
{
    ret_enuErrorStatus_t Local_enuErrorStatus = ret_Ok;
    RCC_enuPLLSource_t Local_PLLSource = Copy_structPLLConfig.RCC_PLLSrc;
    u32 Local_u32PLL_M = Copy_structPLLConfig.RCC_PLL_M;
    u32 Local_u32PLL_N = Copy_structPLLConfig.RCC_PLL_N;
    u32 Local_u32PLL_P = Copy_structPLLConfig.RCC_PLL_P;
    u32 Local_u32PLL_Q = Copy_structPLLConfig.RCC_PLL_Q;

    u32 Local_u32PLLCFGR;

    if( Local_u32PLL_M == 0 || Local_u32PLL_M == 1 || Local_u32PLL_M > 63)
    {
        Local_enuErrorStatus = ret_WrongConfig;
    }
    else if( Local_u32PLL_N == 0 || Local_u32PLL_N == 1 || Local_u32PLL_N >= 433 )
    {
        Local_enuErrorStatus = ret_WrongConfig;
    }
    else if( (Local_u32PLL_P != 2) && (Local_u32PLL_P != 4) && (Local_u32PLL_P != 6) && (Local_u32PLL_P != 8) )
    {
        Local_enuErrorStatus = ret_WrongConfig;
    }
    else if( (Local_u32PLL_Q < 2) || (Local_u32PLL_Q > 15) )
    {
       Local_enuErrorStatus = ret_WrongConfig; 
    }
    else if( (RCC_CR & PLL_ON_MASK) != clock_OFF )
    {
        Local_enuErrorStatus = ret_WrongConfig;
    }
    else
    {
        /*Configure M*/
        Local_u32PLLCFGR = RCC_PLLCFGR;
        Local_u32PLLCFGR &= ~(SET_PLL_M_MASK);
        Local_u32PLLCFGR |= (Local_u32PLL_M << PLL_M_SHIFT);
        RCC_PLLCFGR = Local_u32PLLCFGR;

        /*Configure N*/
        Local_u32PLLCFGR = RCC_PLLCFGR;
        Local_u32PLLCFGR &= ~(SET_PLL_N_MASK);
        Local_u32PLLCFGR |= (Local_u32PLL_N << PLL_N_SHIFT);
        RCC_PLLCFGR = Local_u32PLLCFGR;

        /*Configure P*/
        Local_u32PLLCFGR = RCC_PLLCFGR;
        Local_u32PLLCFGR &= ~(SET_PLL_P_MASK);
        Local_u32PLLCFGR |= (Local_u32PLL_P << PLL_P_SHIFT);
        RCC_PLLCFGR = Local_u32PLLCFGR;

        /*Configure Q*/
        Local_u32PLLCFGR = RCC_PLLCFGR;
        Local_u32PLLCFGR &= ~(SET_PLL_Q_MASK);
        Local_u32PLLCFGR |= (Local_u32PLL_Q << PLL_Q_SHIFT);
        RCC_PLLCFGR = Local_u32PLLCFGR;
        /*Configure PLLSRC*/
        Local_u32PLLCFGR = RCC_PLLCFGR;
        Local_u32PLLCFGR &= ~(SET_PLL_SRC_MASK);
        Local_u32PLLCFGR |= (Local_PLLSource << PLL_PLLSRC_SHIFT);
        RCC_PLLCFGR = Local_u32PLLCFGR;

    }
    return Local_enuErrorStatus;
}
ret_enuErrorStatus_t rcc_controlPrescalerAHB(u32 Copy_u32AHBPrescaler)
{
    ret_enuErrorStatus_t Local_enuErrorStatus = ret_Ok;
    u32 Local_u32CFGR;
    switch(Copy_u32AHBPrescaler)
    {
        case rcc_AHB_NO_CLK_FACTOR :
            Local_u32CFGR = RCC_CFGR;
            Local_u32CFGR &= ~(AHB_SET_MASK);
            Local_u32CFGR |= (rcc_AHB_NO_CLK_FACTOR << AHB_SHIFT);
            RCC_CFGR = Local_u32CFGR;
        break;

        case rcc_AHB_CLK_DIVIDED_BY_2 :
            Local_u32CFGR = RCC_CFGR;
            Local_u32CFGR &= ~(AHB_SET_MASK);
            Local_u32CFGR |= (rcc_AHB_CLK_DIVIDED_BY_2 << AHB_SHIFT);
            RCC_CFGR = Local_u32CFGR;
        break;

        case rcc_AHB_CLK_DIVIDED_BY_4 :
            Local_u32CFGR = RCC_CFGR;
            Local_u32CFGR &= ~(AHB_SET_MASK);
            Local_u32CFGR |= (rcc_AHB_CLK_DIVIDED_BY_4 << AHB_SHIFT);
            RCC_CFGR = Local_u32CFGR;
        break;

        case rcc_AHB_CLK_DIVIDED_BY_8 :
            Local_u32CFGR = RCC_CFGR;
            Local_u32CFGR &= ~(AHB_SET_MASK);
            Local_u32CFGR |= (rcc_AHB_CLK_DIVIDED_BY_8 << AHB_SHIFT);
            RCC_CFGR = Local_u32CFGR;
        break;

        case rcc_AHB_CLK_DIVIDED_BY_16 :
            Local_u32CFGR = RCC_CFGR;
            Local_u32CFGR &= ~(AHB_SET_MASK);
            Local_u32CFGR |= (rcc_AHB_CLK_DIVIDED_BY_16 << AHB_SHIFT);
            RCC_CFGR = Local_u32CFGR;
        break;

        case rcc_AHB_CLK_DIVIDED_BY_64 :
            Local_u32CFGR = RCC_CFGR;
            Local_u32CFGR &= ~(AHB_SET_MASK);
            Local_u32CFGR |= (rcc_AHB_CLK_DIVIDED_BY_64 << AHB_SHIFT);
            RCC_CFGR = Local_u32CFGR;
        break;

        case rcc_AHB_CLK_DIVIDED_BY_128 :
            Local_u32CFGR = RCC_CFGR;
            Local_u32CFGR &= ~(AHB_SET_MASK);
            Local_u32CFGR |= (rcc_AHB_CLK_DIVIDED_BY_64 << AHB_SHIFT);
            RCC_CFGR = Local_u32CFGR;
        break;

        case rcc_AHB_CLK_DIVIDED_BY_256 :
            Local_u32CFGR = RCC_CFGR;
            Local_u32CFGR &= ~(AHB_SET_MASK);
            Local_u32CFGR |= (rcc_AHB_CLK_DIVIDED_BY_128 << AHB_SHIFT);
            RCC_CFGR = Local_u32CFGR;
        break;

        case rcc_AHB_CLK_DIVIDED_BY_512 :
            Local_u32CFGR = RCC_CFGR;
            Local_u32CFGR &= ~(AHB_SET_MASK);
            Local_u32CFGR |= (rcc_AHB_CLK_DIVIDED_BY_256 << AHB_SHIFT);
            RCC_CFGR = Local_u32CFGR;
        break;

        default:
             Local_enuErrorStatus = ret_NotOk;
        break;                             
    }
    return Local_enuErrorStatus;

}
ret_enuErrorStatus_t rcc_controlPrescalerAPB1(u32 Copy_u32APB1Prescaler)
{
    ret_enuErrorStatus_t Local_enuErrorStatus = ret_Ok;
    u32 Local_u32CFGR;
    switch(Copy_u32APB1Prescaler)
    {
        case rcc_APB1_NO_CLK_FACTOR :
            Local_u32CFGR = RCC_CFGR;
            Local_u32CFGR &= ~(APB1_SET_MASK);
            Local_u32CFGR |= (rcc_APB1_NO_CLK_FACTOR << APB1_SHIFT);
            RCC_CFGR = Local_u32CFGR;
        break;

        case rcc_APB1_CLK_DIVIDED_BY_2 :
            Local_u32CFGR = RCC_CFGR;
            Local_u32CFGR &= ~(APB1_SET_MASK);
            Local_u32CFGR |= (rcc_APB1_CLK_DIVIDED_BY_2 << APB1_SHIFT);
            RCC_CFGR = Local_u32CFGR;
        break;

        case rcc_APB1_CLK_DIVIDED_BY_4 :
            Local_u32CFGR = RCC_CFGR;
            Local_u32CFGR &= ~(APB1_SET_MASK);
            Local_u32CFGR |= (rcc_APB1_CLK_DIVIDED_BY_4 << APB1_SHIFT);
            RCC_CFGR = Local_u32CFGR;
        break;

        case rcc_APB1_CLK_DIVIDED_BY_8 :
            Local_u32CFGR = RCC_CFGR;
            Local_u32CFGR &= ~(APB1_SET_MASK);
            Local_u32CFGR |= (rcc_APB1_CLK_DIVIDED_BY_8 << APB1_SHIFT);
            RCC_CFGR = Local_u32CFGR;
        break;

        case rcc_APB1_CLK_DIVIDED_BY_16 :
            Local_u32CFGR = RCC_CFGR;
            Local_u32CFGR &= ~(APB1_SET_MASK);
            Local_u32CFGR |= (rcc_APB1_CLK_DIVIDED_BY_16 << APB1_SHIFT);
            RCC_CFGR = Local_u32CFGR;
        break;
        default :
            Local_enuErrorStatus = ret_NotOk;
        break;    
    }
    return Local_enuErrorStatus;        

}
ret_enuErrorStatus_t rcc_controlPrescalerAPB2(u32 Copy_u32APB2Prescaler)
{
    ret_enuErrorStatus_t Local_enuErrorStatus = ret_Ok;
    u32 Local_u32CFGR;
    switch(Copy_u32APB2Prescaler)
    {
        case rcc_APB2_NO_CLK_FACTOR :
            Local_u32CFGR = RCC_CFGR;
            Local_u32CFGR &= ~(APB2_SET_MASK);
            Local_u32CFGR |= (rcc_APB2_NO_CLK_FACTOR << APB2_SHIFT);
            RCC_CFGR = Local_u32CFGR;
        break;

        case rcc_APB2_CLK_DIVIDED_BY_2 :
            Local_u32CFGR = RCC_CFGR;
            Local_u32CFGR &= ~(APB2_SET_MASK);
            Local_u32CFGR |= (rcc_APB2_CLK_DIVIDED_BY_2 << APB2_SHIFT);
            RCC_CFGR = Local_u32CFGR;
        break;

        case rcc_APB2_CLK_DIVIDED_BY_4 :
            Local_u32CFGR = RCC_CFGR;
            Local_u32CFGR &= ~(APB2_SET_MASK);
            Local_u32CFGR |= (rcc_APB2_CLK_DIVIDED_BY_4 << APB2_SHIFT);
            RCC_CFGR = Local_u32CFGR;
        break;

        case rcc_APB2_CLK_DIVIDED_BY_8 :
            Local_u32CFGR = RCC_CFGR;
            Local_u32CFGR &= ~(APB2_SET_MASK);
            Local_u32CFGR |= (rcc_APB1_CLK_DIVIDED_BY_8 << APB2_SHIFT);
            RCC_CFGR = Local_u32CFGR;
        break;

        case rcc_APB2_CLK_DIVIDED_BY_16 :
            Local_u32CFGR = RCC_CFGR;
            Local_u32CFGR &= ~(APB2_SET_MASK);
            Local_u32CFGR |= (rcc_APB2_CLK_DIVIDED_BY_16 << APB2_SHIFT);
            RCC_CFGR = Local_u32CFGR;
        break;
        default :
            Local_enuErrorStatus = ret_NotOk;
        break;    
    }
    return Local_enuErrorStatus;            

}
ret_enuErrorStatus_t rcc_enablePreipheral(u32 Copy_u32PeripheralBus, u32 Copy_u32Peripheral)
{
    ret_enuErrorStatus_t Local_enuErrorStatus = ret_Ok;
    switch( Copy_u32PeripheralBus )
    {
        case rcc_AHB1 :
            RCC_AHB1ENR |= ( 1 << Copy_u32Peripheral );
        break;

        case rcc_AHB2 :
            RCC_AHB2ENR |= ( 1 << Copy_u32Peripheral );
        break;

        case rcc_APB1 :
            RCC_APB1ENR |= ( 1 << Copy_u32Peripheral );
        break;

        case rcc_APB2 :
            RCC_APB2ENR |= ( 1 << Copy_u32Peripheral );
        break;

        default :
             Local_enuErrorStatus = ret_NotOk;                           
    }
    return Local_enuErrorStatus;

}

ret_enuErrorStatus_t rcc_disablePreipheral(u32 Copy_u32PeripheralBus, u32 Copy_u32Peripheral)
{
    ret_enuErrorStatus_t Local_enuErrorStatus = ret_Ok;
    switch( Copy_u32PeripheralBus )
    {
        case rcc_AHB1 :
            RCC_AHB1ENR &= ~( 1 << Copy_u32Peripheral );
        break;

        case rcc_AHB2 :
            RCC_AHB2ENR &= ~( 1 << Copy_u32Peripheral );
        break;

        case rcc_APB1 :
            RCC_APB1ENR &= ~( 1 << Copy_u32Peripheral );
        break;

        case rcc_APB2 :
            RCC_APB2ENR &= ~( 1 << Copy_u32Peripheral );
        break;

        default :
             Local_enuErrorStatus = ret_NotOk;                           
    }
    return Local_enuErrorStatus;    

}

ret_enuErrorStatus_t rcc_EnableAHB1Preipherals(u64 Copy_u64Peripheral)
{
    ret_enuErrorStatus_t Local_enuErrorStatus = ret_Ok;
    if(( rcc_AHB1_MASK &  Copy_u64Peripheral ) != rcc_AHB1_MASK )
    {
        Local_enuErrorStatus = ret_NotOk;
    }
    else
    {
        RCC_AHB1ENR |= Copy_u64Peripheral;
    }
    return Local_enuErrorStatus;
}
ret_enuErrorStatus_t rcc_EnableAHB2Preipherals(u64 Copy_u64Peripheral)
{
    ret_enuErrorStatus_t Local_enuErrorStatus = ret_Ok;
    if(( rcc_AHB2_MASK &  Copy_u64Peripheral ) != rcc_AHB2_MASK )
    {
        Local_enuErrorStatus = ret_NotOk;
    }
    else
    {
        RCC_AHB2ENR |= Copy_u64Peripheral;
    }
    return Local_enuErrorStatus;
}
ret_enuErrorStatus_t rcc_EnableAPB1Preipherals(u64 Copy_u64Peripheral)
{
    ret_enuErrorStatus_t Local_enuErrorStatus = ret_Ok;
    if(( rcc_APB1_MASK &  Copy_u64Peripheral ) != rcc_APB1_MASK )
    {
        Local_enuErrorStatus = ret_NotOk;
    }
    else
    {
        RCC_APB1ENR |= Copy_u64Peripheral;
    }
    return Local_enuErrorStatus;
}
ret_enuErrorStatus_t rcc_EnableAPB2Preipherals(u64 Copy_u64Peripheral)
{
    ret_enuErrorStatus_t Local_enuErrorStatus = ret_Ok;
    if(( rcc_APB2_MASK &  Copy_u64Peripheral ) != rcc_APB2_MASK )
    {
        Local_enuErrorStatus = ret_NotOk;
    }
    else
    {
        RCC_APB2ENR |= Copy_u64Peripheral;
    }
    return Local_enuErrorStatus;
}
ret_enuErrorStatus_t rcc_DisableAHB1Preipherals(u64 Copy_u64Peripheral)
{
    ret_enuErrorStatus_t Local_enuErrorStatus = ret_Ok;
    if(( rcc_AHB1_MASK &  Copy_u64Peripheral ) != rcc_AHB1_MASK )
    {
        Local_enuErrorStatus = ret_NotOk;
    }
    else
    {
        RCC_AHB1ENR &= ~(Copy_u64Peripheral);
    }
    return Local_enuErrorStatus;
}
ret_enuErrorStatus_t rcc_DisableAHB2Preipherals(u64 Copy_u64Peripheral)
{
    ret_enuErrorStatus_t Local_enuErrorStatus = ret_Ok;
    if(( rcc_AHB2_MASK &  Copy_u64Peripheral ) != rcc_AHB2_MASK )
    {
        Local_enuErrorStatus = ret_NotOk;
    }
    else
    {
        RCC_AHB2ENR &= ~(Copy_u64Peripheral);
    }
    return Local_enuErrorStatus;
}
ret_enuErrorStatus_t rcc_DisableAPB1Preipherals(u64 Copy_u64Peripheral)
{
    ret_enuErrorStatus_t Local_enuErrorStatus = ret_Ok;
    if(( rcc_APB1_MASK &  Copy_u64Peripheral ) != rcc_APB1_MASK )
    {
        Local_enuErrorStatus = ret_NotOk;
    }
    else
    {
        RCC_APB1ENR &= ~(Copy_u64Peripheral);
    }
    return Local_enuErrorStatus;

}
ret_enuErrorStatus_t rcc_DisableAPB2Preipherals(u64 Copy_u64Peripheral)
{
    ret_enuErrorStatus_t Local_enuErrorStatus = ret_Ok;
    if(( rcc_APB2_MASK &  Copy_u64Peripheral ) != rcc_APB2_MASK )
    {
        Local_enuErrorStatus = ret_NotOk;
    }
    else
    {
        RCC_APB2ENR &= ~(Copy_u64Peripheral);
    }
    return Local_enuErrorStatus;

}




