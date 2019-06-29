#ifndef __SPI_DMA_H
#define __SPI_DMA_H

#include "stm32f10x_dma.h"
#include "sys.h"
#include "timer.h"

#define DMA_SPI_buff_len 4
extern u16 DMA_SPI_buff_TX[DMA_SPI_buff_len];
extern u16 DMA_SPI_buff_RX[DMA_SPI_buff_len];

void SPI1_DMA1_Init(u16 arr,u16 psc,u8 master_slaver,u8 open_scheduled_transmition);
/*
������master_slaver=1     �ӻ���master_slaver=0
��ʱ����ʱ���ͣ�open_scheduled_transmition=1������open_scheduled_transmition=0
*/

void SPI_send(const u16 send_buff[DMA_SPI_buff_len]);
/*
SPI�������ݷ��ͣ����ղ���DMA�жϷ�ʽ
�������ݱ���������send_buff�У����鳤�ȹ̶�Ϊ DMA_SPI_buff_len
*/


#endif
