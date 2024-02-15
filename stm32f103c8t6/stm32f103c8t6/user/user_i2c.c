#include "user_i2c.h"
#include "gpio.h"
/**
 * @brief һ���ӳ�
 * @param ��
 * @return ��
 * @author HZ12138
 * @date 2022-07-27 08:53:30
 */
void I2C_Delay(void)
{
	int z = 0xff;
	while (z--)
		;
}
/**
 * @brief дSDA
 * @param H_L:�ߵ͵�ƽ
 * @return ��
 * @author HZ12138
 * @date 2022-10-21 18:07:18
 */
void I2C_Write_SDA(GPIO_PinState H_L)
{
	HAL_GPIO_WritePin(I2C_SDA_GPIOx, I2C_SDA_Pin, H_L);
}
/**
 * @brief дSCL
 * @param H_L:�ߵ͵�ƽ
 * @return ��
 * @author HZ12138
 * @date 2022-10-21 18:07:40
 */
void I2C_Write_SCL(GPIO_PinState H_L)
{
	HAL_GPIO_WritePin(I2C_SCL_GPIOx, I2C_SCL_Pin, H_L);
}
/**
 * @brief ��ȡSDA
 * @param ��
 * @return SDA��״̬
 * @author HZ12138
 * @date 2022-10-21 18:07:56
 */
uint16_t I2C_Read_SDA(void)
{
	return HAL_GPIO_ReadPin(I2C_SDA_GPIOx, I2C_SDA_Pin);
}
/**
 * @brief ��ȡSCL
 * @param ��
 * @return SDA��״̬
 * @author HZ12138
 * @date 2022-10-21 18:07:56
 */
uint16_t I2C_Read_SCL(void)
{
	return HAL_GPIO_ReadPin(I2C_SCL_GPIOx, I2C_SCL_Pin);
}
//#ifdef I2C_Host
/**
 * @brief ����I2C��ʼ�ź�
 * @param ��
 * @return ��
 * @author HZ12138
 * @date 2022-07-27 08:54:48
 */
void I2C_Start(void)
{
	I2C_Write_SDA(GPIO_PIN_SET);   // ����SCL֮ǰ�趨
	I2C_Write_SCL(GPIO_PIN_SET);   // SCL->��
	I2C_Delay();				   // ��ʱ
	I2C_Write_SDA(GPIO_PIN_RESET); // SDA��1->0,������ʼ�ź�
	I2C_Delay();				   // ��ʱ
	I2C_Write_SCL(GPIO_PIN_RESET); // SCL->��
}
/**
 * @brief ����I2C�����ź�
 * @param ��
 * @return ��
 * @author HZ12138
 * @date 2022-07-27 08:57:03
 */
void I2C_End(void)
{
	I2C_Write_SDA(GPIO_PIN_RESET); // ��SCL֮ǰ����
	I2C_Write_SCL(GPIO_PIN_SET);   // SCL->��
	I2C_Delay();				   // ��ʱ
	I2C_Write_SDA(GPIO_PIN_SET);   // SDA��0->1,���������ź�
	I2C_Delay();				   // ��ʱ
}
/**
 * @brief ����Ӧ����
 * @param ack:0 Ӧ�� 1 ��Ӧ��
 * @return ��
 * @author HZ12138
 * @date 2022-07-27 09:03:38
 */
void I2C_Send_ACK(uint8_t ack)
{
	if (ack == 1)
		I2C_Write_SDA(GPIO_PIN_SET); // ����Ӧ���ƽ
	else
		I2C_Write_SDA(GPIO_PIN_RESET);
	I2C_Delay();
	I2C_Write_SCL(GPIO_PIN_SET);   // ����Ӧ���ź�
	I2C_Delay();				   // ��ʱ����4us
	I2C_Write_SCL(GPIO_PIN_RESET); // �����ڼ䱣��Ӧ���ź�
}
/**
 * @brief ����Ӧ����
 * @param ��
 * @return Ӧ���� 0 Ӧ�� 1 ��Ӧ��
 * @author HZ12138
 * @date 2022-07-27 09:04:28
 */
