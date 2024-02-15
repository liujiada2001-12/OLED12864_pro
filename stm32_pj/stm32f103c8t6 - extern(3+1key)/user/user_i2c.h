#ifndef __USER_I2C_H
#define __USER_I2C_H
#include "gpio.h"


#define I2C_Address 0x54
#define I2C_SCL_GPIOx GPIOB
#define I2C_SCL_Pin GPIO_PIN_10
#define I2C_SDA_GPIOx GPIOB
#define I2C_SDA_Pin GPIO_PIN_11
#define I2C_SDA_Pinx 1 // GPIO_PIN_x дx

/*
IIC����
��Ҫ:2��GPIO
    ��©�������ģʽ
*/

// #define I2C_Host

/*
IIC�ӻ�
��Ҫ:2��GPIO
    �����ж�,����
*/

#define I2C_Slave

extern uint8_t I2C_Slave_Add;
extern uint8_t Reg_Add;
extern uint8_t I2C_Slave_RX_Buf;

// IIC���в�������
uint8_t I2C_SendByte(uint8_t dat); // I2C����һ���ֽ�
uint8_t I2C_ReadByte(uint8_t ack); // I2C��ȡһ���ֽ�
uint8_t I2C_Write_Reg(uint8_t reg, uint8_t data);
uint8_t I2C_Read_Reg(uint8_t reg);
uint8_t I2C_Read_Len(uint8_t reg, uint8_t len, uint8_t *buf);
uint8_t I2C_Write_Len(uint8_t reg, uint8_t len, uint8_t *buf);
void I2C_Slave_IRQ_SCL(void);
void I2C_Slave_IRQ_SDA(void);
#endif
