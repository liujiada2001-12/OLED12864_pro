#ifndef __TSL2561_H
#define __TSL2561_H
#include "gpio.h"

/*设备地址*/
#define ADDR_SEL_GND 0x29//ADDR脚接地
#define ADDR_SEL_FLOAT 0x39//ADDR脚浮空
#define ADDR_SEL_VDD 0x49//ADDR脚接Vdd

/*写命令是将0x80|addr(寄存器地址)*/
//命令控制寄存器
#define TSL2561_CMD 0x80//控制寄存器控制芯片是否工作
#define TIMING 0x81//时间寄存器控制增益和积分时间
#define Llimit_Lbyte 0x82//低门限低字节
#define Llimit_Hbyte 0x83//低门限高字节
#define Hlimit_Lbyte 0x84//高门限低字节
#define Hlimit_Hbyte 0x85//高门限高字节
#define INT_CTRL 0x86
#define TSL2561_REG_ID 0x8A//区分TSL2560和TSL2561
#define DATA0LOW 0x8C//通道0低字节
#define DATA0HIGH 0x8D//通道0高字节
#define DATA1LOW 0x8E//通道1低字节
#define DATA1HIGH 0x8F//通道1高字节

/*控制寄存器数据*/
#define POWER_UP 0x03//设备上电
#define POWER_DOWN 0x00//设备断电

//Timing Register Value.Set integration time
//最后两位设置积分时间
#define TIMING_13MS 0x00 //积分时间13.7毫秒
#define TIMING_101MS 0x01 //积分时间101毫秒
#define TIMING_402MS 0x02 //积分时间402毫秒
/*增益倍数与积分时间进行或运算*/
#define TIMING_GAIN_1X 0x00 //增益1
#define TIMING_GAIN_16X 0x10 //增益16倍

void TSL2561_Init(uint8_t Time_model);
void TSL2561_Write(uint8_t command, uint8_t data);
uint8_t TSL2561_Read(uint8_t command);
uint32_t Read_Light(void);
void TSL2561_LED_on(void);
void TSL2561_LED_off(void);

void TSL2561_PowerOn(void);
void TSL2561_PowerDown(void);



//void TSL2561_Init(void);
//uint16_t TSL2561_ReadData(void);
//void TSL2561_on(void);
//void TSL2561_off(void);
//void TSL2561_LED_on(void);
#endif