uint8_t I2C_Get_ACK(void)
{
	uint8_t ret;				 // �������շ���ֵ
	I2C_Write_SDA(GPIO_PIN_SET); // ��������,�����
	I2C_Delay();
	I2C_Write_SCL(GPIO_PIN_SET); // ����Ӧ����
	I2C_Delay();				 // ������ʱ4us
	ret = I2C_Read_SDA();		 // ����Ӧ���ź�
	I2C_Write_SCL(GPIO_PIN_RESET);
	return ret;
}
/**
 * @brief I2Cд1Byte
 * @param dat:1Byte����
 * @return Ӧ���� 0 Ӧ�� 1 ��Ӧ��
 * @author HZ12138
 * @date 2022-07-27 09:05:14
 */
uint8_t I2C_SendByte(uint8_t dat)
{
	uint8_t ack;
	for (int i = 0; i < 8; i++)
	{
		// ����ǰ���ں�
		if (dat & 0x80)
			I2C_Write_SDA(GPIO_PIN_SET);
		else
			I2C_Write_SDA(GPIO_PIN_RESET);
		I2C_Delay();
		I2C_Write_SCL(GPIO_PIN_SET);
		I2C_Delay(); // ��ʱ����4us
		I2C_Write_SCL(GPIO_PIN_RESET);
		dat <<= 1; // ��λ���λ�ƶ�
	}

	ack = I2C_Get_ACK();

	return ack;
}
/**
 * @brief I2C��ȡ1Byte����
 * @param ack:Ӧ�� 0 Ӧ�� 1 ��Ӧ��
 * @return ���ܵ�������
 * @author HZ12138
 * @date 2022-07-27 09:06:13
 */
uint8_t I2C_ReadByte(uint8_t ack)
{
	uint8_t ret = 0;
	I2C_Write_SDA(GPIO_PIN_SET);
	for (int i = 0; i < 8; i++)
	{
		ret <<= 1;
		I2C_Write_SCL(GPIO_PIN_SET);
		I2C_Delay();
		// ����ǰ���ں�
		if (I2C_Read_SDA())
		{
			ret++;
		}
		I2C_Write_SCL(GPIO_PIN_RESET);
		I2C_Delay();
	}

	I2C_Send_ACK(ack);

	return ret;
}
/**
 * @brief I2C����д
 * @param addr:������ַ
 * @param reg:�Ĵ�����ַ
 * @param len:����
 * @param buf:��������ַ
 * @return ״̬ 0�ɹ� ����ʧ��
 * @author HZ12138
 * @date 2022-08-08 15:47:11
 */
uint8_t I2C_Write_Len(uint8_t reg, uint8_t len, uint8_t *buf)
{
	uint8_t i;
	I2C_Start();
	I2C_SendByte(I2C_Address | 0); // ����������ַ+д����
	I2C_SendByte(reg);			   // д�Ĵ�����ַ
	for (i = 0; i < len; i++)
	{
		I2C_SendByte(buf[i]); // ��������
	}
	I2C_End();
	return 0;
}
/**
 * @brief I2C������
 * @param addr:������ַ
 * @param reg:�Ĵ�����ַ
 * @param len:����
 * @param buf:��������ַ
 * @return ״̬ 0�ɹ� ����ʧ��
 * @author HZ12138
 * @date 2022-08-08 15:47:11
 */
uint8_t I2C_Read_Len(uint8_t reg, uint8_t len, uint8_t *buf)
{
	I2C_Start();
	I2C_SendByte(I2C_Address | 0); // ����������ַ+д����
	I2C_SendByte(reg);			   // д�Ĵ�����ַ
	I2C_Start();
	I2C_SendByte(I2C_Address | 1); // ����������ַ+������
	while (len)
	{
		if (len == 1)
			*buf = I2C_ReadByte(1); // ������,����nACK
		else
			*buf = I2C_ReadByte(0); // ������,����ACK
		len--;
		buf++;
	}
	I2C_End(); // ����һ��ֹͣ����
	return 0;
}
/**
 * @brief I2Cдһ���ֽ�
 * @param reg:�Ĵ�����ַ
 * @param data:����
 * @return ״̬ 0�ɹ� ����ʧ��
 * @author HZ12138
 * @date 2022-08-08 15:47:11
 */
