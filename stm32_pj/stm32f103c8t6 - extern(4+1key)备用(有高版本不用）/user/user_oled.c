#include "tsl2561.h"
#include "stdint.h"
#include "oled.h"
#include "rtc.h"
#include "user_oled.h"
#include "gpio.h"
#include "bmp.h"
#include "OLED_Font.h"






//周换算
char * CalWeek(int y, int m, int d){
	if(m==1||m==2) 
	{
		m+=12;
		y--;
	}
	int week =  (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7+1;
	switch(week)
    {   
        case 0 : return "Sunday"; break;
        case 1 : return "Monday"; break;
        case 2 : return "Tuesday"; break;
        case 3 : return "Wednesday"; break;
        case 4 : return "Thursday"; break;
        case 5 : return "Friday"; break;                                                             
        case 6 : return "Saturday"; break;
        default : return NULL; break;
    }   
}
//  日(0) 期(1) 光(2) 强(3) 你(4) 好(5) 欢(6) 迎(7) 使(8) 用(9)

void User_Time_Show(void)
{
		OLED_Clear();

		RTC_DateTypeDef GetData;  //获取日期结构体
		RTC_TimeTypeDef GetTime;   //获取时间结构体
		HAL_RTC_GetTime(&hrtc, &GetTime, RTC_FORMAT_BIN);//获取时间
      /* Get the RTC current Date */
    HAL_RTC_GetDate(&hrtc, &GetData, RTC_FORMAT_BIN);//获取日期

    /* Display date Format : yy/mm/dd */
		char time[30];
    sprintf(time,"%02d/%02d/%02d",(2000 + GetData.Year), GetData.Month, GetData.Date);
    /* Display time Format : hh:mm:ss */
		char data[]="00:00:00";
    sprintf(data,"%02d:%02d:%02d",GetTime.Hours, GetTime.Minutes, GetTime.Seconds);

    OLED_ShowString(2,4,time);
		OLED_ShowString(3,6,CalWeek(GetData.Year, GetData.Month, GetData.Date));
		OLED_ShowString(4,5,data);
		OLED_Chinese16(1,4,0);//日
		OLED_Chinese16(1,5,1);//期
}

void User_Init_Show(void)
{
		OLED_Clear();

		OLED_ShowPicture(0,0,64,64,myBMP1,1);
		OLED_Refresh();
		OLED_Chinese16(2,6,6);//欢
		OLED_Chinese16(2,7,7);//迎
		OLED_Chinese16(3,6,8);//使
		OLED_Chinese16(3,7,9);//用
}

void User_huizhang_Show(void)
{
		OLED_Clear();

		OLED_ShowPicture(0,0,64,64,xiaohui,1);
		OLED_ShowPicture(64,0,64,64,yuanhui,0);
		OLED_Refresh();
}
void User_PIC_Show(void)
{
		OLED_Clear();

		OLED_ShowPicture(0,0,64,64,myBMP,1);
		OLED_Refresh();
	
		RTC_DateTypeDef GetData;  //获取日期结构体
		RTC_TimeTypeDef GetTime;   //获取时间结构体
		HAL_RTC_GetTime(&hrtc, &GetTime, RTC_FORMAT_BIN);//获取时间
      /* Get the RTC current Date */
    HAL_RTC_GetDate(&hrtc, &GetData, RTC_FORMAT_BIN);//获取日期

    /* Display date Format : yy/mm/dd */
		char time[]="2020";
		sprintf(time,"%02d",(2000 + GetData.Year));
		OLED_ShowString(1,11,time);
		char time1[]="07/01";
    sprintf(time1,"%02d/%02d", GetData.Month, GetData.Date);
		OLED_ShowString(2,10,time1);
    /* Display time Format : hh:mm:ss */
		char data[]="00:00:00";
    sprintf(data,"%02d:%02d:%02d",GetTime.Hours, GetTime.Minutes, GetTime.Seconds);
		OLED_ShowString(3,9,CalWeek(GetData.Year, GetData.Month, GetData.Date));
		OLED_ShowString(4,9,data);
}
void User_Data_Show(void)
{
		OLED_Clear();
		OLED_Refresh();
		OLED_Chinese16(2,1,2);//光
		OLED_Chinese16(2,2,3);//强
		
		float lightdata=100;
		lightdata=(float)TSL2561_ReadData();
		char lightdata1[]="100.00aaa";
		sprintf(lightdata1,"%.2f",lightdata);
		OLED_ShowString(2,6,lightdata1);
	
}
// 日(0) 期(1) 光(2) 强(3) 你(4) 好(5) 欢(6) 迎(7) 使(8) 用(9) 测(10) 量(11)
void User_Time(void)
{
		OLED_Chinese16(1,1,10);//
		OLED_Chinese16(1,2,11);//
	
		OLED_Chinese16(2,2,0);//
		OLED_Chinese16(2,3,1);//
	
		OLED_Chinese(3,1,44);//
		OLED_Chinese(3,2,47);//
		OLED_Chinese(3,3,39);//
	
		OLED_Chinese16(4,1,19);//
		OLED_Chinese16(4,2,20);//
}
void User_Data(void)
{
		OLED_Chinese16(1,2,10);//
		OLED_Chinese16(1,3,11);//
	
		OLED_Chinese16(2,1,0);//
		OLED_Chinese16(2,2,1);//
	
		OLED_Chinese(3,1,44);//
		OLED_Chinese(3,2,47);//
		OLED_Chinese(3,3,39);//
	
		OLED_Chinese16(4,1,19);//
		OLED_Chinese16(4,2,20);//
}

void User_LOG(void)
{
		OLED_Chinese16(1,1,10);//
		OLED_Chinese16(1,2,11);//
	
		OLED_Chinese16(2,1,0);//
		OLED_Chinese16(2,2,1);//
	
		OLED_Chinese(3,4,44);//
		OLED_Chinese(3,5,47);//
		OLED_Chinese(3,6,39);//
	
		OLED_Chinese16(4,1,19);//
		OLED_Chinese16(4,2,20);//
}
void User_Play(void)
{
		OLED_Chinese16(1,1,10);//
		OLED_Chinese16(1,2,11);//
	
		OLED_Chinese16(2,1,0);//光强
		OLED_Chinese16(2,2,1);//
	
		OLED_Chinese(3,1,44);//
		OLED_Chinese(3,2,47);//
		OLED_Chinese(3,3,39);//
	
		OLED_Chinese16(4,2,19);//
		OLED_Chinese16(4,3,20);//
}

void User_Home(void)
{
		OLED_Chinese16(2,3,4);//你好
		OLED_Chinese16(2,6,5);//

}