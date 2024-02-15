#ifndef __TSL2561_H
#define __TSL2561_H
#include "gpio.h"

/*�豸��ַ*/
#define ADDR_SEL_GND 0x29//ADDR�Žӵ�
#define ADDR_SEL_FLOAT 0x39//ADDR�Ÿ���
#define ADDR_SEL_VDD 0x49//ADDR�Ž�Vdd

/*д�����ǽ�0x80|addr(�Ĵ�����ַ)*/
//������ƼĴ���
#define TSL2561_CMD 0x80//���ƼĴ�������оƬ�Ƿ���
#define TIMING 0x81//ʱ��Ĵ�����������ͻ���ʱ��
#define Llimit_Lbyte 0x82//�����޵��ֽ�
#define Llimit_Hbyte 0x83//�����޸��ֽ�
#define Hlimit_Lbyte 0x84//�����޵��ֽ�
#define Hlimit_Hbyte 0x85//�����޸��ֽ�
#define INT_CTRL 0x86
#define TSL2561_REG_ID 0x8A//����TSL2560��TSL2561
#define DATA0LOW 0x8C//ͨ��0���ֽ�
#define DATA0HIGH 0x8D//ͨ��0���ֽ�
#define DATA1LOW 0x8E//ͨ��1���ֽ�
#define DATA1HIGH 0x8F//ͨ��1���ֽ�

/*���ƼĴ�������*/
#define POWER_UP 0x03//�豸�ϵ�
#define POWER_DOWN 0x00//�豸�ϵ�

//Timing Register Value.Set integration time
//�����λ���û���ʱ��
#define TIMING_13MS 0x00 //����ʱ��13.7����
#define TIMING_101MS 0x01 //����ʱ��101����
#define TIMING_402MS 0x02 //����ʱ��402����
/*���汶�������ʱ����л�����*/
#define TIMING_GAIN_1X 0x00 //����1
#define TIMING_GAIN_16X 0x10 //����16��

void TSL2561_Init(uint8_t Time_model);
void TSL2561_Write(uint8_t command, uint8_t data);
uint8_t TSL2561_Read(uint8_t command);
uint32_t Read_Light(void);
void TSL2561_LED_on(void);
void TSL2561_LED_off(void);

void TSL2561_PowerOn(void);
void TSL2561_PowerDown(void);



//void TSL2561_Init(void);
//uint16_t TSL2561_ReadData(void);
//void TSL2561_on(void);
//void TSL2561_off(void);
//void TSL2561_LED_on(void);
#endif
