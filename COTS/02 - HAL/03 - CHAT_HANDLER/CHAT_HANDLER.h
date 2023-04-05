/*******************************************************************/
/*         CHAT_HANDLER Driver        */
/* Target:STM32F401CC                       */
/*Author :Yousef_Ahmed                         */
/*Date   :2023-04-04                                      */
/*******************************************************************/

#ifndef _CHAT_HANDLER_H
#define _CHAT_HANDLER_H

#include "CHAT_HANDLER_cfg.h"

typedef enum{

    chat_handler_Idle,
    chat_handler_Busy

}CHAT_HANDLER_State_t;

typedef enum{

    chat_handler_Ok,
    chat_handler_NotOk,
    chat_handler_NullPtr

}CHAT_HANDLER_Error_t;

typedef void (*chat_handler_cbf)(void);

/*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  : void                                                                                                        */
/* Return :  void                                                                                                        */
/*************************************************************************************************************************/
extern void chat_handler_Init(void);

/*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  : void                                                                                                        */
/* Return :  void                                                                                                        */
/*************************************************************************************************************************/
extern CHAT_HANDLER_Error_t chat_handler_SendMessage(u8 *Addp_Message , chat_handler_cbf Notify);

/*************************************************************************************************************************/
/* FunctionDiscription  :                                                                                                */
/* Inputs  : void                                                                                                        */
/* Return :  void                                                                                                        */
/*************************************************************************************************************************/
extern CHAT_HANDLER_Error_t chat_handler_RecieveMessage(u8 *Addp_Message , chat_handler_cbf Notify);

#endif /*CHAT_HANDLER_H*/
