#ifndef __USER_KEY_H
#define __USER_KEY_H
#include "stdint.h"
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void user_key_deal(uint8_t button);
#endif 