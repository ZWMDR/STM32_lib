#include "GUI.h"

u16 zoom_in[5]={0,10,100,1000,10000};

void GUI_Init(void)
{
	LCD_Init();
	LCD_Fill(0,305,240,320,MAGENTA);
	POINT_COLOR=WHITE;
	BACK_COLOR=MAGENTA;
	LCD_ShowString(68,306,200,12,12,"Designed by ZWMDR");
}



void draw_consistant_FullLine(u16 start_xcoord,u16 end_xcoord,u16 ycoord)//横向贯通实线
{
	LCD_DrawLine(start_xcoord,ycoord,end_xcoord,ycoord);
}

void draw_consistant_ImaginaryLine(u16 start_xcoord,u16 end_xcoord,u16 ycoord)//横向贯通虚线
{
	u16 i;
	for(i=start_xcoord;i<end_xcoord;i+=4)
	{
		LCD_DrawLine(i,ycoord,i+2,ycoord);
	}
}

void draw_vconsistant_FullLine(u16 xcoord,u16 start_ycoord,u16 ycoord)//纵向贯通实线
{
	LCD_DrawLine(xcoord,0,xcoord,320);
}

void draw_vconsistant_ImaginaryLine(u16 xcoord,u16 start_ycoord,u16 end_ycoord)//纵向贯通虚线
{
	u16 i;
	for(i=start_ycoord;i<end_ycoord;i+=4)
	{
		LCD_DrawLine(xcoord,i,xcoord,i+2);
	}
}

void draw_arb_FullLine(u16 start_xcoord,u16 end_xcoord,u16 ycoord)//任意实线
{
	LCD_DrawLine(start_xcoord,ycoord,end_xcoord,ycoord);
}

void draw_arb_ImaginaryLine(u16 start_xcoord,u16 end_xcoord,u16 ycoord)//任意虚线
{
	
}

void GUI_WaveWindow_Init(GUI_WW_InitTypeDef *GUI_WW)//初始化波形视窗
{
	u16 i;
	u16 coord;
	
	if(GUI_WW->start_xcoord>=GUI_WW->end_xcoord || GUI_WW->start_ycoord>=GUI_WW->end_ycoord)
		return;
	
	//视窗范围填充
	LCD_Fill(GUI_WW->start_xcoord,GUI_WW->start_ycoord,GUI_WW->end_xcoord,GUI_WW->end_ycoord,GUI_WW->back_color);
	
	if(GUI_WW->set_axle_wire)//中轴线
	{
		POINT_COLOR=GUI_WW->axle_wire_color;
		draw_consistant_FullLine(0,240,GUI_WW->axle_wire_ycoord);
		draw_consistant_FullLine(0,240,GUI_WW->axle_wire_ycoord+1);
	}
	if(GUI_WW->vertical_gd->set_gd)//纵向参考线
	{
		POINT_COLOR=GUI_WW->vertical_gd->gd_color;
		if(GUI_WW->vertical_gd->wire_type==0)//实参考线
		{
			coord=GUI_WW->vertical_gd->gd_coord;
			for(i=0;i<GUI_WW->vertical_gd->gd_num;i++)
			{
				draw_consistant_FullLine(GUI_WW->start_xcoord,GUI_WW->end_xcoord,coord);
				coord+=GUI_WW->vertical_gd->gd_interval;
			}
		}
		else if(GUI_WW->vertical_gd->wire_type==2)//虚参考线
		{
			coord=GUI_WW->vertical_gd->gd_coord;
			for(i=0;i<GUI_WW->vertical_gd->gd_num;i++)
			{
				draw_consistant_ImaginaryLine(GUI_WW->start_xcoord,GUI_WW->end_xcoord,coord);
				coord+=GUI_WW->vertical_gd->gd_interval;
			}
		}
	}
	
	if(GUI_WW->horizontal_gd->set_gd)//纵向参考线
	{
		POINT_COLOR=GUI_WW->horizontal_gd->gd_color;
		if(GUI_WW->horizontal_gd->wire_type==0)//实参考线
		{
			coord=GUI_WW->horizontal_gd->gd_coord;
			for(i=0;i<GUI_WW->horizontal_gd->gd_num;i++)
			{
				draw_vconsistant_FullLine(coord,GUI_WW->start_ycoord,GUI_WW->end_ycoord);
				coord+=GUI_WW->horizontal_gd->gd_interval;
			}
		}
		else if(GUI_WW->horizontal_gd->wire_type==2)//虚参考线
		{
			coord=GUI_WW->horizontal_gd->gd_coord;
			for(i=0;i<GUI_WW->horizontal_gd->gd_num;i++)
			{
				draw_vconsistant_ImaginaryLine(coord,GUI_WW->start_ycoord,GUI_WW->end_ycoord);
				coord+=GUI_WW->horizontal_gd->gd_interval;
			}
		}
	}
}


