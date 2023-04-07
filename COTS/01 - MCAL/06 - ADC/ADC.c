/******************************************************************/
/*ADC Driver                */
/* Target:STM32F401CC                       */
/* Yousef_Ahmed                              */
/* Date:2023-04-07                                       */
/******************************************************************/
#include "STD_TYPES.h"
#include "ADC.h"

typedef struct{

    u32 SR;
    u32 CR1;
    u32 CR2;
    u32 SMPR1;
    u32 SMPR2;
    u32 JOFR1;
    u32 JOFR2;
    u32 JOFR3;
    u32 JOFR4;
    u32 HTR;
    u32 LTR;
    u32 SQR1;
    u32 SQR2;
    u32 SQR3;
    u32 JSQR;
    u32 JDR1;
    u32 JDR2;
    u32 JDR3;
    u32 JDR4;
    u32 DR;
    u32 CCR;

}ADC_t;

#define ADC     ((volatile ADC_t *const)0x40012000)

#define adc_OVERRUN_READ_MASK                    0x00000020
#define adc_REGULAR_CHANNEL_START_READ_MASK      0x00000010
#define adc_INJECTED_CHANNEL_START_MASK          0x00000008
#define adc_INJECTED_CHANNEL_END_OF_CONV_MASK    0x00000004
#define adc_REGULAR_CHANNEL_END_OF_CONV_MASK     0x00000002
#define adc_ANALOG_WD_MASK                       0x00000001