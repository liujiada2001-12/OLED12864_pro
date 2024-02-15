#ifndef __TSL2561_I2C_H
#define __TSL2561_I2C_H

#include "gpio.h"

void TSL2561_I2C_Init(void);

void TSL2561_I2C_Start(void);
void TSL2561_I2C_Stop(void);

void TSL2561_I2C_Write_Byte(uint8_t byte);
uint8_t TSL2561_I2C_Read_Byte(void);

void TSL2561_I2C_Write_ACK(uint8_t ack);
uint8_t TSL2561_I2C_Read_ACK(void);



#define TSL2561_W_SCL(x)		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, x)
#define TSL2561_W_SDA(x)		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, x)
#define TSL2561_R_SCL		HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)
#define TSL2561_R_SDA		HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)
#endif
