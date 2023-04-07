/*******************************************************************/
/*         TEMP_SENSOR Driver        */
/* Target:STM32F401CC                       */
/*Author :Yousef_Ahmed                         */
/*Date   :2023-04-08                                      */
/*******************************************************************/

#ifndef _TEMP_SENSOR_H
#define _TEMP_SENSOR_H

#include "TEMP_SENSOR_cfg.h"



typedef enum{

    temp_sensor_Ok,
    temp_sensor_NotOk

}TEMP_SENSOR_ERROR_t;

typedef enum{

    adc_Internal,
    adc_External


}adc_Channel_t;

/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/
extern TEMP_SENSOR_ERROR_t temp_sensor_GetTemp(u16 * Addp_Temp);


#endif /*TEMP_SENSOR_H*/
