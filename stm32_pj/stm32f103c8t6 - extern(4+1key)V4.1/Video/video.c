#include "video.h"
#include "oled.h"
#include "kunBMP.h"
#include "control.h"
int ye=0;
//extern const unsigned char *kunBMP;
void video_show()
{
	while(1)
	{
//	OLED_ShowString(1,2,"111");
//	OLED_ShowPicture(0,0,128,64,kunBMP1,1);
//	for(ye=0;ye<=106;ye++)
//	{
//	OLED_ShowPicture(0, 0,85, 64,(uint8_t*)kunBMP[ye],1);
//	if(ye>106)ye=0;
//	}
		Game_control();
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==0)
		{
			break;
		}
	}
		
}