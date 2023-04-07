/*******************************************************************/
/*         ADC Driver        */
/* Target:STM32F401CC                       */
/*Author :Yousef_Ahmed                         */
/*Date   :2023-04-07                                      */
/*******************************************************************/

#ifndef _ADC_H
#define _ADC_H

#define 



typedef enum{

    adc_Ok,
    adc_NotOk

}ADC_Error_t;

typedef struct{

    u32 Overrun_Int;
    u32 Resolution;
    u32 Start_Conv;
    u32 External_Trig_Regular_Channels;
    u32 External_Event_Select;
    u32 Data_Align;
    u32 End_Of_Conv_Selection;
    u32 DMA_Disable_Selection;
    u32 DMA_Mode;
    u32 Continuous_Conv;
    u32 ADC_Enable;
    u32 ADC_Prescalar;


}ADC_config_t;


typedef void (*ADC_cbf)(void);


/*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  : void                                                                                                        */
/* Return :  void                                                                                                        */
/*************************************************************************************************************************/ 
extern void adc_Init(ADC_config_t * Addp_Adc_Config);
/*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  : void                                                                                                        */
/* Return :  void                                                                                                        */
/*************************************************************************************************************************/
extern ADC_Error_t adc_GetValueSync( u16 * Addp_Value);
/*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  : void                                                                                                        */
/* Return :  void                                                                                                        */
/*************************************************************************************************************************/
extern ADC_Error_t adc_GetValueAsync( u16 * Addp_Value , ADC_cbf Adc_CallBackFunc);

#endif /*ADC_H*/
