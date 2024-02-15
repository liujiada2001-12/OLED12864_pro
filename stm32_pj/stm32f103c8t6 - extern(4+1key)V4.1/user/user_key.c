#include "stm32f1xx_it.h"
#include "user_oled.h"
#include "user_lightdata.h"
#include "user_key.h"
#include "gpio.h"
#include "tsl2561.h"
#include "menu.h"
int choice=0;
extern int data_num;

user_key_t user_key;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	uint8_t button=99;
	if(GPIO_Pin == GPIO_PIN_0)
	{
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) ==  0)
		{
//			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1);
			HAL_Delay(10);
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) ==  0) {user_key.detect_key=0;button=0;}
			else user_key.detect_key=1;
		}
//		lightdata_detect();
	}
	if(GPIO_Pin == GPIO_PIN_1)
	{
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1) ==  0)
		{
			HAL_Delay(10);
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1) ==  0) {user_key.up=0;button=1;}
			else user_key.up=1;
		}
//		lightdata_up();
	}
	if(GPIO_Pin == GPIO_PIN_2)
	{
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2) ==  0)
		{
			HAL_Delay(10);
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2) ==  0) {user_key.down=0;button=2;}
			else user_key.down=1;
		}
//		lightdata_down();
	}
	if(GPIO_Pin == GPIO_PIN_3)
	{
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3) ==  0)
		{
			HAL_Delay(10);
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3) ==  0) {user_key.enter=0;button=3;}
			else user_key.enter=1;
		}
//		lightdata_delete();
	}
	if(GPIO_Pin == GPIO_PIN_4)
	{
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4) ==  0)
		{
			HAL_Delay(10);
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4) ==  0) {user_key.back=0;button=4;}
			else user_key.back=1;
		}
	}
	
	Menu_key_set(	button);
}
