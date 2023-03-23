

#include "STD_TYPES.h"

#include "RCC.h"
#include "GPIO.h"
#include "HLED.h"


int main(void)
{
	rcc_controlSysClock(rcc_HSE , clock_ON);
	rcc_selectSysClock(rcc_HSE);
	rcc_EnableAHB1Preipherals(rcc_AHB1_GPIOC);
	//rcc_controlPrescalerAHB(rcc_AHB_CLK_DIVIDED_BY_);
	//led_Init();
	//led_SetState( LED_Start , led_STATE_ON);
	while(1)
	{

	}
	return 0;
}
