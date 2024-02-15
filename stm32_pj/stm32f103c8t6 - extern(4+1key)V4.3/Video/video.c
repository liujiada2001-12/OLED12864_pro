#include "video.h"
#include "oled.h"
//#include "kunBMP.h"
#include "control.h"
#include "dinogame.h"
extern int play_flag;
int ye=0;
//extern const unsigned char *kunBMP;
void video_show()
{

//	OLED_ShowString(1,2,"111");
//	OLED_ShowPicture(0,0,128,64,kunBMP1,1);
//	for(ye=0;ye<=106;ye++)
//	{
//	OLED_ShowPicture(0, 0,85, 64,(uint8_t*)kunBMP[ye],1);
//	if(ye>106)ye=0;
//	}
	if(play_flag==1){
//		OLED_DrawBMPFast(kunBMP[ye]);
		ye++;
}
}