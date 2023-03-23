


#include "STD_TYPES.h"
#include "RCC.h"
#include "GPIO.h"
#include "SYSTICK.h"
#include "HLED.h"


void Notify(void)
{
	static u16 Counter = 0;
	Counter++;
	if( Counter % 200 == 0 )
	{
		led_SetState( LED_Start , led_STATE_OFF);
	}
}

int main(void)
{
	rcc_controlSysClock(rcc_HSE,clock_ON);
	rcc_selectSysClock(rcc_HSE);
	rcc_EnableAHB1Preipherals(rcc_AHB1_GPIOC);
	led_Init();
	stk_SetTickTime(stk_CLOCK_SOURCE_AHB);
	stk_SetPeriod_ms( 5 , stk_AHB_CLOCK_HSE );
	stk_SetInterrupt(stk_INT_ON);
	stk_SetCbf(Notify);
	stk_Start();
	while(1)
	{

	}
	return 0;
}
