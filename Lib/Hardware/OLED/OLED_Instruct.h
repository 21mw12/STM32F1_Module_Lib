#ifndef __OLED_INSTRUCT_H
#define __OLED_INSTRUCT_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�OLEDָ���ļ�
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/4/26
//
///////////////////////////////////////////////////////////

// ��Ļ����/�ر�
#define Display_ON				0xAF
#define Display_OFF				0xAE

// ��Ļ����/��ɫ��ʾ
#define Display_Color_Nomal			0xA6
#define Display_Color_Inverse		0xA7

// ��Ļ�����Ƿ�ת
#define Display_Up_Down_Nomal			0xC8
#define Display_Up_Down_Inverse		0xC0

// ��Ļ�����Ƿ�ת
#define Display_Left_Right_Nomal			0xA1
#define Display_Left_Right_Inverse		0xA0

// ������Ļ�Աȶ�(����)
#define Set_Display_Luminance				0x81
#define Display_Luminance_Value			0x7F		// ����ֵ����Χ��0x00 ~ 0xFF��

// ������Ļ��ʾƫ��
#define Set_Display_Skew			0xD3
#define Display_Skew_Value		0x00


// ������ʾ��ʼ��
#define Display_Start_Line		0x40

// ���ó���
#define Set_Display_ChargePump			0x8D
#define Display_ChargePump_Value		0x14

// ������ʾʱ�ӷ�Ƶ��/����Ƶ��
#define Set_Display_ClockOSC				0xD5
#define Display_ClockOSC_Value			0x80

// ���ö�·������
#define Set_Display_Multiplexing			0xA8
#define Display_Multiplexing_Value		0x1F

// ����Ԥ�������
#define Set_Display_ChargingCycle			0xD9
#define Display_ChargingCycle_Value		0xF1

// ����COM����Ӳ������
#define Set_Display_COMPinConfig			0xDA
#define Display_COMPinConfig_Value		0x02		// 0x12 0.96����Ļ128*64�ֱ���
																							// 0x02 0.91������Ļ128*32�ֱ���

// ����VCOMHȡ��ѡ�񼶱�
#define Set_Display_VCOMH				0xDB
#define Display_VCOMH_Value			0x40		//[6:4] 000��0.65*vcc
																				//      001��0.77*vcc
																				//			011��0.83*vcc;

#endif
