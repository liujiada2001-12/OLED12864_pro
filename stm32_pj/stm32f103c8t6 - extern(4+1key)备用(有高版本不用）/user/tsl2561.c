#include "stm32f1xx_hal.h"
#include "user_i2c.h"
#define TSL2561_ADDR 0x29  // TSL2561������ַ 
 
#define TSL2561_CMD 0x80  // �����ֽ�
#define TSL2561_REG_TIMING 0x01  // TIMING�Ĵ�����ַ
#define TSL2561_REG_DATA_0 0x0C  // ���ݼĴ���0��ַ
#define TSL2561_REG_DATA_1 0x0E  // ���ݼĴ���1��ַ
 
#define TSL2561_GAIN_1X 0x00  // ����1x
#define TSL2561_GAIN_16X 0x10  // ����16x
 
#define TSL2561_INTEGRATION_TIME_13MS 0x00  // 13.7ms����ʱ��
#define TSL2561_INTEGRATION_TIME_101MS 0x01  // 101ms����ʱ��
#define TSL2561_INTEGRATION_TIME_402MS 0x02  // 402ms����ʱ��
 
//I2C_HandleTypeDef hi2c1;
 
void TSL2561_Init(void)
{
    uint8_t buf[2];
 
    // ��������Ϊ1x������ʱ��Ϊ13.7ms
    buf[0] = TSL2561_CMD | TSL2561_REG_TIMING;
    buf[1] = TSL2561_GAIN_1X | TSL2561_INTEGRATION_TIME_13MS;
		I2C_Write_Len(TSL2561_ADDR,2,buf);
//    HAL_I2C_Master_Transmit(&hi2c1, TSL2561_ADDR, buf, 2, 1000);
}
 
uint16_t TSL2561_ReadData(void)
{
    uint8_t buf[2];
    uint16_t data;
 
    // ��ȡ���ݼĴ���0�����ݼĴ���1��ֵ
    buf[0] = TSL2561_CMD | TSL2561_REG_DATA_0;
		I2C_Write_Len(TSL2561_ADDR,1,buf);
//    HAL_I2C_Master_Transmit(&hi2c1, TSL2561_ADDR, buf, 1, 1000);
	
		I2C_Read_Len(TSL2561_ADDR, 2, buf);
//    HAL_I2C_Master_Receive(&hi2c1, TSL2561_ADDR, buf, 2, 1000);
 
    // ����ȡ��������ת��Ϊ16λ����
    data = buf[1] << 8 | buf[0];
 
    return data;
}