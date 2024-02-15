#include "stm32f1xx_hal.h"
#include "user_i2c.h"
#include "tsl2561_i2c.h"
#include "tsl2561.h"
#include "gpio.h"
#include <math.h>
void TSL2561_Write(uint8_t command, uint8_t data)
{
	TSL2561_I2C_Init();
	TSL2561_I2C_Start();
	TSL2561_I2C_Write_Byte(ADDR_SEL_GND <<1);
	TSL2561_I2C_Read_ACK();
	TSL2561_I2C_Write_Byte(command);
	TSL2561_I2C_Read_ACK();
	TSL2561_I2C_Write_Byte(data);
	TSL2561_I2C_Read_ACK();
	TSL2561_I2C_Stop();
	HAL_Delay(10);
}


uint8_t TSL2561_Read(uint8_t command)
{
	uint8_t data;
	TSL2561_I2C_Init();

	TSL2561_I2C_Start();
	TSL2561_I2C_Write_Byte(ADDR_SEL_GND << 1);//器件地址，Addr脚接地0101001+写0
	TSL2561_I2C_Read_ACK();
	TSL2561_I2C_Write_Byte(command);
	TSL2561_I2C_Read_ACK();

	TSL2561_I2C_Start();
	TSL2561_I2C_Write_Byte((ADDR_SEL_GND << 1) | 0x01);//器件地址，Addr脚接地,0101001+读1
	TSL2561_I2C_Read_ACK();
	data = TSL2561_I2C_Read_Byte();
	TSL2561_I2C_Stop();
	HAL_Delay(10);
	return data;

}


/*
功能：开启TSL模块
*/
void TSL2561_PowerOn(void)
{
TSL2561_Write(TSL2561_CMD,POWER_UP);
}

/*
功能：关闭TSL模块
*/
void TSL2561_PowerDown(void)
{
TSL2561_Write(TSL2561_CMD,POWER_DOWN);
}

/*
功能：设置积分时间
参数：TIMING_13MS、TIMING_101MS、TIMING_402MS|TIMING_GAIN_1X,TIMING_GAIN_16X选择积分时间和增益，两个或运算
*/
void TSL2561_TimingSet(uint8_t TIME)
{
TSL2561_Write(TIMING,TIME);
}

void TSL2561_Init(uint8_t Time_model)
{
TSL2561_I2C_Init();
TSL2561_PowerDown(); //设置TSL2561未开启状态
TSL2561_TimingSet(Time_model);
}

uint32_t Read_Light(void)
{
uint8_t DataLow0,DataHigh0,DataLow1,DataHigh1,commad;
float Channel_0,Channel_1,temp;
float E = 0;//光强

DataLow0  = TSL2561_Read(DATA0LOW);
DataHigh0 = TSL2561_Read(DATA0HIGH);
Channel_0 = ((uint16_t)DataHigh0 << 8) + DataLow0;

DataLow1  = TSL2561_Read(DATA1LOW);
DataHigh1 = TSL2561_Read(DATA1HIGH);
Channel_1 = ((uint16_t)DataHigh1 << 8)+ DataLow1;

HAL_Delay(100);
// printf(“DataLow0 = %d\r\n”,DataLow0);
// printf(“DataHigh0 = %d\r\n”,DataHigh0);
// printf(“DataLow1 = %d\r\n”,DataLow1);
// printf(“DataHigh1 = %d\r\n”,DataHigh1);
// printf(“Channel_0 = %f\r\n”,Channel_0);
// printf(“Channel_1 = %f\r\n”,Channel_1);

if(0.0 < Channel_1/Channel_0 && Channel_1/Channel_0 <= 0.50)
	{
		E = (0.0304*Channel_0 - 0.062*Channel_0*pow(Channel_1/Channel_0, 1.4));
	}
if(0.50 < Channel_1/Channel_0 && Channel_1/Channel_0 <= 0.61)
{
	E = (0.0224*Channel_0 - 0.031*Channel_1);
}
if(0.61 < Channel_1/Channel_0 && Channel_1/Channel_0 <= 0.80)
{
	E = (0.0128*Channel_0 - 0.0153*Channel_1);
}
if(0.80 < Channel_1/Channel_0 && Channel_1/Channel_0 <= 1.30)
{
	E = (0.00146*Channel_0 - 0.00112*Channel_1);
}
if(Channel_1/Channel_0 > 1.30)
{
	E = 0;
}
HAL_Delay(100);	
	
return E;

}


void TSL2561_LED_on(void)
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,1);
}
void TSL2561_LED_off(void)
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,0);
}






















//#define TSL2561_ADDR 0x29  // TSL2561器件地址 
// 
//#define TSL2561_CMD 0x80  // 命令字节
//#define TSL2561_REG_TIMING 0x01  // TIMING寄存器地址
//#define TSL2561_REG_DATA_0 0x0C  // 数据寄存器0地址
//#define TSL2561_REG_DATA_1 0x0E  // 数据寄存器1地址
// 
//#define TSL2561_GAIN_1X 0x00  // 增益1x
//#define TSL2561_GAIN_16X 0x10  // 增益16x
// 
//#define TSL2561_INTEGRATION_TIME_13MS 0x00  // 13.7ms积分时间
//#define TSL2561_INTEGRATION_TIME_101MS 0x01  // 101ms积分时间
//#define TSL2561_INTEGRATION_TIME_402MS 0x02  // 402ms积分时间
// 
////I2C_HandleTypeDef hi2c1;
// 
//void TSL2561_Init(void)
//{
//    uint8_t buf[2];
// 
//    // 设置增益为1x，积分时间为13.7ms
//    buf[0] = TSL2561_CMD | TSL2561_REG_TIMING;
//    buf[1] = TSL2561_GAIN_1X | TSL2561_INTEGRATION_TIME_13MS;
//		I2C_Write_Len(TSL2561_ADDR,2,buf);
////    HAL_I2C_Master_Transmit(&hi2c1, TSL2561_ADDR, buf, 2, 1000);
//		TSL2561_LED_on();
//}
// 
//uint16_t TSL2561_ReadData(void)
//{
//    uint8_t buf[2];
//    uint16_t data;
// 
//    // 读取数据寄存器0和数据寄存器1的值
//    buf[0] = TSL2561_CMD | TSL2561_REG_DATA_0;
//		I2C_Write_Len(TSL2561_ADDR,1,buf);
////    HAL_I2C_Master_Transmit(&hi2c1, TSL2561_ADDR, buf, 1, 1000);
//	
//		I2C_Read_Len(TSL2561_ADDR, 2, buf);
////    HAL_I2C_Master_Receive(&hi2c1, TSL2561_ADDR, buf, 2, 1000);
// 
//    // 将读取到的数据转换为16位整数
//    data = buf[1] << 8 | buf[0];
// 
//    return data;
//}

