#include "stm32f1xx_it.h"
#include "user_oled.h"
#include "user_lightdata.h"
#include "user_key.h"
#include "gpio.h"
#include "tsl2561.h"
uint8_t button=100;
uint8_t last_button=99;
int choice=0;
extern int data_num;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0)
	{
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) ==  0)
		{
//			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1);
			HAL_Delay(10);
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) ==  0) {
			TSL2561_on();
			User_Detect_Show();
			HAL_Delay(200);
			User_Data_Show();
			choice=data_num;
			}
			else TSL2561_off();
		}
	}
	if(GPIO_Pin == GPIO_PIN_1)
	{
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1) ==  0)
		{
			HAL_Delay(10);
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1) ==  0) {
			choice--;

			if(choice>=data_num) choice=data_num;
			if(choice<0) choice=0;
			User_DataChoice_Show(choice);
			}
		}
	}
	if(GPIO_Pin == GPIO_PIN_2)
	{
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2) ==  0)
		{
			HAL_Delay(10);
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2) ==  0) {
			choice++;
			
			if(choice>=data_num) choice=data_num;
			if(choice<0) choice=0;
			User_DataChoice_Show(choice);
			}
		}
	}
}

