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


TEMP_SENSOR_ERROR_t temp_sensor_GetTemp(u16 * Addp_Temp)
{
    #if ADC == ADC_INTERNAL
         adc_GetValueAsync(  Addp_Temp , NULL);
    #endif
    #if ADC == ADC_EXTERNAL
        adc_MX1000_GetValueAsync( Addp_Temp , NULL );
    #endif    
}