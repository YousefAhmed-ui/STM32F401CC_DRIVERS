
#include "STD_TYPES.h"
#include "RCC.h"
#include "GPIO.h"
#include "NVIC.h"
#include "HLED.h"
#include <diag/Trace.h>

int main(void)
{
	rcc_controlSysClock(rcc_HSE,clock_ON);
	rcc_selectSysClock(rcc_HSE);
	rcc_EnableAHB1Preipherals(rcc_AHB1_GPIOC);
	nvic_SetPriorityGrouping(PRIORITY_GROUP_2_SUB_2);
	nvic_SetPriority(nvic_IRQ_6 , PRIORITY_IRQ_4);
	nvic_SetPriority(nvic_IRQ_7,PRIORITY_IRQ_0);
	led_Init();
	nvic_EnableIRQ(nvic_IRQ_6);
	nvic_SetPendingIRQ(nvic_IRQ_6);
	while(1)
	{

	}
	return 0;
}

void EXTI0_IRQHandler(void)
{
	led_SetState(LED_Start,led_STATE_ON);
	nvic_EnableIRQ(nvic_IRQ_7);
	nvic_SetPendingIRQ(nvic_IRQ_7);

	while(1);
}
void EXTI1_IRQHandler(void)
{
	trace_printf("this is preemption");
}
