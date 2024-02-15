#ifndef __USER_KEY_H
#define __USER_KEY_H
#include "stdint.h"

typedef struct{
	int up;
	int down;
	int enter;
	int back;
	int detect_key;
}user_key_t;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
uint8_t user_key_deal(user_key_t u);
#endif 