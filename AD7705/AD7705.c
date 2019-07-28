#include "AD7705.h"

void GPIO_Set_High(AD7705_GPIO* GPIO)
{
	GPIO_SetBits(GPIO->GPIOx,GPIO->Pin);
	GPIO->status=Bit_SET;
}
void GPIO_Set_Low(AD7705_GPIO* GPIO)
{
	GPIO_ResetBits(GPIO->GPIOx,GPIO->Pin);
	GPIO->status=Bit_RESET;
}

u8 GPIO_Read(AD7705_GPIO* GPIO)
{
	GPIO->status=GPIO_ReadInputDataBit(GPIO->GPIOx,GPIO->Pin);
	return GPIO->status;
	/*Bit_SET / Bit_RESET */
}


void AD7705_GPIO_OutPut_init(AD7705_GPIO* GPIO)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(GPIO->RCC_APB2Periph_GPIOx,ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//�������
	GPIO_InitStructure.GPIO_Pin=GPIO->Pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIO->GPIOx,&GPIO_InitStructure);
}

void AD7705_GPIO_InPut_init(AD7705_GPIO* GPIO)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(GPIO->RCC_APB2Periph_GPIOx,ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//��������
	GPIO_InitStructure.GPIO_Pin=GPIO->Pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIO->GPIOx,&GPIO_InitStructure);
}
void AD7705_GPIO_AF_init(AD7705_GPIO* GPIO)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(GPIO->RCC_APB2Periph_GPIOx,ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//����������
	GPIO_InitStructure.GPIO_Pin=GPIO->Pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIO->GPIOx,&GPIO_InitStructure);
}

