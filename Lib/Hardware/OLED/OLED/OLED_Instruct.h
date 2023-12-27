#ifndef __OLED_INSTRUCT_H
#define __OLED_INSTRUCT_H

///////////////////////////////////////////////////////////
//
// 文件功能：OLED指令文件
// 版本：V1.1
// 作者：墨蔚（MW）
// 修改时间：2023/12/27
//
///////////////////////////////////////////////////////////

#define OLED_Command								0x00
#define OLED_Data										0x40

#define Display_SetAddressPattern		0x20		// 设置OLED显存地址模式
#define Set_Display_ColumnPinConfig	0xDA		// 设置列引脚硬件配置
#define Set_Display_Luminance				0x81		// 设置屏幕对比度(亮度)
#define Set_Display_Skew						0xD3		// 设置屏幕显示偏移
#define Display_Start_Line					0x40		// 设置显示开始行
#define Set_Display_ChargePump			0x8D		// 设置充电泵
#define Set_Display_RefreshRate			0xD5		// 设置显示刷新率（范围：0x10 ~ 0xF0）
#define Set_Display_Multiplexing		0xA8		// 设置多路复用率（范围：0x00 ~ 0x3F）
#define Set_Display_ChargingCycle		0xD9		// 设置预充电周期
#define Set_Display_VCOMH						0xDB		// 设置VCOMH取消选择级别

#define Display_ON									0xAF		// 屏幕开启/关闭
#define Display_OFF									0xAE
#define Display_VideoMemory_ON			0xA4		// 显存开启/关闭
#define Display_VideoMemory_OFF			0xA5
#define Display_Color_Nomal					0xA6		// 屏幕正常/反色显示
#define Display_Color_Inverse				0xA7
#define Display_Up_Down_Nomal				0xC8		// 屏幕上下是否反转
#define Display_Up_Down_Inverse			0xC0
#define Display_Left_Right_Nomal		0xA1		// 屏幕左右是否反转
#define Display_Left_Right_Inverse	0xA0

#endif
