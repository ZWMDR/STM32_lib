#ifndef __AD_7705_H
#define __AD_7705_H
#include "sys.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "delay.h"
#include "led.h"

enum
{
	/* Ƭ�ڼĴ���  RS2 RS1 RS0  */
	REG_COMM	= 0x00,	/* ͨ�żĴ��� */
	REG_SETUP	= 0x10,	/* ���üĴ���*/
	REG_CLOCK	= 0x20,	/* ʱ�ӼĴ��� */
	REG_DATA	= 0x30,	/* ���ݼĴ���*/
	REG_ZERO_CH1	= 0x60,	/* CH1 ƫ�ƼĴ��� */
	REG_FULL_CH1	= 0x70,	/* CH1 �����̼Ĵ���*/
	REG_ZERO_CH2	= 0x61,	/* CH2 ƫ�ƼĴ���*/
	REG_FULL_CH2	= 0x71,	/* CH2 �����̼Ĵ���*/

	/* ��/д���� */
	WRITE 		= 0x00,	/* ??? */
	READ 		= 0x08,	/* ??? */

	/* ͨ�� */
	CH_1		= 0,	/* AIN1+  AIN1- */
	CH_2		= 1,	/* AIN2+  AIN2- */
	CH_3		= 2,	/* AIN1-  AIN1- */
	CH_4		= 3		/* AIN1-  AIN2- */
};

/* ���üĴ���bit����*/
enum
{
	MD_NORMAL		= (0 << 6),	/* ����ģʽ */
	MD_CAL_SELF		= (1 << 6),	/* ��У׼ģʽ */
	MD_CAL_ZERO		= (2 << 6),	/* У׼��̶�ģʽ */
	MD_CAL_FULL		= (3 << 6),	/* У׼���̶�ģʽ */

	/* ���� */
	GAIN_1			= (0 << 3),	
	GAIN_2			= (1 << 3),	
	GAIN_4			= (2 << 3),	
	GAIN_8			= (3 << 3),
	GAIN_16			= (4 << 3),
	GAIN_32			= (5 << 3),
	GAIN_64			= (6 << 3),
	GAIN_128		= (7 << 3),	

	/*������/˫�������� */
	BIPOLAR			= (0 << 2),	/* ˫�������� */
	UNIPOLAR		= (1 << 2),	/* ����������*/

	/* ��������� */
	BUF_NO			= (0 << 1),	/*���������뻺��*/
	BUF_EN			= (1 << 1),	/* �������뻺�� */

/* �˲���ͬ�� */
	FSYNC_0			= 0, /* ���� */
	FSYNC_1			= 1		/* ������ */
};

/* ʱ�ӼĴ���bit���� */
enum
{
	CLKDIS_0	= 0x00,		/* ʱ�����ʹ�ܣ��ⲿ���� */
	CLKDIS_1	= 0x10,		/* ʱ�������ֹ */

	CLK_4_9152M = 0x08,
	CLK_2_4576M = 0x00,
	CLK_1M 		= 0x04,
	CLK_2M 		= 0x0C,

	FS_20HZ   = 0x00,
	FS_25HZ   =0x01,
	FS_50HZ		= 0x04,
	FS_60HZ		= 0x05,
	FS_100HZ = 0x02,
	FS_200HZ = 0x03,
	FS_250HZ	= 0x06,
	FS_500HZ	= 0x07,

	ZERO_0		= 0x00,
	ZERO_1		= 0x80
};



typedef struct AD7705_GPIO_TypeDef
{
	GPIO_TypeDef* GPIOx;
	uint16_t Pin;
	uint32_t RCC_APB2Periph_GPIOx;
	u8 status;
}AD7705_GPIO;

typedef struct AD7705_InitTypeDef
{
	//GPIO�˿�
	AD7705_GPIO* SCK;
	AD7705_GPIO* DIN;
	AD7705_GPIO* DOUT;
	AD7705_GPIO* CS;
	AD7705_GPIO* DRDY;
	AD7705_GPIO* RESET;
	
	//SPI����
	SPI_TypeDef* SPIx;
	uint32_t RCC_APB1Periph_SPIx;
	
	//�ⲿ�ж�
	uint32_t EXTI_Linex;
	uint8_t IRQChannel;
	uint8_t GPIO_PortSuorceGPIOx;
	uint8_t GPIO_PinSuorcePinx;
	
}AD7705_InitTypeDef;

#define _20Hz   0x10
#define _25Hz   0x20
#define _50Hz   0x30
#define _60Hz   0x40
#define _100Hz 0x50
#define _200Hz 0x60
#define _250Hz 0x70
#define _500Hz 0x80


//�˿ڶ�д
void GPIO_Set_High(AD7705_GPIO* GPIO);
void GPIO_Set_Low(AD7705_GPIO* GPIO);
u8 GPIO_Read(AD7705_GPIO* GPIO);

//ͨ��
u8 AD7705_ReadWriteByte(SPI_TypeDef *SPIx,u8 byte);
u16 AD7705_Read_ADC(AD7705_InitTypeDef* AD7705,u8 ch);

//У׼
void AD7705_SelfCalibration(SPI_TypeDef *SPIx,u8 ch);//��У׼
void AD7705_SysCalibration(SPI_TypeDef* SPIx,u8 ch);//��̶�У׼���ֶ��̽�AIN+ AIN-���룩
void AD7705_FullCalibration(SPI_TypeDef* SPIx,u8 ch);//���̶�У׼���ֶ���AIN+ AIN-��������ѹ��

//��ʼ������
void AD7705_Init(AD7705_InitTypeDef* AD7705,u8 refresh_speed);

//�ⲿ�ж����ú���
void AD7705_EXTI_Init(AD7705_InitTypeDef* AD7705);


#endif
