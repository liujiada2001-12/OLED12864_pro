#include "control.h"
#include "dinooled.h"
#include "oled.h"
#include "dinogame.h"
#include "stdlib.h"
#include "user_key.h"
#include "gpio.h"
#include "menu.h"
int game_flag=0;
extern uint8_t button;
extern uint8_t last_button;
int get_key()
{
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3) ==  0)
		{
//			last_button=button;
//			return 2;
			for(int i=0;i<200;i++);
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3) ==  0) {return 2;}
		}

		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1) ==  0)
		{
//			last_button=button;
//			return 1;
			for(int i=0;i<200;i++);
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1) ==  0) {return 1;}
		}
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2) ==  0)
		{
//			last_button=button;
//			return 3;
			for(int i=0;i<200;i++);
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2) ==  0) {return 3;}
		}
	return 0;
}


void Game_control()
{
	unsigned char key_num = 0;
	unsigned char cactus_category = 0;
	unsigned char cactus_length = 8;
	unsigned int score = 0;
	unsigned int highest_score = 0;
	int height = 0;
	int cactus_pos = 128;
	unsigned char cur_speed = 30;
	char failed = 0;
	char reset = 0;
//	if(game_flag==1)
//	{
//		while(1)
//		{
//			if(get_key() == 3)		
//			{
//				game_flag=0;
////				OLED_Clear1();
////				Play1();
//				break;
//			}

				if (failed == 1)
			{
				OLED_DrawRestart();

				key_num = get_key();
				if (key_num == 2)//2ÖØ¿ª
				{
					if(score > highest_score) highest_score = score;
					score = 0;
					failed = 0;
					height = 0;
					reset = 1;
					OLED_DrawDinoJump(reset);
					OLED_DrawCactusRandom(cactus_category, reset);
					OLED_Clear1();
				}
				
			}


			score ++;
			if (height <= 0) key_num = get_key();

			OLED_DrawGround();
			OLED_DrawCloud();

			if (height>0 || key_num == 1) height = OLED_DrawDinoJump(reset);//1Ìø
			else OLED_DrawDino();

			cactus_pos = OLED_DrawCactusRandom(cactus_category, reset);
			if(cactus_category == 0) cactus_length = 8;
			else if(cactus_category == 1) cactus_length = 16;
			else cactus_length = 24;

			if (cactus_pos + cactus_length < 0)
			{
				cactus_category = rand()%4;
				OLED_DrawCactusRandom(cactus_category, 1);
			}

			if ((height < 16) && ( (cactus_pos>=16 && cactus_pos <=32) || (cactus_pos + cactus_length>=16 && cactus_pos + cactus_length <=32)))
			{
				failed = 1;
			}

			OLED_ShowString1(35, 0, "H:", 12);
			OLED_ShowNum1(58, 0, highest_score, 5, 12);
			OLED_ShowNum1(98, 0, score, 5, 12);


			reset = 0;

			cur_speed = score/20;
			if (cur_speed > 29) cur_speed = 29;
			HAL_Delay(30 - cur_speed);
	//		HAL_Delay(500);
			key_num = 0;
//		}
//	}
}