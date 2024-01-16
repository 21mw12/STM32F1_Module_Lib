#ifndef __OLED_INSTRUCT_H
#define __OLED_INSTRUCT_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�OLEDָ���ļ�
// �汾��V1.1
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/12/27
//
///////////////////////////////////////////////////////////

#define OLED_Command								0x00
#define OLED_Data										0x40

#define Display_SetAddressPattern		0x20		// ����OLED�Դ��ַģʽ
#define Set_Display_ColumnPinConfig	0xDA		// ����������Ӳ������
#define Set_Display_Luminance				0x81		// ������Ļ�Աȶ�(����)
#define Set_Display_Skew						0xD3		// ������Ļ��ʾƫ��
#define Display_Start_Line					0x40		// ������ʾ��ʼ��
#define Set_Display_ChargePump			0x8D		// ���ó��ã�0X14������ 0X10�رգ�
#define Set_Display_RefreshRate			0xD5		// ������ʾˢ���ʣ���Χ��0x10 ~ 0xF0��
#define Set_Display_Multiplexing		0xA8		// ���ö�·�����ʣ���Χ��0x00 ~ 0x3F��
#define Set_Display_ChargingCycle		0xD9		// ����Ԥ�������
#define Set_Display_VCOMH						0xDB		// ����VCOMHȡ��ѡ�񼶱�

#define Display_ON									0xAF		// ��Ļ����/�ر�
#define Display_OFF									0xAE
#define Display_VideoMemory_ON			0xA4		// �Դ濪��/�ر�
#define Display_VideoMemory_OFF			0xA5
#define Display_Color_Nomal					0xA6		// ��Ļ����/��ɫ��ʾ
#define Display_Color_Inverse				0xA7
#define Display_Up_Down_Nomal				0xC8		// ��Ļ�����Ƿ�ת
#define Display_Up_Down_Inverse			0xC0
#define Display_Left_Right_Nomal		0xA1		// ��Ļ�����Ƿ�ת
#define Display_Left_Right_Inverse	0xA0

#endif
