#ifndef __GUI_H
#define __GUI_H
#include "lcd.h"
#include "led.h"

/*--------------------������ʾ�Ӵ�------------------------*/

typedef struct GUI_WaveWindow_msg//���β���
{
	u16 lst_xcoord;
	u16 lst_ycoord;
	u16 xcoord;
	u16 ycoord;
	u8 show;//�Ƿ���Ҫ��ʾ�����£�
}WW_msg;

typedef struct GUI_waveform_InitTypeDef//������ʾ����
{
	u16 point_color;//������ɫ
	u8 wave_form;//����
	u8 refresh_type;//ˢ�·�ʽ
	
	WW_msg msg;
	
}GUI_wf_InitTypeDef;
/*--------------------
     wave_form
   0: ��ͨ����ʵ��
   1: ˫��ʵ��
   2: ��������
   3: ˫������
   4: ����ʽ����

    refresh_type
    0: ����ˢ��
    1: ÿ��ˢ��
--------------------*/

typedef struct GUI_WaveWindow_guide_line_InitTypeDef//�ȼ��ο������ò���
{
	u8 set_gd;//�Ƿ����òο���
	u8 gd_num;//�ο�������
	u8 wire_type;//�ο�������
	/*---------------
	wave_form
   0: ����ʵ��
   2: ��������
	----------------*/
	
	u16 gd_color;//�ο�����ɫ
	u16 gd_coord;//�ο�����ʼλ��
	u16 gd_interval;//�ο��߼��
	
}GUI_WW_gd_InitTypeDef;

typedef struct GUI_WaveWindow_InitTypeDef//���δ��ڲ���
{
	//�Ӵ���С
	u16 start_xcoord;
	u16 start_ycoord;
	u16 end_xcoord;
	u16 end_ycoord;
	u16 back_color;
	
	//�Ӵ����Ͳ���
	u16 num_lines;//�Ӵ���������
	GUI_wf_InitTypeDef *lines;//�Ӵ����Ͳ���
	
	//������
	u8 set_axle_wire;//�Ƿ�����������
	u16 axle_wire_ycoord;//������λ��
	u16 axle_wire_color;//��������ɫ
	
	//����ο���
	u8 set_vertical_gd;
	GUI_WW_gd_InitTypeDef *vertical_gd;
	
	//����ο���
	u8 set_hroizontal_gd;
	GUI_WW_gd_InitTypeDef *horizontal_gd;
	
}GUI_WW_InitTypeDef;

/*--------------------��Ϣ��ʾ�Ӵ�------------------------*/
typedef struct GUI_msg_num_TypeDef
{
	char* header;
	float number;
	u8 size;
	
	u8 digits_header;//���ⳤ��
	u8 digits_latter;//С����ǰλ��
	u8 digits_former;//С�����λ��
	u16 ycoord;
	
}GUI_msg_num;

typedef struct GUI_msg_str_TypeDef
{
	char* header;
	char* content;
	u8 size;
	
	u8 digits_header;//���ⳤ��
	u8 digits_content;//���ݳ���
	u16 ycoord;
	
}GUI_msg_str;

typedef struct GUI_MsgWindow_InitTypeDef
{
	//�Ӵ���С
	u16 start_xcoord;
	u16 start_ycoord;
	u16 end_xcoord;
	u16 end_ycoord;
	u16 back_color;
	
	u8 alignment;
	u16 axle;
	/*---------------
	���뷽ʽ
	0�������
	1: �ж���
	----------------*/
	
	u16 num_num;
	u16 str_num;
	u16 header_color;
	u16 msg_color;
	GUI_msg_num* msgs_num;
	GUI_msg_str* msgs_str;
	
}GUI_MW_InitTypeDef;

/*---------------------�˵���------------------------*/

typedef struct GUI_Menu_catalog_table//�˵�����
{
	char* content;
	u8 size;//�ֺ�
	u8 length;//�ַ�����
	u16 xcoord;
	u16 ycoord;
	
}GUI_catalog_table;

typedef struct GUI_Menu_InitTypeDef
{
	//�˵����ڲ���
	u16 start_xcoord;
	u16 start_ycoord;
	u16 end_xcoord;
	u16 end_ycoord;
	
	//������ɫ��ѡ����ɫ
	u16 back_color;
	u16 point_color;
	u16 select_back_color;
	u16 select_point_color;
	
	//��ʾ���
	u8 show_frame;
	u8 frame_mode;
	/*--------------
	0: ����ʾ���
	1: �������
	2: ˫�����
	3: �������
	11:�����������
	12:˫���������
	13:�����������
	--------------*/
	u16 frame_color;
	
	//�˵�����
	u8 table_num;//�˵���Ŀ
	GUI_catalog_table* catalog_tables;//��������
	
}GUI_Menu_InitTypeDef;


/*---------------------�����------------------------*/

typedef struct GUI_InputBox_InitTypeDef
{
	u16 start_xcoord;
	u16 start_ycoord;
	u16 end_xcoord;
	u16 end_ycoord;
	
	u16 back_color;
	u16 point_color;
	u16 select_back_color;
	u16 select_point_color;
	
	u8 show_frame;
	u8 frame_mode;
	u16 frame_color;
	
	char* header;
	u8 digit_header;
	u8 digit_fromer;
	u8 digit_later;
	u8* digits;
	u8 size;
	u16 header_color;
	u16 digits_color;
	u16 xcoord;
	u16 ycoord;
	float number;
	
}GUI_IB_InitTypeDef;

void GUI_Init(void);//��ʼ��
void GUI_clear(void);//����

void GUI_show_frame(u8 frame_mode,u16 frame_color,u16 start_xcoord,u16 start_ycoord,u16 end_xcoord,u16 end_ycoord);


void GUI_WaveWindow_Init(GUI_WW_InitTypeDef *GUI_WW);//GUI�����Ӵ���ʼ��
void GUI_WaveWindow_refresh(GUI_WW_InitTypeDef *GUI_WW);//GUI�����Ӵ�ˢ��


void GUI_MsgWindow_Init(GUI_MW_InitTypeDef* GUI_MW); //GUI��Ϣ�Ӵ���ʼ��
void GUI_MsgWindow_refresh(GUI_MW_InitTypeDef *GUI_MW);//GUI��Ϣ�Ӵ�ˢ��


//�˵�


//ѡ��˵�
u8 GUI_Menu_Init(GUI_Menu_InitTypeDef* Menu);//�˵���ʼ��
u8 GUI_Menu_Select(GUI_Menu_InitTypeDef *Menu,u8 select_status);//�˵�ѡ��

//�����
void GUI_InputBox_Init(GUI_IB_InitTypeDef* GUI_IB,u8 select_status);


#endif
