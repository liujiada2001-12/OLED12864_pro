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
  SDA引脚转变为 输入模式(输入模式传输具体的数据) 
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
	//设置为输出模式
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
	//设置为输入模式
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
	TSL2561_W_SDA(1);//主设备释放SDA总线控制权----开漏功能
	TSL2561_W_SCL(0);
	i2c_delat_us(5);
	TSL2561_W_SCL(1);
//设置为输入模式
	IIC_SDA_Mode_IN();
	ack <<= 1;
	ack |= TSL2561_R_SDA;
	i2c_delat_us(4);

	TSL2561_W_SCL(0);

/*配置SDA线为输出模式*/
	IIC_SDA_Mode_OUT();
	TSL2561_W_SDA(1);

return ack;

}

void TSL2561_I2C_Write_Byte(uint8_t byte)
{
	//设置为输出模式
	IIC_SDA_Mode_OUT();
	
	uint8_t i=0;
	for(i = 0; i < 8; i++)
	{
		TSL2561_W_SCL(0);//开始准备数据
		if(byte & (0x80 >> i))
		{
			TSL2561_W_SDA(1);
		}
		else
		{
			TSL2561_W_SDA(0);
		}
		i2c_delat_us(5);//准备数据已经完成
		
		TSL2561_W_SCL(1);//开始发送数据
		i2c_delat_us(4);//发送数据完成----从设备保存数据时间
	}

	TSL2561_W_SCL(0);

}

uint8_t TSL2561_I2C_Read_Byte(void)
{
	//设置为输入模式
	IIC_SDA_Mode_IN();
	uint8_t i=0;
	uint8_t byte_data=0;
	TSL2561_W_SDA(1);//主设备释放SDA总线控制权

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

