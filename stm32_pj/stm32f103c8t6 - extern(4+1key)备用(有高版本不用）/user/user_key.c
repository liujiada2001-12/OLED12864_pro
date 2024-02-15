#include "stm32f1xx_it.h"
#include "user_oled.h"

#include "user_key.h"
#include "gpio.h"
#include "menu.h"
uint8_t button=100;
uint8_t last_button=99;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_1)
	{
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1) ==  0)
		{
//			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1);
			for(int i=0;i<200;i++);
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1) ==  0) {button=1;}
		}
	}
	
	if(GPIO_Pin == GPIO_PIN_2)
	{
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2) ==  0)
		{
//			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,0);
			for(int i=0;i<200;i++);
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2) ==  0) {button=2;}
		}
	}
	
	if(GPIO_Pin == GPIO_PIN_3)
	{
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3) ==  0)
		{
//			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1);
			for(int i=0;i<200;i++);
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3) ==  0) {button=3;}
		}
	}
	if(GPIO_Pin == GPIO_PIN_4)
	{
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4) ==  0)
		{
//			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1);
			for(int i=0;i<200;i++);
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4) ==  0) {button=4;}
		}
	}
	Menu_key_set(button);
//	last_button=button;
//	user_key_deal(button);
}

void user_key_deal(uint8_t button)
{
		switch(button)
		{
			case 1:
			{
				User_Init_Show();
				break;
			}
			case 2:
			{
				User_PIC_Show();
				break;
			}
			case 3:
			{
				User_Data_Show();
				break;
			}

		}
}