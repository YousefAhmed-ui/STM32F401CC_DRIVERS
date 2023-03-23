/*************************************************************************************************************************/
/* author : yousef ahmed                                                                                                 */
/* date   : 30/1/2022                                                                                                     */
/* version: V01                                                                                                          */
/*************************************************************************************************************************/ 
#ifndef RCC_H
#define RCC_H

#include "STD_TYPES.h"
#include "BIT_MATH.h"



/*******************************SystemClocks*****************************************/
#define rcc_HSI   0
#define rcc_HSE   1
#define rcc_PLL   2

#define rcc_AHB1  0
#define rcc_AHB2  1
#define rcc_APB1  2
#define rcc_APB2  3

#define RCC_RDY_STATUS           0
#define RCC_NOT_RDY_STATUS       1

/********************************Prescalars******************************************/


/**********************************AHB_Prescalars************************************/
#define rcc_AHB_NO_CLK_FACTOR              0b0000
#define rcc_AHB_CLK_DIVIDED_BY_2           0b1000
#define rcc_AHB_CLK_DIVIDED_BY_4           0b1001
#define rcc_AHB_CLK_DIVIDED_BY_8           0b1010
#define rcc_AHB_CLK_DIVIDED_BY_16          0b1011
#define rcc_AHB_CLK_DIVIDED_BY_64          0b1100
#define rcc_AHB_CLK_DIVIDED_BY_128         0b1101
#define rcc_AHB_CLK_DIVIDED_BY_256         0b1110
#define rcc_AHB_CLK_DIVIDED_BY_512         0b1111

/*********************************APB1_Prescalars*************************************/
#define rcc_APB1_NO_CLK_FACTOR             0b000
#define rcc_APB1_CLK_DIVIDED_BY_2          0b100
#define rcc_APB1_CLK_DIVIDED_BY_4          0b101
#define rcc_APB1_CLK_DIVIDED_BY_8          0b110
#define rcc_APB1_CLK_DIVIDED_BY_16         0b111

/*********************************APB2_Prescalars*************************************/
#define rcc_APB2_NO_CLK_FACTOR             0b000
#define rcc_APB2_CLK_DIVIDED_BY_2          0b100
#define rcc_APB2_CLK_DIVIDED_BY_4          0b101
#define rcc_APB2_CLK_DIVIDED_BY_8          0b110
#define rcc_APB2_CLK_DIVIDED_BY_16         0b111

/**********************************Peripherals****************************************/
/**********************************AHB1***********************************************/
#define rcc_GPIOA                          0
#define rcc_GPIOB                          1
#define rcc_GPIOC                          2
#define rcc_GPIOD                          3
#define rcc_GPIOE                          4
#define rcc_GPIOH                          7
#define rcc_CRC                            12
#define rcc_DMA1                           21
#define rcc_DMA2                           22
/********************************AHB2**************************************************/

#define rcc_OTGFS                          7

/*******************************APB1***************************************************/

#define rcc_TIM2                           0
#define rcc_TIM3                           1
#define rcc_TIM4                           2
#define rcc_TIM5                           3
#define rcc_WWDG                           11
#define rcc_SPI2                           14
#define rcc_SPI3                           15
#define rcc_USART3                         17
#define rcc_I2C1                           21
#define rcc_I2C2                           22
#define rcc_I2C3                           23
#define rcc_PWR                            28
/******************************APB2****************************************************/
#define rcc_TIM0                           0
#define rcc_USART1                         4
#define rcc_USART2                         5
#define rcc_ADC1                           8
#define rcc_SDIO                           11
#define rcc_SPI1                           12
#define rcc_SPI4                           13
#define rcc_SYSCFG                         14
#define rcc_TIM9                           16
#define rcc_TIM10                          17
#define rcc_TIM11                          18
/************************************************************************************/
#define rcc_AHB1_GPIOA                     (u64)(0x100000001)
#define rcc_AHB1_GPIOB                     (u64)(0x100000002)
#define rcc_AHB1_GPIOC                     (u64)(0x100000004)
#define rcc_AHB1_GPIOD                     (u64)(0x100000008)
#define rcc_AHB1_GPIOE                     (u64)(0x100000010)
#define rcc_AHB1_GPIOH                     (u64)(0x100000080)
#define rcc_AHB1_CRC                       (u64)(0x100001000)
#define rcc_AHB1_DMA1                      (u64)(0x100020000) 
#define rcc_AHB1_DMA2                      (u64)(0x100040000)
#define rcc_AHB1_MASK                      (u64)(0x100000000)
/*********************************AHB2************************************************/
#define rcc_AHB2_OTGFS                     (u64)(0x200000080)
#define rcc_AHB2_MASK                      (u64)(0x200000000)
/*******************************APB1**************************************************/
#define rcc_TIM2                           (u64)(0x300000001)
#define rcc_TIM3                           (u64)(0x300000002)
#define rcc_TIM4                           (u64)(0x300000004)
#define rcc_TIM5                           (u64)(0x300000008)
#define rcc_WWDG                           (u64)(0x300000800)
#define rcc_SPI2                           (u64)(0x300004000)
#define rcc_SPI3                           (u64)(0x300008000)
#define rcc_USART2                         (u64)(0x300020000)
#define rcc_I2C1                           (u64)(0x300200000)
#define rcc_I2C2                           (u64)(0x300400000)
#define rcc_I2C3                           (u64)(0x300800000)
#define rcc_PWR                            (u64)(0x310000000)
#define rcc_APB1_MASK                      (u64)(0x300000000) 
/******************************APB2****************************************************/
#define rcc_TIM0                           (u64)(0x400000001)
#define rcc_USART1                         (u64)(0x400000010)
#define rcc_USART6                         (u64)(0x400000020)
#define rcc_ADC1                           (u64)(0x400000100)
#define rcc_SDIO                           (u64)(0x400000800)
#define rcc_SPI1                           (u64)(0x400001000)
#define rcc_SPI4                           (u64)(0x400002000)
#define rcc_SYSCFG                         (u64)(0x400004000)
#define rcc_TIM9                           (u64)(0x400010000)
#define rcc_TIM10                          (u64)(0x400020000)
#define rcc_TIM11                          (u64)(0x400040000)
#define rcc_APB2_MASK                      (u64)(0x400000000)
/*************************************************************************************/
#define RCC_RDY_STATUS           0
#define RCC_NOT_RDY_STATUS       1

