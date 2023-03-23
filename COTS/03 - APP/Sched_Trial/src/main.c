


#include "STD_TYPES.h"
#include "RCC.h"
#include "SYSTICK.h"
#include "SCHED.h"
#include "HLED.h"

int main(void)
{

	rcc_controlSysClock(rcc_HSE , clock_ON);
	rcc_selectSysClock(rcc_HSE);
	rcc_EnableAHB1Preipherals(rcc_AHB1_GPIOC);
	led_Init();
	sched_Init();
	sched_Start();

	return 0;
}
