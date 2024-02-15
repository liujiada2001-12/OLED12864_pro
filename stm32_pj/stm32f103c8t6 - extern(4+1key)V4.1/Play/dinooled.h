#ifndef __OLED_H
#define __OLED_H

#include "main.h"

#define u8 uint8_t
#define u32 uint32_t

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

#define OLED0561_ADD	0x78  // OLED I2C地址
#define COM				0x00  // OLED 
#define DAT 			0x40  // OLED 

#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF
#define X_WIDTH 	128
#define Y_WIDTH 	64


//-----------------OLED IIC GPIO进行模拟----------------

#define OLED_SCLK_Clr() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET) //GPIO_ResetBits(GPIOB,GPIO_Pin_10)//SCL
#define OLED_SCLK_Set() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET) //GPIO_SetBits(GPIOB,GPIO_Pin_10)

#define OLED_SDIN_Clr() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET) // GPIO_ResetBits(GPIOB,GPIO_Pin_11)//SDA
#define OLED_SDIN_Set() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET) // GPIO_SetBits(GPIOB,GPIO_Pin_11)


//I2C GPIO模拟
void IIC_Start();
void IIC_Stop();
void IIC_WaitAck();
void IIC_WriteByte(unsigned char IIC_Byte);
void IIC_WriteCommand(unsigned char IIC_Command);
void IIC_WriteData(unsigned char IIC_Data);
void OLED_WR_Byte1(unsigned dat,unsigned cmd);


//功能函数
void OLED_Init1(void);
void OLED_WR_Byte1(unsigned dat,unsigned cmd);

void OLED_FillPicture1(unsigned char fill_Data);
void OLED_SetPos1(unsigned char x, unsigned char y);
void OLED_DisplayOn1(void);
void OLED_DisplayOff1(void);
void OLED_Clear1(void);
void OLED_On1(void);
void OLED_ShowChar1(u8 x,u8 y,u8 chr,u8 Char_Size);
u32 oled_pow1(u8 m,u8 n);
void OLED_ShowNum1(u8 x,u8 y,u32 num,u8 len,u8 size2);
void OLED_ShowString1(u8 x,u8 y,u8 *chr,u8 Char_Size);

#endif