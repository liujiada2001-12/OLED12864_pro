#ifndef __MENU_H
#define __MENU_H
 
#include "main.h"
#define  u8 unsigned char
 
 
 
typedef struct
{
    u8 current;	//��ǰ״̬������
    u8 up; 		//����0һ��
		u8 down;		//����һ��
    u8 enter; 	//ȷ��
		u8 back; 		//�˳�
	  u8 detect;
    void (*current_operation)(void); //��ǰ״̬Ӧ��ִ�еĲ���
} Menu_table;
 
//����UI
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