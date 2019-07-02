#ifndef __GUI_H
#define __GUI_H
#include "lcd.h"

/*--------------------������ʾ�Ӵ�------------------------*/

typedef struct GUI_waveform_InitTypeDef//������ʾ����
{
	u16 point_color;
	u8 wave_form;
	u8 refresh_type;
	
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
	GUI_wf_InitTypeDef *lines;//�Ӵ����Բ���
	
	//������
	u8 set_axle_wire;//�Ƿ�����������
	u16 axle_wire_ycoord;//������λ��
	u16 axle_wire_color;//��������ɫ
	
	//����ο���
	GUI_WW_gd_InitTypeDef *vertical_gd;
	
	//����ο���
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
	
}GUI_msg_num;

typedef struct GUI_msg_str_TypeDef
{
	char* header;
	char* content;
	u8 size;
	
	u8 digits_header;//���ⳤ��
	u8 digits_content;//���ݳ���
	
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
	�ж���
	----------------*/
	
	u16 num;
	u16 header_color;
	u16 msg_color;
	GUI_msg_num* msgs_num;
	GUI_msg_str* msgs_str;
	
}GUI_MW_InitTypeDef;


void GUI_Init(void);
void GUI_WaveWindow_Init(GUI_WW_InitTypeDef *GUI_WW);//GUI�����Ӵ���ʼ��

#endif
