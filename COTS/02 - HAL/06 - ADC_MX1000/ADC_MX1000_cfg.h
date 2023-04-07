/*******************************************************************/
/*         ADC_MX1000 Driver         */
/* Target:STM32F401CC                       */
/*Author :Yousef_Ahmed                         */
/*Date   :2023-04-08                                      */
/*******************************************************************/

#ifndef _ADC_MX1000_CFG_H
#define _ADC_MX1000_CFG_H


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
    u32 adc_MX1000_Enable;
    u32 adc_MX1000_Prescalar;
    u32 Analog_WatchDog;
    u32 Discont_Mode_Normal_Channel_Count;
    u32 Discont_Mode_Injected_Channel_Count;
    u32 Dicont_Mode_Regular_Channels;
    u32 Automatic_Inj_Grp_Conv;
    u32 AWD_On_Single_Channel_Scan_Mode;
    u32 Scan;
    u32 Inj_Channel_Int;
    u32 AWD_Int;
    u32 End_Of_Conv_Int;
    u32 AWD_Channel_Select;
    u32 Extern_Trig;
    u32 Extern_Event_Select;
    u32 Extern_Trig_Inj;
    u32 Extern_Event_Select_Inj;
    u32 Sampling_Time;
    u32 Inj_Data_Offset;
    u32 Regular_Seq_Len;
    u32 Regular_Sequence;
    u32 Inj_Seq_Len;
    u32 Inj_Sequence;

}adc_MX1000_config_t;

#endif /*ADC_MX1000_CFG_H*/
