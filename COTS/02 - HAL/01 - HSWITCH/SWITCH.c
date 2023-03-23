/*************************************************************************************************************************/
/* author : yousef ahmed                                                                                                 */
/* date   : 21/2/2023                                                                                                    */
/* version: V01                                                                                                          */
/*************************************************************************************************************************/ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO.h"
#include "SWITCH.h"

extern const SWITCHCfg_t switchs[switch_count];

static u8 switch_state[switch_count];

void switch_Init(void)
{
    GPIO_strInit_t Switch_cfg;
    u8 Local_u8Index = 0;
    for(Local_u8Index = 0 ; Local_u8Index < switch_count ; Local_u8Index++)
    {
        if(switchs[Local_u8Index].switch_Mode == switch_INPUT_FLOATING)
        {
            Switch_cfg.GPIO_Mode = gpio_INPUT_FLOATING;
        }
        else if(switchs[Local_u8Index].switch_Mode == switch_INPUT_PD)
        {
            Switch_cfg.GPIO_Mode = gpio_INPUT_PD;
        }
        else // INPUT PU
        {
            Switch_cfg.GPIO_Mode = gpio_INPUT_PU;
        }
        Switch_cfg.GPIO_Pin = switchs[Local_u8Index].switch_Pin;
        Switch_cfg.GPIO_Port = switchs[Local_u8Index].switch_Port;

        gpio_Init(&Switch_cfg);
    }
}
SWITCHErrorStatus_t switch_GetState(u8 Copy_SwitchNum , u8 * Copy_u8Value )
{
    SWITCHErrorStatus_t Local_enuErrorStatus = switch_Ok;
    if( Copy_SwitchNum > switch_count )
    {
        Local_enuErrorStatus = switch_NotOk;
    }
    else
    {
        *Copy_u8Value = switch_state[Copy_SwitchNum] ^ switchs[Copy_SwitchNum].switch_Mode;
    }
}


// call every 5ms
void Switch_Task(void)
{
    u8 Local_u8CurrentVal[switch_count];
    static u8 Local_u8PrvVal[switch_count];
    static u8 Local_u8Counter[switch_count];
    u8 Local_u8iterator;

    for(Local_u8iterator = 0 ; Local_u8iterator < switch_count ; Local_u8iterator++)
    {
         gpio_GetPinValue(switchs[Local_u8iterator].switch_Port , switchs[Local_u8iterator].switch_Pin  , &Local_u8CurrentVal[Local_u8iterator]);

         if(Local_u8CurrentVal[Local_u8iterator] == Local_u8PrvVal[Local_u8iterator])
         {
            Local_u8Counter[Local_u8iterator]++;
         }
         else
         {
            Local_u8Counter[Local_u8iterator] = 0;
         }

         if(Local_u8Counter == 5)
         {
            switch_state[Local_u8iterator] = Local_u8CurrentVal[Local_u8iterator];
            Local_u8Counter[Local_u8iterator] = 0;
         }

         Local_u8PrvVal[Local_u8iterator] = Local_u8CurrentVal[Local_u8iterator];
    }



    
}