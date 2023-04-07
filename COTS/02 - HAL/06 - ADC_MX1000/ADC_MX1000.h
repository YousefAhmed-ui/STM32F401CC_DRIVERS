/*******************************************************************/
/*         adc_MX1000_MX1000_MX1000 Driver        */
/* Target:STM32F401CC                       */
/*Author :Yousef_Ahmed                         */
/*Date   :2023-04-08                                      */
/*******************************************************************/

#ifndef _ADC_MX1000_MX1000_H
#define _ADC_MX1000_MX1000_H


#include "ADC_MX1000_cfg.h"


#define adc_MX1000_OVERRUN_INT_ENABLE                0X04000000
#define adc_MX1000_OVERRUN_INT_DISABLE               0X00000000


#define adc_MX1000_RESOLUTION_12_BIT                 0x00000000
#define adc_MX1000_RESOLUTION_10_BIT                 0x01000000
#define adc_MX1000_RESOLUTION_8_BIT                  0x02000000
#define adc_MX1000_RESOLUTION_6_BIT                  0x03000000

#define adc_MX1000_AWD_ENABLE_REGULAR                0x00800000

#define adc_MX1000_AWD_ENABLE_INJ                    0x00400000

#define adc_MX1000_DISCONT_MOD_CH_COUNT_1            0x00000000              
#define adc_MX1000_DISCONT_MOD_CH_COUNT_2            0x00001000              
#define adc_MX1000_DISCONT_MOD_CH_COUNT_3            0x00002000              
#define adc_MX1000_DISCONT_MOD_CH_COUNT_4            0x00003000              
#define adc_MX1000_DISCONT_MOD_CH_COUNT_5            0x00004000              
#define adc_MX1000_DISCONT_MOD_CH_COUNT_6            0x00005000              
#define adc_MX1000_DISCONT_MOD_CH_COUNT_7            0x00006000              
#define adc_MX1000_DISCONT_MOD_CH_COUNT_8            0x00007000

#define adc_MX1000_DISCONT_MOD_CH_INJ_ENABLE         0x00001000

#define adc_MX1000_DISCONT_MOD_CH_REGUALR_ENABLE     0x00000800

#define adc_MX1000_AUTO_INJ_GRP_CONV_ENABLE          0x00000400

#define adc_MX1000_AWD_ON_SING_CH_SCAN_ENABLE        0x00000200

#define adc_MX1000_SCAN_MODE_ENABLE                  0x00000100

#define INJ_CH_INT_ENABLE                     0x00000080

#define AWD_INT_ENABLE                        0x00000040

#define adc_MX1000_END_OF_CONV_INT_ENABLE            0x00000020

#define adc_MX1000_AWD_CH_SELECT_0                   0x00000000
#define adc_MX1000_AWD_CH_SELECT_1                   0x00000001
#define adc_MX1000_AWD_CH_SELECT_2                   0x00000002
#define adc_MX1000_AWD_CH_SELECT_3                   0x00000003
#define adc_MX1000_AWD_CH_SELECT_4                   0x00000004
#define adc_MX1000_AWD_CH_SELECT_5                   0x00000005
#define adc_MX1000_AWD_CH_SELECT_6                   0x00000006
#define adc_MX1000_AWD_CH_SELECT_7                   0x00000007
#define adc_MX1000_AWD_CH_SELECT_8                   0x00000008
#define adc_MX1000_AWD_CH_SELECT_9                   0x00000009
#define adc_MX1000_AWD_CH_SELECT_10                  0x0000000A
#define adc_MX1000_AWD_CH_SELECT_11                  0x0000000B
#define adc_MX1000_AWD_CH_SELECT_12                  0x0000000C
#define adc_MX1000_AWD_CH_SELECT_13                  0x0000000D
#define adc_MX1000_AWD_CH_SELECT_14                  0x0000000E
#define adc_MX1000_AWD_CH_SELECT_15                  0x0000000F
#define adc_MX1000_AWD_CH_SELECT_16                  0x00000010
#define adc_MX1000_AWD_CH_SELECT_17                  0x00000011
#define adc_MX1000_AWD_CH_SELECT_18                  0x00000012

 

typedef enum{

    adc_MX1000_Ok,
    adc_MX1000_NotOk

}adc_MX1000_Error_t;




typedef void (*adc_MX1000_cbf)(void);


/*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  : void                                                                                                        */
/* Return :  void                                                                                                        */
/*************************************************************************************************************************/ 
extern void adc_MX1000_Init(adc_MX1000_config_t * Addp_adc_MX1000_Config);
/*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  : void                                                                                                        */
/* Return :  void                                                                                                        */
/*************************************************************************************************************************/
extern adc_MX1000_Error_t adc_MX1000_GetValueSync( u16 * Addp_Value);
/*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  : void                                                                                                        */
/* Return :  void                                                                                                        */
/*************************************************************************************************************************/
extern adc_MX1000_Error_t adc_MX1000_GetValueAsync( u16 * Addp_Value , adc_MX1000_cbf adc_MX1000_CallBackFunc);


#endif /*adc_MX1000_MX1000_H*/
