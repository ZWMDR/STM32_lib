#ifndef __RED_H
#define __RED_H 
#include "sys.h"  
#include "led.h"
  
#define RDATA 	PAin(1)	 	//红外数据输入脚

#define REMOTE_ID 0      		   

extern u8 RmtCnt;			//按键按下的次数
extern u8 IR_flag;


void Remote_Init(void);    	//红外传感器接收头引脚初始化
u8 Remote_Scan(void);	 
u8 remote_key(void);
#endif

