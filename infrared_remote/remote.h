#ifndef __RED_H
#define __RED_H 
#include "sys.h"  
#include "led.h"
  
#define RDATA 	PAin(1)	 	//�������������

#define REMOTE_ID 0      		   

extern u8 RmtCnt;			//�������µĴ���
extern u8 IR_flag;


void Remote_Init(void);    	//���⴫��������ͷ���ų�ʼ��
u8 Remote_Scan(void);	 
u8 remote_key(void);
#endif

