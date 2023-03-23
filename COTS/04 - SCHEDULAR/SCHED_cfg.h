/*******************************************************************/
/*         SCHED Driver         */
/* Target:STM32F401CC                       */
/*Author :Yousef_Ahmed                         */
/*Date   :2023-03-18                                      */
/*******************************************************************/

#ifndef _SCHED_CFG_H
#define _SCHED_CFG_H

#include "SYSTICK.h"

#define  NUM_OF_TASKS               3

#define TICKS    1

#define CLOCK    stk_AHB_CLOCK_HSE

typedef void (*Cbf)(void);

typedef struct{
    u8 *Name;
    Cbf Task_cbf;
    u16 Period;
    u16 StartDelay;

}Task_info_t;




#endif /*SCHED_CFG_H*/
