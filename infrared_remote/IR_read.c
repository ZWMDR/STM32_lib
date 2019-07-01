#include "IR_read.h"

void IR_Init(void)
{
	IR_flag=0;
	Remote_Init();
}

u8 IR_read(void)
{
	u8 IR_instruct=remote_key();
	
	//do something
	
	return IR_instruct;
}