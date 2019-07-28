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
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO->Pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIO->GPIOx,&GPIO_InitStructure);
}

void AD7705_GPIO_InPut_init(AD7705_GPIO* GPIO)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(GPIO->RCC_APB2Periph_GPIOx,ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入
	GPIO_InitStructure.GPIO_Pin=GPIO->Pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIO->GPIOx,&GPIO_InitStructure);
}
void AD7705_GPIO_AF_init(AD7705_GPIO* GPIO)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(GPIO->RCC_APB2Periph_GPIOx,ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//推挽服用输出
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

void AD7705_SelfCalibration(SPI_TypeDef *SPIx,u8 ch)//启动自校准
{
	switch(ch)
	{
		case 1:
		{
			AD7705_ReadWriteByte(SPIx,REG_SETUP | WRITE | CH_1);//写设置寄存器
			AD7705_ReadWriteByte(SPIx,MD_CAL_SELF //自校准模式
																									|GAIN_1 //1倍增益
																									|UNIPOLAR //单极性
																									|BUF_EN //启用输入缓冲
																									|FSYNC_0);//启用滤波器同步
			break;
		}
		case 2:
		{
			AD7705_ReadWriteByte(SPIx,REG_SETUP | WRITE | CH_2);//写设置寄存器
			AD7705_ReadWriteByte(SPIx,MD_CAL_SELF //自校准模式
																									|GAIN_1 //1倍增益
																									|UNIPOLAR //单极性
																									|BUF_EN //启用输入缓冲
																									|FSYNC_0);//启用滤波器同步
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
			AD7705_ReadWriteByte(SPIx,REG_SETUP | WRITE | CH_1);//写设置寄存器
			AD7705_ReadWriteByte(SPIx,MD_CAL_ZERO //校准零刻度模式
																									|GAIN_1 //1倍增益
																									|UNIPOLAR //单极性
																									|BUF_EN //启用输入缓冲
																									|FSYNC_0);//启用滤波器同步
			break;
		}
		case 2:
		{
			AD7705_ReadWriteByte(SPIx,REG_SETUP | WRITE | CH_2);//写设置寄存器
			AD7705_ReadWriteByte(SPIx,MD_CAL_ZERO //校准零刻度模式
																									|GAIN_1 //1倍增益
																									|UNIPOLAR //单极性
																									|BUF_EN //启用输入缓冲
																									|FSYNC_0);//启用滤波器同步
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
			AD7705_ReadWriteByte(SPIx,REG_SETUP | WRITE | CH_1);//写设置寄存器
			AD7705_ReadWriteByte(SPIx,MD_CAL_FULL //校准满刻度模式
																									|GAIN_1 //1倍增益
																									|UNIPOLAR //单极性
																									|BUF_EN //启用输入缓冲
																									|FSYNC_0);//启用滤波器同步
			break;
		}
		case 2:
		{
			AD7705_ReadWriteByte(SPIx,REG_SETUP | WRITE | CH_2);//写设置寄存器
			AD7705_ReadWriteByte(SPIx,MD_CAL_FULL //校准满刻度模式
																									|GAIN_1 //1倍增益
																									|UNIPOLAR //单极性
																									|BUF_EN //启用输入缓冲
																									|FSYNC_0);//启用滤波器同步
			break;
		}
	}
}


void AD7705_Init(AD7705_InitTypeDef* AD7705)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(AD7705->RCC_APB1Periph_SPIx, ENABLE);
	
	//GPIO初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
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
	
	//SPI初始化
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//串行同步时钟的空闲状态为高电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//定义波特率预分频的值:波特率预分频值为256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
	SPI_Init(AD7705->SPIx, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
	SPI_Cmd(AD7705->SPIx,ENABLE);
	
	//AD7705复位
	GPIO_Set_High(AD7705->RESET);
	delay_ms(1);
	GPIO_Set_Low(AD7705->RESET);
	delay_ms(2);
	GPIO_Set_High(AD7705->RESET);
	delay_ms(1);
	
	//AD7705时钟同步
	GPIO_Set_Low(AD7705->CS);
	AD7705_ReadWriteByte(AD7705->SPIx,0xFF);
	AD7705_ReadWriteByte(AD7705->SPIx,0xFF);
	AD7705_ReadWriteByte(AD7705->SPIx,0xFF);
	AD7705_ReadWriteByte(AD7705->SPIx,0xFF);
	GPIO_Set_High(AD7705->CS);
	
	delay_ms(5);
	
	//AD7705寄存器配置
	GPIO_Set_Low(AD7705->CS);
	AD7705_ReadWriteByte(AD7705->SPIx,REG_CLOCK|WRITE|CH_1);//设置通信寄存器，对时钟寄存器进行操作
	AD7705_ReadWriteByte(AD7705->SPIx,CLKDIS_0|CLK_4_9152M|FS_50HZ);
	//delay_ms(5);
	AD7705_ReadWriteByte(AD7705->SPIx,REG_CLOCK|WRITE|CH_2);//设置通信寄存器，对时钟寄存器进行操作
	AD7705_ReadWriteByte(AD7705->SPIx,CLKDIS_0|CLK_4_9152M|FS_50HZ);
	GPIO_Set_High(AD7705->CS);
	delay_ms(5);
	
	//AD7705自校准
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

u16 AD7705_Read_ADC(AD7705_InitTypeDef* AD7705,u8 ch)//读取１６位ADC数值
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
