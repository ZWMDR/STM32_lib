#include "SPI_DMA.h"

void SPI1_DMA1_Init(u16 arr,u16 psc,u8 master_slaver,u8 open_scheduled_transmition)
{
	SPI_InitTypeDef   SPI_InitStructure;
	DMA_InitTypeDef   DMA_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
	
	//SPI��ʼ��
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = (master_slaver==1)?SPI_Mode_Master:SPI_Mode_Slave;//����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//ѡ���˴���ʱ�ӵ���̬:ʱ�����ո�
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//���ݲ����ڵڶ���ʱ����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(SPI1, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
	
	
	// SPI����
	DMA_DeInit(DMA1_Channel2);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI1->DR;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)DMA_SPI_buff_RX;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = DMA_SPI_buff_len;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel2, &DMA_InitStructure);
	
	//SPI ����
	DMA_DeInit(DMA1_Channel3);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI1->DR;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)DMA_SPI_buff_TX;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = DMA_SPI_buff_len;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel3, &DMA_InitStructure);
	
	DMA_ITConfig(DMA1_Channel3, DMA_IT_TC, ENABLE);//��������ж�
	DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);
	//DMA_ITConfig(DMA1_Channel3, DMA_IT_TE, ENABLE);//��������ж�
	//DMA_ITConfig(DMA1_Channel2, DMA_IT_TE, ENABLE);
	
	/* Enable SPI1 DMA TX request */
	SPI1->CR2 |= 1<<1;
	
	/* Enable SPI1 DMA RX request */
	SPI1->CR2 |= 1<<0;
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//��ʱ����
	if(open_scheduled_transmition)
	{
		TIM2_Int_Init(arr,psc);
		TIM2->CNT=0;
		TIM_Cmd(TIM2,ENABLE);
	}
	
	DMA_Cmd(DMA1_Channel2, ENABLE);
	DMA_Cmd(DMA1_Channel3, DISABLE);
	SPI_Cmd(SPI1, ENABLE); //ʹ��SPI����
}

void SPI_send(const u16 send_buff[DMA_SPI_buff_len])
{
	//����װ��
	int i=0;
	for(i=0;i<DMA_SPI_buff_len;i++)
		DMA_SPI_buff_TX[i]=send_buff[i];
	
	//����
	DMA1_Channel3->CNDTR=DMA_SPI_buff_len;
	DMA_Cmd(DMA1_Channel3, ENABLE);
	
}

//�жϺ���
void DMA1_Channel3_IRQHandler(void)//SPI�������
{
	if (DMA_GetITStatus(DMA1_IT_TC3)!=RESET)
	{
		//do something
		
		DMA_Cmd(DMA1_Channel3, DISABLE);
		
		DMA_ClearITPendingBit(DMA1_IT_TC3);
	}
}

void DMA1_Channel2_IRQHandler(void)//SPI�������
{
	if (DMA_GetITStatus(DMA1_IT_TC2)!=RESET)
	{
		//do something
		
		DMA_Cmd(DMA1_Channel2,DISABLE);
		DMA1_Channel2->CNDTR=4;
		DMA_Cmd(DMA1_Channel2,ENABLE);
		
		DMA_ClearITPendingBit(DMA1_IT_TC2);
	}
}

void TIM2_IRQHandler(void)//SPI����
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		//do something

		DMA1_Channel3->CNDTR=4;
		DMA_Cmd(DMA1_Channel3, ENABLE);
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //���TIMx���жϴ�����λ:TIM �ж�Դ 
	}
}
