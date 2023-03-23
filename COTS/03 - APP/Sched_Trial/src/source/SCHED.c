/******************************************************************/
/*SCHED Driver                */
/* Target:STM32F401CC                       */
/* Yousef_Ahmed                              */
/* Date:2023-03-18                                       */
/******************************************************************/
#include "STD_TYPES.h"
#include "SCHED.h"
#include "SYSTICK.h"
#include "diag/Trace.h"


static SchedError_t sched(void);

typedef struct{
    const Task_info_t * Task_info;
    u16 RemainTime;
}Task_t;

static u8 SchedFlag;

Task_t Tasks[NUM_OF_TASKS];

extern const Task_info_t Tasks_info[NUM_OF_TASKS];

void sched_Init(void)
{
    u8 Local_u8Iter = 0;

    stk_SetTickTime(stk_CLOCK_SOURCE_AHB);

    stk_SetPeriod_ms( TICKS , CLOCK);

    stk_SetCbf(sched_cbf);

    stk_SetInterrupt(stk_INT_ON);

    for(Local_u8Iter = 0 ; Local_u8Iter < NUM_OF_TASKS ; Local_u8Iter++)
    {
        Tasks[Local_u8Iter].Task_info = &Tasks_info[Local_u8Iter];
        Tasks[Local_u8Iter].RemainTime = Tasks_info[Local_u8Iter].StartDelay;
    }
}

void sched_Start(void)
{
    stk_Start();

    while(1){
        if(SchedFlag == 1)
        {
            sched();
            SchedFlag = 0;
        }

    }
}

SchedError_t sched(void)
{
    u8 Local_u8Iter = 0;

    for(Local_u8Iter = 0 ; Local_u8Iter < NUM_OF_TASKS ; Local_u8Iter++)
    {
        if(Tasks[Local_u8Iter].Task_info)
        {
            if(Tasks[Local_u8Iter].RemainTime == 0)
            {
                  Tasks[Local_u8Iter].Task_info->Task_cbf();
                  Tasks[Local_u8Iter].RemainTime = Tasks[Local_u8Iter].Task_info->Period;
            }
            Tasks[Local_u8Iter].RemainTime -= TICKS;
        }
    }
}

void sched_cbf(void)
{
    if(SchedFlag == 0)
    {
        SchedFlag = 1;
    }
    else
    {
        trace_printf("100 percent cpu usage");
    }
}
