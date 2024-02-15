#include "stm32f1xx_it.h"
#include "user_oled.h"

#include "user_key.h"
#include "gpio.h"
#include "tsl2561.h"
uint8_t button=100;
uint8_t last_button=99;
float light_ret;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0)
	{
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) ==  0)
		{
//			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1);
			HAL_Delay(200);
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) ==  0) {
			TSL2561_LED_on();
			TSL2561_PowerOn();
			User_Detect_Show();
			HAL_Delay(200);
			User_Data_Show();
			}
			else {
				TSL2561_PowerDown();
				TSL2561_LED_off();
			}
		}
	}
	if(GPIO_Pin == GPIO_PIN_8)
	{
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8) ==  1)
		{
			light_ret=Read_Light();
			TSL2561_PowerDown();
			TSL2561_LED_off();
		}
	}
}

