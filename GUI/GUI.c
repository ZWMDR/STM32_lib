#include "GUI.h"

u16 zoom_in[5]={0,10,100,1000,10000};

void draw_consistant_FullLine(u16 start_xcoord,u16 end_xcoord,u16 ycoord)//�����ͨʵ��
{
	LCD_DrawLine(start_xcoord,ycoord,end_xcoord,ycoord);
}

void draw_consistant_ImaginaryLine(u16 start_xcoord,u16 end_xcoord,u16 ycoord)//�����ͨ����
{
	u16 i;
	for(i=start_xcoord;i<end_xcoord;i+=4)
	{
		LCD_DrawLine(i,ycoord,i+2,ycoord);
	}
}

void draw_vconsistant_FullLine(u16 xcoord,u16 start_ycoord,u16 ycoord)//�����ͨʵ��
{
	LCD_DrawLine(xcoord,0,xcoord,320);
}

void draw_vconsistant_ImaginaryLine(u16 xcoord,u16 start_ycoord,u16 end_ycoord)//�����ͨ����
{
	u16 i;
	for(i=start_ycoord;i<end_ycoord;i+=4)
	{
		LCD_DrawLine(xcoord,i,xcoord,i+2);
	}
}

void draw_arb_FullLine(u16 start_xcoord,u16 end_xcoord,u16 ycoord)//����ʵ��
{
	LCD_DrawLine(start_xcoord,ycoord,end_xcoord,ycoord);
}

void draw_arb_ImaginaryLine(u16 start_xcoord,u16 end_xcoord,u16 ycoord)//��������
{
	
}

void GUI_Init(void)
{
	LCD_Init();
}

void GUI_WaveWindow_Init(GUI_WW_InitTypeDef *GUI_WW)//��ʼ�������Ӵ�
{
	u16 i;
	u16 coord;
	
	if(GUI_WW->start_xcoord>=GUI_WW->end_xcoord || GUI_WW->start_ycoord>=GUI_WW->end_ycoord)
		return;
	
	//�Ӵ���Χ���
	LCD_Fill(GUI_WW->start_xcoord,GUI_WW->start_ycoord,GUI_WW->end_xcoord,GUI_WW->end_ycoord,GUI_WW->back_color);
	
	if(GUI_WW->set_axle_wire)//������
	{
		POINT_COLOR=GUI_WW->axle_wire_color;
		draw_consistant_FullLine(0,240,GUI_WW->axle_wire_ycoord);
		draw_consistant_FullLine(0,240,GUI_WW->axle_wire_ycoord+1);
	}
	if(GUI_WW->vertical_gd->set_gd)//����ο���
	{
		POINT_COLOR=GUI_WW->vertical_gd->gd_color;
		if(GUI_WW->vertical_gd->wire_type==0)//ʵ�ο���
		{
			coord=GUI_WW->vertical_gd->gd_coord;
			for(i=0;i<GUI_WW->vertical_gd->gd_num;i++)
			{
				draw_consistant_FullLine(GUI_WW->start_xcoord,GUI_WW->end_xcoord,coord);
				coord+=GUI_WW->vertical_gd->gd_interval;
			}
		}
		else if(GUI_WW->vertical_gd->wire_type==2)//��ο���
		{
			coord=GUI_WW->vertical_gd->gd_coord;
			for(i=0;i<GUI_WW->vertical_gd->gd_num;i++)
			{
				draw_consistant_ImaginaryLine(GUI_WW->start_xcoord,GUI_WW->end_xcoord,coord);
				coord+=GUI_WW->vertical_gd->gd_interval;
			}
		}
	}
	
	if(GUI_WW->horizontal_gd->set_gd)//����ο���
	{
		POINT_COLOR=GUI_WW->horizontal_gd->gd_color;
		if(GUI_WW->horizontal_gd->wire_type==0)//ʵ�ο���
		{
			coord=GUI_WW->horizontal_gd->gd_coord;
			for(i=0;i<GUI_WW->horizontal_gd->gd_num;i++)
			{
				draw_vconsistant_FullLine(coord,GUI_WW->start_ycoord,GUI_WW->end_ycoord);
				coord+=GUI_WW->horizontal_gd->gd_interval;
			}
		}
		else if(GUI_WW->horizontal_gd->wire_type==2)//��ο���
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
	
	//�Ӵ���Χ���
	BACK_COLOR=GUI_MW->back_color;
	LCD_Fill(GUI_MW->start_xcoord,GUI_MW->start_ycoord,GUI_MW->end_xcoord,GUI_MW->end_ycoord,GUI_MW->back_color);
	
	//��������
	if(GUI_MW->alignment==0)//�������
	{
		ycoord=GUI_MW->start_ycoord;
		for(i=0;i<GUI_MW->num;i++)
		{
			xcoord=GUI_MW->start_xcoord;
			LCD_ShowString(xcoord,ycoord,180,GUI_MW->msgs_num[i].size,GUI_MW->msgs_num[i].size,(u8*)GUI_MW->msgs_num[i].header);
			xcoord+=size*GUI_MW->msgs_num[i].digits_header;
			temp=GUI_MW->msgs_num[i].number;
			adcx=temp;
			LCD_ShowxNum(xcoord,ycoord,adcx,GUI_MW->msgs_num[i].digits_former,size,0);
			temp-=adcx;
			temp*=zoom_in[GUI_MW->msgs_num[i].digits_latter];
			ycoord+=20;
		}
	}
	else if(GUI_MW->alignment==1)//���ж���
	{
		
	}
	
}