u8 AD7705_ReadWriteByte(SPI_TypeDef *SPIx,u8 byte)
{
	while(SPI_I2S_GetFlagStatus(SPIx,SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(SPIx,byte);
	while(SPI_I2S_GetFlagStatus(SPIx,SPI_I2S_FLAG_RXNE)==RESET);
	return SPI_I2S_ReceiveData(SPIx);
}

void AD7705_SelfCalibration(SPI_TypeDef *SPIx,u8 ch)//������У׼
{
	switch(ch)
	{
		case 1:
		{
			AD7705_ReadWriteByte(SPIx,REG_SETUP | WRITE | CH_1);//д���üĴ���
			AD7705_ReadWriteByte(SPIx,MD_CAL_SELF //��У׼ģʽ
																									|GAIN_1 //1������
																									|UNIPOLAR //������
																									|BUF_EN //�������뻺��
																									|FSYNC_0);//�����˲���ͬ��
			break;
		}
		case 2:
		{
			AD7705_ReadWriteByte(SPIx,REG_SETUP | WRITE | CH_2);//д���üĴ���
			AD7705_ReadWriteByte(SPIx,MD_CAL_SELF //��У׼ģʽ
																									|GAIN_1 //1������
																									|UNIPOLAR //������
																									|BUF_EN //�������뻺��
																									|FSYNC_0);//�����˲���ͬ��
			break;
		}
	}
	//delay_ms(200);
}

void AD7705_SysCalibration(SPI_TypeDef* SPIx,u8 ch)
{
	switch(ch)
	{
		case 1:
		{
			AD7705_ReadWriteByte(SPIx,REG_SETUP | WRITE | CH_1);//д���üĴ���
			AD7705_ReadWriteByte(SPIx,MD_CAL_ZERO //У׼��̶�ģʽ
																									|GAIN_1 //1������
																									|UNIPOLAR //������
																									|BUF_EN //�������뻺��
																									|FSYNC_0);//�����˲���ͬ��
			break;
		}
		case 2:
		{
			AD7705_ReadWriteByte(SPIx,REG_SETUP | WRITE | CH_2);//д���üĴ���
			AD7705_ReadWriteByte(SPIx,MD_CAL_ZERO //У׼��̶�ģʽ
																									|GAIN_1 //1������
																									|UNIPOLAR //������
																									|BUF_EN //�������뻺��
																									|FSYNC_0);//�����˲���ͬ��
			break;
		}
	}
}

void AD7705_FullCalibration(SPI_TypeDef* SPIx,u8 ch)
{
	switch(ch)
	{
		case 1:
		{
			AD7705_ReadWriteByte(SPIx,REG_SETUP | WRITE | CH_1);//д���üĴ���
			AD7705_ReadWriteByte(SPIx,MD_CAL_FULL //У׼���̶�ģʽ
																									|GAIN_1 //1������
																									|UNIPOLAR //������
																									|BUF_EN //�������뻺��
																									|FSYNC_0);//�����˲���ͬ��
			break;
		}
		case 2:
		{
			AD7705_ReadWriteByte(SPIx,REG_SETUP | WRITE | CH_2);//д���üĴ���
			AD7705_ReadWriteByte(SPIx,MD_CAL_FULL //У׼���̶�ģʽ
																									|GAIN_1 //1������
																									|UNIPOLAR //������
																									|BUF_EN //�������뻺��
																									|FSYNC_0);//�����˲���ͬ��
			break;
		}
	}
}


void AD7705_Init(AD7705_InitTypeDef* AD7705)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(AD7705->RCC_APB1Periph_SPIx, ENABLE);
	
	//GPIO��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	AD7705_GPIO_OutPut_init(AD7705->CS);
	AD7705_GPIO_OutPut_init(AD7705->RESET);
	
	AD7705_GPIO_InPut_init(AD7705->DRDY);
	
	AD7705_GPIO_AF_init(AD7705->SCK);
	AD7705_GPIO_AF_init(AD7705->DIN);
	AD7705_GPIO_AF_init(AD7705->DOUT);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
	GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);
	GPIO_SetBits(GPIOC,GPIO_Pin_4);
	
	//SPI��ʼ��
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(AD7705->SPIx, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
	SPI_Cmd(AD7705->SPIx,ENABLE);
	
	//AD7705��λ
	GPIO_Set_High(AD7705->RESET);
	delay_ms(1);
	GPIO_Set_Low(AD7705->RESET);
	delay_ms(2);
	GPIO_Set_High(AD7705->RESET);
	delay_ms(1);
	
	//AD7705ʱ��ͬ��
	GPIO_Set_Low(AD7705->CS);
	AD7705_ReadWriteByte(AD7705->SPIx,0xFF);
	AD7705_ReadWriteByte(AD7705->SPIx,0xFF);
	AD7705_ReadWriteByte(AD7705->SPIx,0xFF);
	AD7705_ReadWriteByte(AD7705->SPIx,0xFF);
	GPIO_Set_High(AD7705->CS);
	
	delay_ms(5);
	
	//AD7705�Ĵ�������
	GPIO_Set_Low(AD7705->CS);
	AD7705_ReadWriteByte(AD7705->SPIx,REG_CLOCK|WRITE|CH_1);//����ͨ�żĴ�������ʱ�ӼĴ������в���
	AD7705_ReadWriteByte(AD7705->SPIx,CLKDIS_0|CLK_4_9152M|FS_50HZ);
	//delay_ms(5);
	AD7705_ReadWriteByte(AD7705->SPIx,REG_CLOCK|WRITE|CH_2);//����ͨ�żĴ�������ʱ�ӼĴ������в���
	AD7705_ReadWriteByte(AD7705->SPIx,CLKDIS_0|CLK_4_9152M|FS_50HZ);
	GPIO_Set_High(AD7705->CS);
	delay_ms(5);
	
	//AD7705��У׼
	GPIO_Set_Low(AD7705->CS);
	
	//AD7705_SysCalibration(AD7705->SPIx,1);
	//while(GPIO_Read(AD7705->DRDY)!=Bit_RESET);
	//AD7705_SysCalibration(AD7705->SPIx,2);
	//while(GPIO_Read(AD7705->DRDY)!=Bit_RESET);
	
	AD7705_SelfCalibration(AD7705->SPIx,1);
	while(GPIO_Read(AD7705->DRDY)!=Bit_RESET);
	AD7705_Read_ADC(AD7705,1);
	
	AD7705_SelfCalibration(AD7705->SPIx,2);
	while(GPIO_Read(AD7705->DRDY)!=Bit_RESET);
	AD7705_Read_ADC(AD7705,2);
	GPIO_Set_High(AD7705->CS);
}

void AD7705_EXTI_Init(AD7705_InitTypeDef* AD7705)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_EXTILineConfig(AD7705->GPIO_PortSuorceGPIOx,AD7705->GPIO_PinSuorcePinx);
	EXTI_InitStructure.EXTI_Line=AD7705->EXTI_Linex;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=AD7705->IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

u16 AD7705_Read_ADC(AD7705_InitTypeDef* AD7705,u8 ch)//��ȡ����λADC��ֵ
{
	u16 data=0;
	GPIO_Set_Low(AD7705->CS);

	while(GPIO_Read(AD7705->DRDY)==Bit_SET);
	switch(ch)
	{
		case 1:
		{
			AD7705_ReadWriteByte(AD7705->SPIx,0x38);
			break;
		}
		case 2:
		{
			AD7705_ReadWriteByte(AD7705->SPIx,0x39);
			break;
		}
	}
	
	data=AD7705_ReadWriteByte(AD7705->SPIx,0xFF);
	data<<=8;
	data|=AD7705_ReadWriteByte(AD7705->SPIx,0xFF);
	GPIO_Set_High(AD7705->CS);
	return data;
}

void EXTI1_IRQHandler(void)
{
	LED1=!LED1;
	EXTI_ClearITPendingBit(EXTI_Line1);
}
