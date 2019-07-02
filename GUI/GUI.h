#ifndef __GUI_H
#define __GUI_H
#include "lcd.h"

/*--------------------波形显示视窗------------------------*/

typedef struct GUI_waveform_InitTypeDef//波形显示参数
{
	u16 point_color;
	u8 wave_form;
	u8 refresh_type;
	
}GUI_wf_InitTypeDef;
/*--------------------
     wave_form
   0: 普通单层实线
   1: 双层实线
   2: 单层虚线
   3: 双层虚线
   4: 覆盖式线型

    refresh_type
    0: 屏满刷新
    1: 每次刷新
--------------------*/

typedef struct GUI_WaveWindow_guide_line_InitTypeDef//等间距参考线设置参数
{
	u8 set_gd;//是否设置参考线
	u8 gd_num;//参考线数量
	u8 wire_type;//参考线线型
	/*---------------
	wave_form
   0: 单层实线
   2: 单层虚线
	----------------*/
	
	u16 gd_color;//参考线颜色
	u16 gd_coord;//参考线起始位置
	u16 gd_interval;//参考线间隔
	
}GUI_WW_gd_InitTypeDef;

typedef struct GUI_WaveWindow_InitTypeDef//波形窗口参数
{
	//视窗大小
	u16 start_xcoord;
	u16 start_ycoord;
	u16 end_xcoord;
	u16 end_ycoord;
	u16 back_color;
	
	//视窗线型参数
	u16 num_lines;//视窗线型种类
	GUI_wf_InitTypeDef *lines;//视窗线性参数
	
	//中轴线
	u8 set_axle_wire;//是否设置中轴线
	u16 axle_wire_ycoord;//中轴线位置
	u16 axle_wire_color;//中轴线颜色
	
	//纵向参考线
	GUI_WW_gd_InitTypeDef *vertical_gd;
	
	//横向参考线
	GUI_WW_gd_InitTypeDef *horizontal_gd;
	
}GUI_WW_InitTypeDef;

/*--------------------信息显示视窗------------------------*/
typedef struct GUI_msg_num_TypeDef
{
	char* header;
	float number;
	u8 size;
	
	u8 digits_header;//标题长度
	u8 digits_latter;//小数点前位数
	u8 digits_former;//小数点后位数
	
}GUI_msg_num;

typedef struct GUI_msg_str_TypeDef
{
	char* header;
	char* content;
	u8 size;
	
	u8 digits_header;//标题长度
	u8 digits_content;//内容长度
	
}GUI_msg_str;

typedef struct GUI_MsgWindow_InitTypeDef
{
	//视窗大小
	u16 start_xcoord;
	u16 start_ycoord;
	u16 end_xcoord;
	u16 end_ycoord;
	u16 back_color;
	
	u8 alignment;
	u16 axle;
	/*---------------
	对齐方式
	0：左对齐
	中对齐
	----------------*/
	
	u16 num;
	u16 header_color;
	u16 msg_color;
	GUI_msg_num* msgs_num;
	GUI_msg_str* msgs_str;
	
}GUI_MW_InitTypeDef;


void GUI_Init(void);
void GUI_WaveWindow_Init(GUI_WW_InitTypeDef *GUI_WW);//GUI波形视窗初始化

#endif
