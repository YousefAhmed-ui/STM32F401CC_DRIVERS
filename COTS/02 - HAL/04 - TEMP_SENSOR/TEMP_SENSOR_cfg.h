/*******************************************************************/
/*         TEMP_SENSOR Driver         */
/* Target:STM32F401CC                       */
/*Author :Yousef_Ahmed                         */
/*Date   :2023-04-08                                      */
/*******************************************************************/

#ifndef _TEMP_SENSOR_CFG_H
#define _TEMP_SENSOR_CFG_H

#include "ADC.h"
#include "GPIO.h"


#define ADC_INTERNAL                0
#define ADC_EXTERNAL                1


/*
    ADC_INTERNAL
    ADC_EXTERNAL  */

#define ADC   ADC_INTERNAL

typedef struct{

    struct{

        ADC_t ADC;
        GPIO_strInit_t Pins[10];

    }INTERNAL_ADC;

    struct{

        ADC_MX100_t ADC;
        GPIO_strInit_t Pins[10];

    }EXTERNAL_ADC;


}ADC_cfg_t;

#endif /*TEMP_SENSOR_CFG_H*/
