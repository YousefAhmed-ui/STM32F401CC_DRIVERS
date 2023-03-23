/*************************************************************************************************************************/
/* author : yousef ahmed                                                                                                 */
/* date   : 21/2/2022                                                                                                     */
/* version: V01                                                                                                          */
/*************************************************************************************************************************/ 
#ifndef HLED_H 
#define HLED_H 

#include "HLED_cfg.h"

typedef enum{
    LED_Ok,
    LED_NotOk
}LEDErrorStatus_t;

#define led_STATE_ON                            0
#define led_STATE_OFF                           1

#define led_ACTIVE_HIGH                         0
#define led_ACTIVE_LOW                          1

#define led_LOW_SPEED                           0
#define led_MEDIUM_SPEED                        1
#define led_HIGH_SPEED                          2
#define led_VERY_HIGH_SPEED                     3

#define led_OUTPUT_TYPE_PP                      0
#define led_OUTPUT_TYPE_OD                      1

#define LED_COUNT                               65536
/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/
LEDErrorStatus_t led_Init(void);
/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/
LEDErrorStatus_t led_SetState(u16 Copy_Led , u8 Copy_State);

#endif
