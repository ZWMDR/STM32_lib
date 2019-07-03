#ifndef __IR_H
#define __IR_H

#include "sys.h"
#include "delay.h"
#include "GUI.h"

#define RDATA 	PAin(1)

#define REMOTE_ID 0

typedef struct IR_Menu_InitTypeDef
{
	u8 status;
	u8 select_status;
	u8 promote_rule;//晋升规则
	/*-------------
	promote_rule
	0: 二级菜单=一级菜单*10
	1：二级菜单=一级菜单+10
	--------------*/
	u8 level;//菜单等级
	u8 max_level;
	
}IR_Menu_InitTypeDef;

extern u8 RmtCnt;
extern u8 IR_flag;

void IR_Init(void);
u8 IR_read(u8* IR_instruct);
u8 IR_Menu_selet(GUI_Menu_InitTypeDef* Menu,IR_Menu_InitTypeDef* IR_Menu);

#endif