/*******************************Types************************************************/

typedef enum{
  HSI_PLL_SRC,
  HSE_PLL_SRC
}RCC_enuPLLSource_t;

typedef struct{
    RCC_enuPLLSource_t RCC_PLLSrc;
    u32 RCC_PLL_M;
    u32 RCC_PLL_N;
    u32 RCC_PLL_P;
    u32 RCC_PLL_Q;
}RCC_PllConfigParams_t;

typedef enum{
  clock_OFF,
  clock_ON
}RCC_enuClockStatus_t;

typedef enum{
    ret_Ok,
    ret_NotOk,
    ret_WrongConfig
}ret_enuErrorStatus_t;





/*************************************************************************************************************************/
/* Function_Description : the function is to select which clock source you want to select                                */
/* Inputs   : HSI - HSE - PLL                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/ 
ret_enuErrorStatus_t rcc_selectSysClock( u8 Copy_u8ClockSystem );
/*************************************************************************************************************************/
/* Function_Description :turn on system clock and wait untill it's ready                                                 */
/* Inputs   : system clock (HSI - HSE - PLL)                                                                             */
/* Return   : Error_status either Ready or not                                                                           */
/*************************************************************************************************************************/ 
ret_enuErrorStatus_t rcc_controlSysClock( u8 Copy_u8ClockSystem , RCC_enuClockStatus_t Copy_enuClkStatus );
/*************************************************************************************************************************/
/* Function_Description : check if the selected clock is ready                                                           */
/* Inputs   : system clock you wanna check on                                                                            */
/* Return   : Error_status either ready or not                                                                           */
/*************************************************************************************************************************/ 
ret_enuErrorStatus_t rcc_checkReady(u8 Copy_u8ClockSystem, u8* Add_pu8ReadyStatus);
/*************************************************************************************************************************/
/* Function_Description : config every parameter in pll                                                                  */
/* Inputs   : (P - M - N - Q )                                                                                           */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/ 
ret_enuErrorStatus_t rcc_configPLL(RCC_PllConfigParams_t Copy_structPLLConfig);
/*************************************************************************************************************************/
/* Function_Description : set the prescalar of AHB bus                                                                   */
/* Inputs   : division amount                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/ 
ret_enuErrorStatus_t rcc_controlPrescalerAHB(u32 Copy_u32AHBPrescaler);
/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/ 
ret_enuErrorStatus_t rcc_controlPrescalerAPB1(u32 Copy_u32APB1Prescaler);
/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/ 
ret_enuErrorStatus_t rcc_controlPrescalerAPB2(u32 Copy_u32APB2Prescaler);
/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/ 
ret_enuErrorStatus_t rcc_enablePreipheral(u32 Copy_u32PeripheralBus, u32 Copy_u32Peripheral);
/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/ 
ret_enuErrorStatus_t rcc_disablePreipheral(u32 Copy_u32PeripheralBus, u32 Copy_u32Peripheral);
/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/
ret_enuErrorStatus_t rcc_EnableAHB1Preipherals(u64 Copy_u64Peripheral);
/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/
ret_enuErrorStatus_t rcc_EnableAHB2Preipherals(u64 Copy_u64Peripheral);
/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/
ret_enuErrorStatus_t rcc_EnableAPB1Preipherals(u64 Copy_u64Peripheral);
/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/
ret_enuErrorStatus_t rcc_EnableAPB2Preipherals(u64 Copy_u64Peripheral);
/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/
ret_enuErrorStatus_t rcc_DisableAHB1Preipherals(u64 Copy_u64Peripheral);
/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/
ret_enuErrorStatus_t rcc_DisableAHB2Preipherals(u64 Copy_u64Peripheral);
/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/
ret_enuErrorStatus_t rcc_DisableAPB1Preipherals(u64 Copy_u64Peripheral);
/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/
ret_enuErrorStatus_t rcc_DisableAPB2Preipherals(u64 Copy_u64Peripheral);






#endif
