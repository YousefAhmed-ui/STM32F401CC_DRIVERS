/*******************************************************************/
/*         ADC Driver        */
/* Target:STM32F401CC                       */
/*Author :Yousef_Ahmed                         */
/*Date   :2023-04-07                                      */
/*******************************************************************/

#ifndef _ADC_H
#define _ADC_H

#define adc_OVERRUN_INT_ENABLE                0X04000000
#define adc_OVERRUN_INT_DISABLE               0X00000000


#define adc_RESOLUTION_12_BIT                 0x00000000
#define adc_RESOLUTION_10_BIT                 0x01000000
#define adc_RESOLUTION_8_BIT                  0x02000000
#define adc_RESOLUTION_6_BIT                  0x03000000

#define adc_AWD_ENABLE_REGULAR                0x00800000

#define adc_AWD_ENABLE_INJ                    0x00400000

#define adc_DISCONT_MOD_CH_COUNT_1            0x00000000              
#define adc_DISCONT_MOD_CH_COUNT_2            0x00001000              
#define adc_DISCONT_MOD_CH_COUNT_3            0x00002000              
#define adc_DISCONT_MOD_CH_COUNT_4            0x00003000              
#define adc_DISCONT_MOD_CH_COUNT_5            0x00004000              
#define adc_DISCONT_MOD_CH_COUNT_6            0x00005000              
#define adc_DISCONT_MOD_CH_COUNT_7            0x00006000              
#define adc_DISCONT_MOD_CH_COUNT_8            0x00007000

#define adc_DISCONT_MOD_CH_INJ_ENABLE         0x00001000

#define adc_DISCONT_MOD_CH_REGUALR_ENABLE     0x00000800

#define adc_AUTO_INJ_GRP_CONV_ENABLE          0x00000400

#define adc_AWD_ON_SING_CH_SCAN_ENABLE        0x00000200

#define adc_SCAN_MODE_ENABLE                  0x00000100

#define INJ_CH_INT_ENABLE                     0x00000080

#define AWD_INT_ENABLE                        0x00000040

#define adc_END_OF_CONV_INT_ENABLE            0x00000020

#define adc_AWD_CH_SELECT_0                   0x00000000
#define adc_AWD_CH_SELECT_1                   0x00000001
#define adc_AWD_CH_SELECT_2                   0x00000002
#define adc_AWD_CH_SELECT_3                   0x00000003
#define adc_AWD_CH_SELECT_4                   0x00000004
#define adc_AWD_CH_SELECT_5                   0x00000005
#define adc_AWD_CH_SELECT_6                   0x00000006
#define adc_AWD_CH_SELECT_7                   0x00000007
#define adc_AWD_CH_SELECT_8                   0x00000008
#define adc_AWD_CH_SELECT_9                   0x00000009
#define adc_AWD_CH_SELECT_10                  0x0000000A
#define adc_AWD_CH_SELECT_11                  0x0000000B
#define adc_AWD_CH_SELECT_12                  0x0000000C
#define adc_AWD_CH_SELECT_13                  0x0000000D
#define adc_AWD_CH_SELECT_14                  0x0000000E
#define adc_AWD_CH_SELECT_15                  0x0000000F
#define adc_AWD_CH_SELECT_16                  0x00000010
#define adc_AWD_CH_SELECT_17                  0x00000011
#define adc_AWD_CH_SELECT_18                  0x00000012

 

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
