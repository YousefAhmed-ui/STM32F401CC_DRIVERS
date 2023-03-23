/*******************************************************************/
/*         SYSTICK Driver        */
/* Target:STM32F401CC                       */
/*Author :Yousef_Ahmed                         */
/*Date   :2023-03-09                                      */
/*******************************************************************/

#ifndef _SYSTICK_H
#define _SYSTICK_H

#define stk_ENABLE_MASK                             0x00000001
#define stk_DISABLE_MASK                            0xFFFFFFFE

#define stk_ENABLE_INT                              0x00000002
#define stk_DISABLE_INT                             0xFFFFFFFD

#define stk_CLOCK_SOURCE_AHB                        0x00000004    
#define stk_CLOCK_SOURCE_AHB_DIVIDED_BY_8           0xFFFFFFF7    

#define stk_INT_ON                                   0
#define stk_INT_OFF                                  1

#define stk_AHB_CLOCK_HSE                           (u32)(25000000)
#define stk_AHB_CLOCK_HSI                           (u32)(16000000)
#define stk_AHB_CLOCK_PLL                           (u32)(84000000)

typedef enum{
    stk_Ok,
    stk_NotOk,
    stk_NullPtr
}STKError_t;

typedef void (*STK_cbf)(void);

/*************************************************************************************************************************/
/* FunctionDiscription  : Starts the the Systick                                                                         */
/* Inputs  : void                                                                                                        */
/* Return :  void                                                                                                        */
/*************************************************************************************************************************/ 
extern void stk_Start(void);
/*************************************************************************************************************************/
/* FunctionDiscription  : Stops  the the Systick                                                                         */
/* Inputs  :  void                                                                                                       */
/* Return :   void                                                                                                       */
/*************************************************************************************************************************/ 
extern void stk_Stop(void);
/*************************************************************************************************************************/
/* FunctionDiscription  : read the current value of the systick                                                          */
/* Inputs  : pointer to a variable that will hold the value                                                              */
/* Return : error status                                                                                                 */
/*************************************************************************************************************************/ 
extern STKError_t stk_GetCurrentValue(u32 * Addp_CurrentValue);
/*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  :                                                                                                             */
/* Return :                                                                                                              */
/*************************************************************************************************************************/
extern STKError_t stk_SetPeriod_ms(u16 Copy_u16Period , u32 Copy_AHBClock);
/*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  :                                                                                                             */
/* Return :                                                                                                              */
/*************************************************************************************************************************/ 
extern STKError_t stk_SetTickTime(u32 Copy_u32Prescalar);
/*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  :                                                                                                             */
/* Return :                                                                                                              */
/*************************************************************************************************************************/ 
extern STKError_t stk_SetCbf(STK_cbf STK_CallBackFunction);
/*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  :                                                                                                             */
/* Return :                                                                                                              */
/*************************************************************************************************************************/ 
extern void stk_SetInterrupt(u8 Copy_u8Status);



#endif /*SYSTICK_H*/
