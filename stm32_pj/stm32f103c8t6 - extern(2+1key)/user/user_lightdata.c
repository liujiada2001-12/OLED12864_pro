#include "tsl2561.h"
#include "stdint.h"
#include "oled.h"
#include "rtc.h"
#include "user_oled.h"
#include "gpio.h"
#include "user_lightdata.h"
int data_num=-1;
float lightdata[99];
void User_Data_Show(void)
{
		data_num++;
		OLED_Clear();
		OLED_Refresh();
		OLED_Chinese16(1,2,2);//光
		OLED_Chinese16(1,3,3);//强
		OLED_ShowString(1,10,"cd/m2");
		lightdata[data_num]=100;
		lightdata[data_num]=(float)TSL2561_ReadData();
		char lightdata2[3][20]={"              ","              ","              "};
		if(data_num>=2)
		{
		sprintf(lightdata2[0],"%2d.  %.2f",data_num-2,lightdata[data_num-2]);
		sprintf(lightdata2[1],"%2d.  %.2f",data_num-1,lightdata[data_num-1]);
		sprintf(lightdata2[2],"->%2d.  %.2f",data_num,lightdata[data_num]);
			
		OLED_ShowString(2,1,lightdata2[0]);
		OLED_ShowString(3,1,lightdata2[1]);
		OLED_ShowString(4,1,lightdata2[2]);
		}
		else if(data_num==1)
		{
			sprintf(lightdata2[0],"%2d.  %.2f",data_num-1,lightdata[data_num-1]);
			sprintf(lightdata2[1],"->%2d.  %.2f",data_num,lightdata[data_num]);
			
			OLED_ShowString(2,1,lightdata2[0]);
			OLED_ShowString(3,1,lightdata2[1]);
		}
		else
		{
			sprintf(lightdata2[0],"->%2d.  %.2f",data_num,lightdata[data_num]);
			
			OLED_ShowString(2,1,lightdata2[0]);
		}
}

void User_DataChoice_Show(int data_no)
{
		if(data_no>=data_num) data_no=data_num;
		if(data_no<0) data_no=0;
		OLED_Clear();
		OLED_Refresh();
		OLED_Chinese16(1,2,2);//光
		OLED_Chinese16(1,3,3);//强
		OLED_ShowString(1,10,"cd/m2");
		char lightdata2[3][20]={"              ","              ","              "};
		if(data_num>=2)
		{
			if(data_no>=2)
			{
			sprintf(lightdata2[0],"%2d.  %.2f",data_no-2,lightdata[data_no-2]);
			sprintf(lightdata2[1],"%2d.  %.2f",data_no-1,lightdata[data_no-1]);
			sprintf(lightdata2[2],"->%2d.  %.2f",data_no,lightdata[data_no]);
			}
			else if(data_no==1)
			{
			sprintf(lightdata2[0],"%2d.  %.2f",data_no-1,lightdata[data_no-1]);
			sprintf(lightdata2[1],"->%2d.  %.2f",data_no,lightdata[data_no]);
			sprintf(lightdata2[2],"%2d.  %.2f",data_no+1,lightdata[data_no+1]);
			}
			else
			{
			sprintf(lightdata2[0],"->%2d.  %.2f",data_no,lightdata[data_no]);
			sprintf(lightdata2[1],"%2d.  %.2f",data_no+1,lightdata[data_no+1]);
			sprintf(lightdata2[2],"%2d.  %.2f",data_no+2,lightdata[data_no+2]);
			}
		OLED_ShowString(2,1,lightdata2[0]);
		OLED_ShowString(3,1,lightdata2[1]);
		OLED_ShowString(4,1,lightdata2[2]);
		}
		else if(data_num==1)
		{
			if(data_no==1)
			{
				sprintf(lightdata2[0],"%2d.  %.2f",data_no-1,lightdata[data_no-1]);
				sprintf(lightdata2[1],"->%2d.  %.2f",data_no,lightdata[data_no]);
			}
			else 
			{
				sprintf(lightdata2[0],"->%2d.  %.2f",data_no,lightdata[data_no]);
				sprintf(lightdata2[1],"%2d.  %.2f",data_no+1,lightdata[data_no+1]);
			}
			
			OLED_ShowString(2,1,lightdata2[0]);
			OLED_ShowString(3,1,lightdata2[1]);
		}
		else
		{
			sprintf(lightdata2[0],"->%2d.  %.2f",data_no,lightdata[data_no]);
			
			OLED_ShowString(2,1,lightdata2[0]);
		}
}

void User_Detect_Show(void)
{
		OLED_Clear();
		OLED_Refresh();
		OLED_Chinese16(2,2,10);//
		OLED_Chinese16(2,3,11);//
		OLED_Chinese16(2,4,21);//	
		OLED_ShowString(2,10,"...");
}

int User_DeleteData(int delete_no)
{
	//数据数组删除
	int i;
	for(i=delete_no;i<99;i++)
	{
		if(i<98)lightdata[i]=lightdata[i+1];
		if(i=98)lightdata[i]=0;
	}
		//当前数据数减一
		data_num--;
	return -1;//返回值给choice
}