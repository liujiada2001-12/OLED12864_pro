#include "tsl2561_i2c.h"
#include "gpio.h"
#define TSL2561_SCL_Type     GPIOA
#define TSL2561_SDA_Type     GPIOA
 
#define TSL2561_SCL_GPIO    GPIO_PIN_6
#define TSL2561_SDA_GPIO    GPIO_PIN_7


void IIC_SDA_Mode_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = TSL2561_SDA_GPIO;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(TSL2561_SDA_Type, &GPIO_InitStruct);
}
/*****************************************
  SDA����ת��Ϊ ����ģʽ(����ģʽ������������) 
******************************************/
void IIC_SDA_Mode_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = TSL2561_SDA_GPIO;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(TSL2561_SDA_Type, &GPIO_InitStruct);
}




void i2c_delat_us(int x)
{
	int i,j;
	for(i=0;i<x;i++)
	{
		for(j=0;j<115;j++);
	}
}
void TSL2561_I2C_Init(void)
{
	TSL2561_W_SCL(1);
	TSL2561_W_SDA(1);
}

void TSL2561_I2C_Start(void)
{
	
	IIC_SDA_Mode_OUT();
	
	TSL2561_W_SCL(1);
	TSL2561_W_SDA(1);
	i2c_delat_us(5);
	TSL2561_W_SDA(0);
	i2c_delat_us(4);
	TSL2561_W_SCL(0);
}

void TSL2561_I2C_Stop(void)
{
	//����Ϊ���ģʽ
	IIC_SDA_Mode_OUT();
	
	TSL2561_W_SCL(0);
	TSL2561_W_SDA(0);
	i2c_delat_us(4);
	TSL2561_W_SCL(1);
	i2c_delat_us(4);
	TSL2561_W_SDA(1);
	i2c_delat_us(5);
}

void TSL2561_I2C_Write_ACK(uint8_t ack)
{
	//����Ϊ����ģʽ
	IIC_SDA_Mode_IN();
	
	TSL2561_W_SCL(0);
	if(ack)
	{
		TSL2561_W_SDA(1);
	}
	else
	{
		TSL2561_W_SDA(0);
	}
}

uint8_t TSL2561_I2C_Read_ACK(void)
{
	IIC_SDA_Mode_OUT();
	
	uint8_t ack=0;
	TSL2561_W_SDA(1);//���豸�ͷ�SDA���߿���Ȩ----��©����
	TSL2561_W_SCL(0);
	i2c_delat_us(5);
	TSL2561_W_SCL(1);
//����Ϊ����ģʽ
	IIC_SDA_Mode_IN();
	ack <<= 1;
	ack |= TSL2561_R_SDA;
	i2c_delat_us(4);

	TSL2561_W_SCL(0);

/*����SDA��Ϊ���ģʽ*/
	IIC_SDA_Mode_OUT();
	TSL2561_W_SDA(1);

return ack;

}

void TSL2561_I2C_Write_Byte(uint8_t byte)
{
	//����Ϊ���ģʽ
	IIC_SDA_Mode_OUT();
	
	uint8_t i=0;
	for(i = 0; i < 8; i++)
	{
		TSL2561_W_SCL(0);//��ʼ׼������
		if(byte & (0x80 >> i))
		{
			TSL2561_W_SDA(1);
		}
		else
		{
			TSL2561_W_SDA(0);
		}
		i2c_delat_us(5);//׼�������Ѿ����
		
		TSL2561_W_SCL(1);//��ʼ��������
		i2c_delat_us(4);//�����������----���豸��������ʱ��
	}

	TSL2561_W_SCL(0);

}

uint8_t TSL2561_I2C_Read_Byte(void)
{
	//����Ϊ����ģʽ
	IIC_SDA_Mode_IN();
	uint8_t i=0;
	uint8_t byte_data=0;
	TSL2561_W_SDA(1);//���豸�ͷ�SDA���߿���Ȩ

	for(i = 0; i < 8; i++)
	{
		TSL2561_W_SCL(0);
		i2c_delat_us(5);
		
		TSL2561_W_SCL(1);
		byte_data <<= 1;
		if(TSL2561_R_SDA)
		{
			byte_data |= 1;
		}
		i2c_delat_us(4);
	}
	TSL2561_W_SCL(0);
		
	return byte_data;
}

