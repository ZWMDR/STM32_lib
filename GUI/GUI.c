#include "GUI.h"

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

void GUI_Init(void)
{
	LCD_Init();
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