void GUI_MsgWindow_Init(GUI_MW_InitTypeDef* GUI_MW)
{
	u16 i;
	u16 xcoord;
	u16 ycoord;
	u8 size;
	float temp;
	short adcx;
	if(GUI_MW->start_xcoord>=GUI_MW->end_xcoord || GUI_MW->start_ycoord>=GUI_MW->end_ycoord)
		return;
	
	//视窗范围填充
	BACK_COLOR=GUI_MW->back_color;
	LCD_Fill(GUI_MW->start_xcoord,GUI_MW->start_ycoord,GUI_MW->end_xcoord,GUI_MW->end_ycoord,GUI_MW->back_color);
	
	//数字内容
	if(GUI_MW->alignment==0)//靠左对齐
	{
		for(i=0;i<GUI_MW->num_num;i++)
		{
			size=GUI_MW->msgs_num[i].size;
			xcoord=GUI_MW->start_xcoord;
			ycoord=GUI_MW->msgs_num[i].ycoord;
			POINT_COLOR=GUI_MW->header_color;
			LCD_ShowString(xcoord,ycoord,180,size,size,(u8*)(GUI_MW->msgs_num[i].header));
			
			POINT_COLOR=GUI_MW->msg_color;
			xcoord+=size/2*GUI_MW->msgs_num[i].digits_header;
			temp=GUI_MW->msgs_num[i].number;
			adcx=temp;
			LCD_ShowxNum(xcoord,ycoord,adcx,GUI_MW->msgs_num[i].digits_former,size,0);
			temp-=adcx;
			temp*=zoom_in[GUI_MW->msgs_num[i].digits_latter];
			xcoord+=size/2*(GUI_MW->msgs_num[i].digits_former+1);
			LCD_ShowxNum(xcoord,ycoord,temp,GUI_MW->msgs_num[i].digits_latter,size,0);
		}
	}
	else if(GUI_MW->alignment==1)//居中对齐
	{
		for(i=0;i<GUI_MW->num_num;i++)
		{
			xcoord=GUI_MW->axle;
			ycoord=GUI_MW->msgs_num[i].ycoord;
			size=GUI_MW->msgs_num[i].size/2;
			POINT_COLOR=GUI_MW->header_color;
			LCD_ShowString(xcoord-GUI_MW->msgs_num[i].digits_header*size,ycoord,180,GUI_MW->msgs_num[i].size,GUI_MW->msgs_num[i].size,(u8*)GUI_MW->msgs_num[i].header);
			
			POINT_COLOR=GUI_MW->msg_color;
			temp=GUI_MW->msgs_num[i].number;
			adcx=temp;
			LCD_ShowxNum(xcoord,ycoord,adcx,GUI_MW->msgs_num[i].digits_former,GUI_MW->msgs_num[i].size,0);
			temp-=adcx;
			temp*=zoom_in[GUI_MW->msgs_num[i].digits_latter];
			xcoord+=size*(GUI_MW->msgs_num[i].digits_former+1);
			LCD_ShowxNum(xcoord,ycoord,temp,GUI_MW->msgs_num[i].digits_latter,GUI_MW->msgs_num[i].size,0);
		}
	}
	
	//字符内容
	if(GUI_MW->alignment==0)//靠左对齐
	{
		for(i=0;i<GUI_MW->str_num;i++)
		{
			size=GUI_MW->msgs_str[i].size;
			xcoord=GUI_MW->start_xcoord;
			ycoord=GUI_MW->msgs_str[i].ycoord;
			POINT_COLOR=GUI_MW->header_color;
			LCD_ShowString(xcoord,ycoord,180,size,size,(u8*)(GUI_MW->msgs_str[i].header));
			
			POINT_COLOR=GUI_MW->msg_color;
			xcoord+=size/2*GUI_MW->msgs_str[i].digits_header;
			LCD_ShowString(xcoord,ycoord,180,size,size,(u8*)(GUI_MW->msgs_str[i].content));
		}
	}
	else if(GUI_MW->alignment==1)//居中对齐
	{
		for(i=0;i<GUI_MW->str_num;i++)
		{
			xcoord=GUI_MW->axle;
			ycoord=GUI_MW->msgs_str[i].ycoord;
			size=GUI_MW->msgs_str[i].size/2;
			POINT_COLOR=GUI_MW->header_color;
			LCD_ShowString(xcoord-GUI_MW->msgs_str[i].digits_header*size,ycoord,180,GUI_MW->msgs_num[i].size,GUI_MW->msgs_num[i].size,(u8*)GUI_MW->msgs_str[i].header);
			
			POINT_COLOR=GUI_MW->msg_color;
			LCD_ShowString(xcoord,ycoord,180,GUI_MW->msgs_num[i].size,GUI_MW->msgs_num[i].size,(u8*)GUI_MW->msgs_str[i].content);
		}
	}
	
}



void Level1_Menu(u8 select_status)
{
	if(select_status==0)
	{
		POINT_COLOR=RED;
		BACK_COLOR=WHITE;
		LCD_ShowString(38,200,200,24,24,"Tracing Mode");
		LCD_ShowString(38,250,200,24,24,"Clipping Mode");
	}
	else if(select_status==1)
	{
		POINT_COLOR=RED;
		BACK_COLOR=YELLOW;
		LCD_ShowString(38,200,200,24,24,"Tracing Mode");
		BACK_COLOR=WHITE;
		LCD_ShowString(38,250,200,24,24,"Clipping Mode");
	}
	else if(select_status==2)
	{
		POINT_COLOR=RED;
		BACK_COLOR=WHITE;
		LCD_ShowString(38,200,200,24,24,"Tracing Mode");
		BACK_COLOR=YELLOW;
		LCD_ShowString(38,250,200,24,24,"Clipping Mode");
	}
}

void Level2_Menu(u8 select_status)
{
	
}

