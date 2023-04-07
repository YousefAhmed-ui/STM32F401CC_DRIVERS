/******************************************************************/
/*TEMP_SENSOR Driver                */
/* Target:STM32F401CC                       */
/* Yousef_Ahmed                              */
/* Date:2023-04-08                                       */
/******************************************************************/
#include "STD_TYPES.h"
#include "ADC.h"
#include "ADC_MX1000.h"
#include "TEMP_SENSOR.h"


TEMP_SENSOR_ERROR_t temp_sensor_GetTempInternal(u16 * Addp_Temp)
{
    adc_GetValueAsync( Addp_Temp);
   
}
TEMP_SENSOR_ERROR_t temp_sensor_GetTempExternal(u16 * Addp_Temp)
{
    adc_MX1000_GetValueSync( Addp_Temp);
}