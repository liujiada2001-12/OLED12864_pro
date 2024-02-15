#ifndef __TSL2561_H
#define __TSL2561_H
#include "gpio.h"

void TSL2561_Init(void);
uint16_t TSL2561_ReadData(void);
void TSL2561_on(void);
void TSL2561_off(void);
void TSL2561_LED_on(void);
#endif