uint8_t I2C_Write_Reg(uint8_t reg, uint8_t data)
{
	I2C_Start();
	I2C_SendByte(I2C_Address | 0); // ����������ַ+д����
	I2C_SendByte(reg);			   // д�Ĵ�����ַ
	I2C_SendByte(data);			   // ��������
	I2C_End();
	return 0;
}
/**
 * @brief I2C��һ���ֽ�
 * @param reg:�Ĵ�����ַ
 * @return ��ȡ��������
 * @author HZ12138
 * @date 2022-08-08 15:47:11
 */
uint8_t I2C_Read_Reg(uint8_t reg)
{
	uint8_t res;
	I2C_Start();
	I2C_SendByte(I2C_Address | 0); // ����������ַ+д����
	I2C_SendByte(reg);			   // д�Ĵ�����ַ
	I2C_Start();
	I2C_SendByte(I2C_Address | 1); // ����������ַ+������
	res = I2C_ReadByte(1);		   // ��ȡ����,����nACK
	I2C_End();					   // ����һ��ֹͣ����
	return res;
}
//#endif
//
//
//
//
//
//
//
//
//
//
//
//#ifdef I2C_Slave
//uint8_t I2C_Slave_Ins = 0;
//uint8_t I2C_Slave_zj = 0;
//uint8_t I2C_Slave_num = 0;
//uint8_t I2C_Slave_Add = 0;
//uint8_t Reg_Add = 0;
//uint8_t I2C_Slave_RX_Buf = 0;
//uint8_t I2C_Slave_TX_Buf = 0;
//uint8_t I2C_Slave_SDA_IRQ_EN = 1;
///**
// * @brief ����SDAΪ�ж�ģʽ
// * @param ��
// * @return ��
// * @author HZ12138
// * @date 2022-12-29 19:56:29
// */
//void I2C_Slave_Set_SDA_IT(void)
//{
//	I2C_SDA_GPIOx->MODER &= ~(3 << (I2C_SDA_Pinx * 2));
//	I2C_SDA_GPIOx->MODER |= 0 << I2C_SDA_Pinx * 2;
//}
///**
// * @brief ����SDAΪ��©�������
// * @param ��
// * @return ��
// * @author HZ12138
// * @date 2022-12-29 19:56:54
// */
//void I2C_Slave_Set_SDA_Out(void)
//{
//	I2C_SDA_GPIOx->MODER &= ~(3 << (I2C_SDA_Pinx * 2));
//	I2C_SDA_GPIOx->MODER |= 1 << I2C_SDA_Pinx * 2;
//}
///**
// * @brief SCL�����ط�����
// * @param ��
// * @return ��
// * @author HZ12138
// * @date 2022-12-29 21:29:43
// */
//void I2C_Slave_IRQ_SCL_Rising(void)
//{ // SCL������
//	switch (I2C_Slave_Ins)
//	{
//	case 2: // ������ַ����

//		I2C_Slave_zj <<= 1;
//		I2C_Slave_zj |= I2C_Read_SDA();
//		I2C_Slave_num++;
//		if (I2C_Slave_num == 8) // ������
//		{
//			I2C_Slave_Add = I2C_Slave_zj;
//			I2C_Slave_zj = 0;
//		}
//		else if (I2C_Slave_num == 9) // Ӧ����
//		{
//			I2C_Slave_num = 0;
//			if (I2C_Slave_Add == (I2C_Address & 0xfe))
//				I2C_Slave_Ins = 3; // ���Ĵ�����ַ��ȡ̬
//			else if (I2C_Slave_Add == (I2C_Address | 0x01))
//			{
//				I2C_Write_SDA(GPIO_PIN_SET);
//				I2C_Slave_Set_SDA_Out();
//				I2C_Slave_Ins = 5;
//				I2C_Slave_zj = 0xaa;
//				I2C_Slave_num = 0;
//				I2C_Slave_SDA_IRQ_EN = 0;
//			}
//		}

