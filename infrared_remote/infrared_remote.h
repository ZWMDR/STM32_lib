#ifndef __IR_H
#define __IR_H

#include "sys.h"
#include "delay.h"
#include "GUI.h"
#include "math.h"

#define RDATA 	PAin(1)

#define REMOTE_ID 0

typedef struct IR_Input_Box_Msg
{
	GUI_IB_InitTypeDef* GUI_IB;
	u8 select_status;
	u8 select;
	
}IR_IB_Msg;


typedef struct IR_Menu_InitTypeDef
{
	u8 status;
	u8 select_status;
	u8 promote_rule;//��������
	u8 menu_type;
	/*-------------
	promote_rule
	0: �����˵�=һ���˵�*10
	1�������˵�=һ���˵�+10
	--------------*/
	
	u8 level;//�˵��ȼ�
	u8 max_level;
	
}IR_Menu_InitTypeDef;

extern u8 RmtCnt;
extern u8 IR_flag;

void IR_Init(void);
u8 IR_read(u8* IR_instruct);

//�˵�
u8 IR_Menu_selet(GUI_Menu_InitTypeDef* Menu,IR_Menu_InitTypeDef* IR_Menu);

//�����
u8 IR_Input_Box_select(IR_IB_Msg* IB_Msg);


float IR_IB_number_assign(IR_IB_Msg* IB_Msg);

#endif
