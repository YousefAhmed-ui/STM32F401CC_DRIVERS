


#include "RCC.h"
#include "GPIO.h"



int main(void)
{
	RCC_PllConfigParams_t Local_strPLLConfig = {HSE_PLL_SRC,16,192,8,2};
	rcc_controlSysClock(rcc_HSE,clock_ON);
	rcc_configPLL(Local_strPLLConfig);
	rcc_controlSysClock(rcc_PLL,clock_ON);
	rcc_selectSysClock(rcc_HSE);
	rcc_EnableAHB1Preipherals(rcc_AHB1_GPIOC);
	GPIO_strInit_t Led_pin;
	Led_pin.GPIO_Mode = gpio_OUPUT_PP_MODE;
	Led_pin.GPIO_Port = GPIO_PORTC;
	Led_pin.GPIO_Speed = gpio_VERY_HIGH_SPEED;
	Led_pin.GPIO_Pin = gpio_PIN13;
	gpio_Init(&Led_pin);
	gpio_SetPinValue(gpio_PORTC , gpio_PIN13 , GPIO_SET_VALUE);

	//rcc_DisableAHB1Preipherals(rcc_AHB1_GPIOA);


	while(1)
	{

	}
	return 0;
}
