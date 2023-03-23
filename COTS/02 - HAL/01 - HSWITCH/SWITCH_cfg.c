/*************************************************************************************************************************/
/* author : yousef ahmed                                                                                                 */
/* date   : 21/2/2023                                                                                                    */
/* version: V01                                                                                                          */
/*************************************************************************************************************************/ 
#include "STD_TYPES.h"
#include "GPIO.h"

#include "SWITCH.h"

const SWITCHCfg_t switchs[switch_count] = {
    [switch_Start] = {
        .switch_Mode = switch_INPUT_PU,
        .switch_Pin = gpio_PIN4,
        .switch_Port = GPIO_PORTA
    }
};