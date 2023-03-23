/******************************************************************/
/*SCHED Driver                 */
/* Target:STM32F401CC                       */
/* Yousef_Ahmed                               */
/* Date:2023-03-18                                       */
/******************************************************************/


#include "STD_TYPES.h"
#include "SCHED.h"
#include "App.h"


void App1_Runnable(void){}

const Task_info_t Tasks_info[NUM_OF_TASKS] = {
    [0] = {
        .Name = "App1",
        .Period = 100,
        .StartDelay = 0,
        .Task_cbf = Led1
    },
    [1] = {
        .Name = "App2",
        .Period = 200,
        .StartDelay = 100,
        .Task_cbf = Led2
    },
	[2] = {
	    .Name = "App2",
	    .Period = 300,
	    .StartDelay = 200,
	    .Task_cbf = Led3
	}

};
