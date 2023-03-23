/*******************************************************************/
/*         SCHED Driver        */
/* Target:STM32F401CC                       */
/*Author :Yousef_Ahmed                         */
/*Date   :2023-03-18                                      */
/*******************************************************************/

#ifndef _SCHED_H
#define _SCHED_H

#include "SCHED_cfg.h"

typedef enum{
    sched_Ok,
    sched_NotOk
}SchedError_t;


/*************************************************************************************************************************/
/* FunctionDiscription  : intitialize the hardware necessary for sched                                                   */
/* Inputs  : void                                                                                                        */
/* Return :  void                                                                                                        */
/*************************************************************************************************************************/ 
extern void sched_Init(void);
/*************************************************************************************************************************/
/* FunctionDiscription  : start the sched                                                                                */
/* Inputs  : void                                                                                                        */
/* Return :  Error status                                                                                                */
/*************************************************************************************************************************/ 
extern void sched_Start(void);
/*************************************************************************************************************************/
/* FunctionDiscription  : this function maneuvers the sched to work in thread mode                                       */
/* Inputs  : void                                                                                                        */
/* Return :  void                                                                                                        */
/*************************************************************************************************************************/ 
extern void sched_cbf(void);

#endif /*SCHED_H*/
