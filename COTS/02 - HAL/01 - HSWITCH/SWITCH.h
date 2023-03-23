/*************************************************************************************************************************/
/* author : yousef ahmed                                                                                                 */
/* date   : 21/2/2023                                                                                                    */
/* version: V01                                                                                                          */
/*************************************************************************************************************************/ 
#ifndef SWITCH_H
#define SWITCH_H

#include "SWITCH_cfg.h"



#define switch_STATE_PRESSED             0
#define switch_STATE_RELEASED            1

#define switch_INPUT_PU                  0
#define switch_INPUT_PD                  1
#define switch_INPUT_FLOATING            2



typedef enum{
    switch_Ok,
    switch_NotOk
}SWITCHErrorStatus_t;


/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/
extern void switch_Init(void);
/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/
extern SWITCHErrorStatus_t switch_GetState(u16 Copy_Led , u8 * Copy_u8Value , u8 Copy_State);
/*************************************************************************************************************************/
/* Function_Description :                                                                                                */
/* Inputs   :                                                                                                            */
/* Return   : Error_status either ok or not                                                                              */
/*************************************************************************************************************************/
extern void switch_Task(void);

#endif