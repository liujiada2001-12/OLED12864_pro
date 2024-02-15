#include "menu.h"
#include "oled.h"
#include "gpio.h"
//#include "dinogame.h"
//#include "control.h"
#include "rtc.h"
#include "user_oled.h"
#include "user_lightdata.h"
#include "video.h"
#include "control.h"
RTC_DateTypeDef GetData;  //��ȡ���ڽṹ��
 
RTC_TimeTypeDef GetTime;   //��ȡʱ��ṹ��
 
 
//UI����
//��ҳ
/****************************************************/
//UI��
 
/****************************************************/
 
void (*current_operation_index)();	 

Menu_table  table[30]=
{
    {0,0,0,1,0,0,(*home)},	//һ�����棨��ҳ�棩 �������ϣ��£�ȷ�����˳�
		
    {1,4,2,5,0,13,(*Data)},	//�������� ����
    {2,1,3,6,0,2,(*Time)},	//�������� ����
    {3,2,4,7,0,3,(*LOG)},	//�������� LOG
    {4,3,1,8,0,4,(*Play)},	//�������� ����
		
		{5,9,10,11,1,13,(*lightdata_show)},		//�������棺��������
		{6,6,6,6,2,6,(*Timeshow)},				//�������棺ʱ�����
		{7,7,7,7,14,7,(*LOGshow)},								//�������棺УԺ��LOG��ʾ
		{8,8,8,8,4,8,(*Game_control)},				//�������棺���ߺ������Ŀ��Ϣ
 
		{9,9,10,11,1,13,(*lightdata_up)},		//
		{10,9,10,11,1,13,(*lightdata_down)},		//
		{11,11,11,12,5,11,(*lightdata_askfordelete)},		//
		{12,9,10,11,1,13,(*lightdata_delete)},
		{13,9,10,11,1,13,(*lightdata_detect)},
		
		{14,2,4,7,0,3,(*LOG1)},	//�������� LOG
		{15,3,1,8,0,4,(*Play1)}
};
 
uint8_t  func_index = 0;	//�������ʱ���ڳ��������ֵ
 
void  Menu_key_set(uint8_t button)
{
	if((button == 0) && (func_index != 6))
  { 
    func_index=table[func_index].detect;	//����UP���º��������
    OLED_Clear(); 
  }
	
	
  if((button == 1) && (func_index != 6))
  { 
    func_index=table[func_index].up;	//����UP���º��������
    OLED_Clear(); 
  }
	
  if((button == 2) && (func_index != 6))
  {
    func_index=table[func_index].down;	//����down���º��������
    OLED_Clear();
  }
 
	if((button == 3) && (func_index != 6))
  {
    func_index=table[func_index].enter;	//����enter���º��������
    OLED_Clear(); 
  }
	if(button == 4)
  {
    func_index=table[func_index].back;	//����back���º��������
    OLED_Clear(); 
  }
	
  current_operation_index=table[func_index].current_operation;	//ִ�е�ǰ����������Ӧ�Ĺ��ܺ���
  (*current_operation_index)();//ִ�е�ǰ��������
}
 

void Data()
{
	User_Data();
}

void Time()
{
	while(1)
	{
	User_Time();
	}
}

 
void home()
{
	User_Home();
}
 
void LOG()
{
	User_LOG();
}
void LOG1()
{
	User_LOG1();
}
void Play()
{
	User_Play();
}
void Play1()
{
	User_Play1();
}
void Video()
{
	User_Video();
}
void Video1()
{
	User_Video1();
}

void Datashow()
{
	User_Data_Show();
}

void Timeshow()
{
	User_PIC_Show();
}

void LOGshow()
{
	User_huizhang_Show();
}
extern int game_flag;
void Playshow()
{
//	game_flag=1;
//	Game_control();
//	OLED_ShowString(0,0,"Author:Sneak",16);
//	OLED_ShowString(0,2,"Date:2022/8/23",16);
//	OLED_ShowString(0,4,"Lab: Multi-level menu",16);
}

void Temperature()
{
	OLED_ShowString(2,1,"Temperature");
//	RTC_display();
//	OLED_DrawBMP(0,0,20,3,signal_BMP);
//	OLED_DrawBMP(20,0,36,2,gImage_bulethouch);
//	OLED_DrawBMP(112,0,128,2,gImage_engery);
//	OLED_DrawBMP(4,6,20,8,gImage_yes);
//	OLED_DrawBMP(12,4,28,6,gImage_left);
//	OLED_DrawBMP(40,2,88,8,gImage_temp);
//	OLED_DrawBMP(99,4,115,6,gImage_right);
//	OLED_DrawBMP(107,6,123,8,gImage_back);
}
 
void Palygame()
{
	OLED_ShowString(2,1,"Temperature");
//	RTC_display();
//	OLED_DrawBMP(0,0,20,3,signal_BMP);
//	OLED_DrawBMP(20,0,36,2,gImage_bulethouch);
//	OLED_DrawBMP(112,0,128,2,gImage_engery);
//	OLED_DrawBMP(4,6,20,8,gImage_yes);
//	OLED_DrawBMP(12,4,28,6,gImage_left);
//	OLED_DrawBMP(40,2,88,8,gImage_playgame);
//	OLED_DrawBMP(99,4,115,6,gImage_right);
//	OLED_DrawBMP(107,6,123,8,gImage_back);
}
 
 

 
 
 
void TestTemperature()
{
	OLED_ShowString(2,1,"Temperature");
//	DHT11();
}
 
void ConrtolGame()
{
	OLED_ShowString(2,1,"ConrtolGame");
//	Game_control();
}
 
void Set()
{
	OLED_ShowString(2,1,"Set");
//	OLED_ShowString(0,0,"Peripherals: Lights",16);
//	OLED_ShowString(0,2,"Status: Closed",16);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
}
 

 
void LED()
{
	OLED_ShowString(2,1,"LED");
//	OLED_ShowString(0,0,"Peripherals: Lights",16);
//	OLED_ShowString(0,2,"Status: Open",16);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
}
 
 
 
void RTC_display()				//RTC????
{
	OLED_ShowString(2,1,"RTC_display");
//	  /* Get the RTC current Time */
//	  HAL_RTC_GetTime(&hrtc, &GetTime, RTC_FORMAT_BIN);
//      /* Get the RTC current Date */
//    HAL_RTC_GetDate(&hrtc, &GetData, RTC_FORMAT_BIN);
//	
//		/* Display date Format : yy/mm/dd */
//	
//        /* Display time Format : hh:mm:ss */
//		OLED_ShowNum(40,0,GetTime.Hours,2,16);				//hour
//		OLED_ShowString(57,0,":",16);	
//		OLED_ShowNum(66,0,GetTime.Minutes,2,16);			//min
//		OLED_ShowString(83,0,":",16);	
//		OLED_ShowNum(93,0,GetTime.Seconds,2,16);			//seconds
}