//		break;
//	case 3: // �Ĵ�����ַ��ȡ

//		I2C_Slave_zj <<= 1;
//		I2C_Slave_zj |= I2C_Read_SDA();
//		I2C_Slave_num++;
//		if (I2C_Slave_num == 8) // ������
//		{
//			Reg_Add = I2C_Slave_zj;
//		}
//		else if (I2C_Slave_num == 9) // Ӧ����
//		{
//			I2C_Slave_Ins = 4; // ���ݶ�ȡ
//			I2C_Slave_zj = 0;
//			I2C_Slave_num = 0;
//		}
//		break;
//	case 4: // ���ݶ�ȡ(����д)
//		I2C_Slave_zj <<= 1;
//		I2C_Slave_zj |= I2C_Read_SDA();
//		I2C_Slave_num++;
//		if (I2C_Slave_num == 9) // Ӧ����
//		{
//			I2C_Slave_zj = 0;
//			I2C_Slave_num = 0;
//		}
//		break;

//	default:
//		break;
//	}
//}
///**
// * @brief SCL�½��ط�����
// * @param ��
// * @return ��
// * @author HZ12138
// * @date 2022-12-29 21:29:43
// */
//void I2C_Slave_IRQ_SCL_Falling(void)
//{ // SCL�½���
//	switch (I2C_Slave_Ins)
//	{
//	case 1: // ׼��̬
//		I2C_Slave_zj = 0;
//		I2C_Slave_num = 0;
//		I2C_Slave_Ins = 2; // ��������ַ����
//		break;
//	case 5: // ���ݷ���(������)

//		if (I2C_Slave_zj & 0x80)
//			I2C_Write_SDA(GPIO_PIN_SET);
//		else
//			I2C_Write_SDA(GPIO_PIN_RESET);
//		I2C_Slave_zj <<= 1;
//		I2C_Slave_num++;
//		if (I2C_Slave_num == 9) // Ӧ����
//		{
//			I2C_Slave_num = 0;
//			I2C_Write_SDA(GPIO_PIN_SET);
//			I2C_Slave_Set_SDA_IT();
//			I2C_Slave_SDA_IRQ_EN = 1;
//			I2C_Slave_Ins = 0;
//		}
//		break;
//	default:
//		break;
//	}
//}
///**
// * @brief ��SCL�жϷ������е���
// * @param ��
// * @return ��
// * @author HZ12138
// * @date 2022-12-29 21:28:32
// */
//void I2C_Slave_IRQ_SCL(void)
//{

//	if (I2C_Read_SCL() == GPIO_PIN_SET)
//	{ // ������
//		I2C_Slave_IRQ_SCL_Rising();
//	}
//	else
//	{ // �½���
//		I2C_Slave_IRQ_SCL_Falling();
//	}
//}
///**
// * @brief ��SDA�жϷ������е���
// * @param ��
// * @return ��
// * @author HZ12138
// * @date 2022-12-29 21:28:32
// */
//void I2C_Slave_IRQ_SDA(void)
//{
//	if (I2C_Slave_SDA_IRQ_EN == 1)
//	{
//		if (I2C_Read_SCL() == GPIO_PIN_SET)
//		{
//			if (I2C_Read_SDA() == GPIO_PIN_SET)
//			{					   // SDA������
//								   // ���̬
//				I2C_Slave_Ins = 0; // ������̬
//				I2C_Slave_Set_SDA_IT();
//			}
//			else
//			{ // SDA�½���
//				I2C_Slave_Set_SDA_IT();
//				if (I2C_Slave_Ins == 0) // ����̬
//					I2C_Slave_Ins = 1;	// ��׼��̬
//				else
//				{
//					I2C_Slave_Ins = 1;
//				}
//			}
//		}
//	}
//}
//#endif





















