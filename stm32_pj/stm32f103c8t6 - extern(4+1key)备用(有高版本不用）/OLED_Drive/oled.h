#ifndef __OLED_H
#define __OLED_H

#include "stdint.h"
#include "gpio.h"
#include "core_cm3.h"
void OLED_Init(void);
void OLED_Clear(void);
void OLED_Clear1(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowFloat(uint8_t Line, uint8_t Column,float Number1,int Length);

void OLED_Chinese(uint8_t Line, uint8_t Column, char Char);
void OLED_Chinese16(uint8_t Line, uint8_t Column, char Char);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_Refresh(void);
void OLED_ShowPicture(uint8_t x,uint8_t y,uint8_t sizex,uint8_t sizey,const uint8_t BMP[],uint8_t mode);


void OLED_I2C_SendByte(uint8_t Byte);
void OLED_SetCursor(uint8_t Y, uint8_t X);
void OLED_I2C_Start(void);
void OLED_WriteCommand(uint8_t Command);
void OLED_I2C_WaitAck(void);
void OLED_I2C_Stop(void);
#endif
