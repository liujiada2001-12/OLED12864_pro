#include "stm32f1xx_hal.h"
#include "user_i2c.h"
#define TSL2561_ADDR 0x29  // TSL2561器件地址 
 
#define TSL2561_CMD 0x80  // 命令字节
#define TSL2561_REG_TIMING 0x01  // TIMING寄存器地址
#define TSL2561_REG_DATA_0 0x0C  // 数据寄存器0地址
#define TSL2561_REG_DATA_1 0x0E  // 数据寄存器1地址
 
#define TSL2561_GAIN_1X 0x00  // 增益1x
#define TSL2561_GAIN_16X 0x10  // 增益16x
 
#define TSL2561_INTEGRATION_TIME_13MS 0x00  // 13.7ms积分时间
#define TSL2561_INTEGRATION_TIME_101MS 0x01  // 101ms积分时间
#define TSL2561_INTEGRATION_TIME_402MS 0x02  // 402ms积分时间
 
//I2C_HandleTypeDef hi2c1;
 
void TSL2561_Init(void)
{
    uint8_t buf[2];
 
    // 设置增益为1x，积分时间为13.7ms
    buf[0] = TSL2561_CMD | TSL2561_REG_TIMING;
    buf[1] = TSL2561_GAIN_1X | TSL2561_INTEGRATION_TIME_13MS;
		I2C_Write_Len(TSL2561_ADDR,2,buf);
//    HAL_I2C_Master_Transmit(&hi2c1, TSL2561_ADDR, buf, 2, 1000);
}
 
uint16_t TSL2561_ReadData(void)
{
    uint8_t buf[2];
    uint16_t data;
 
    // 读取数据寄存器0和数据寄存器1的值
    buf[0] = TSL2561_CMD | TSL2561_REG_DATA_0;
		I2C_Write_Len(TSL2561_ADDR,1,buf);
//    HAL_I2C_Master_Transmit(&hi2c1, TSL2561_ADDR, buf, 1, 1000);
	
		I2C_Read_Len(TSL2561_ADDR, 2, buf);
//    HAL_I2C_Master_Receive(&hi2c1, TSL2561_ADDR, buf, 2, 1000);
 
    // 将读取到的数据转换为16位整数
    data = buf[1] << 8 | buf[0];
 
    return data;
}