#ifndef __MENU_H
#define __MENU_H
 
#include "main.h"
#define  u8 unsigned char
 
 
 
typedef struct
{
    u8 current;	//当前状态索引号
    u8 up; 		//向上0一个
		u8 down;		//向下一个
    u8 enter; 	//确定
		u8 back; 		//退出
	  u8 detect;
    void (*current_operation)(void); //当前状态应该执行的操作
} Menu_table;
 
//界面UI
void home();
void Time();
void Data();
void LOG();
void LOG1();
void Play();
void Play1();
void Video();
void Video1();

void Datashow();
void Timeshow();
void LOGshow();
void Playshow();
void Temperature();
void Palygame(); 
 
void  Menu_key_set(uint8_t button);
u8 KEY_Scan(u8 mode);
 
void TestTemperature();
void ConrtolGame();
void Set();

 
void LED();
void RTC_display();
 
#endif