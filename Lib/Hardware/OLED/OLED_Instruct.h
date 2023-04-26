#ifndef __OLED_INSTRUCT_H
#define __OLED_INSTRUCT_H

///////////////////////////////////////////////////////////
//
// 文件功能：OLED指令文件
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/4/26
//
///////////////////////////////////////////////////////////

// 屏幕开启/关闭
#define Display_ON				0xAF
#define Display_OFF				0xAE

// 屏幕正常/反色显示
#define Display_Color_Nomal			0xA6
#define Display_Color_Inverse		0xA7

// 屏幕上下是否反转
#define Display_Up_Down_Nomal			0xC8
#define Display_Up_Down_Inverse		0xC0

// 屏幕左右是否反转
#define Display_Left_Right_Nomal			0xA1
#define Display_Left_Right_Inverse		0xA0

// 设置屏幕对比度(亮度)
#define Set_Display_Luminance				0x81
#define Display_Luminance_Value			0x7F		// 亮度值（范围：0x00 ~ 0xFF）

// 设置屏幕显示偏移
#define Set_Display_Skew			0xD3
#define Display_Skew_Value		0x00


// 设置显示开始行
#define Display_Start_Line		0x40

// 设置充电泵
#define Set_Display_ChargePump			0x8D
#define Display_ChargePump_Value		0x14

// 设置显示时钟分频比/振荡器频率
#define Set_Display_ClockOSC				0xD5
#define Display_ClockOSC_Value			0x80

// 设置多路复用率
#define Set_Display_Multiplexing			0xA8
#define Display_Multiplexing_Value		0x1F

// 设置预充电周期
#define Set_Display_ChargingCycle			0xD9
#define Display_ChargingCycle_Value		0xF1

// 设置COM引脚硬件配置
#define Set_Display_COMPinConfig			0xDA
#define Display_COMPinConfig_Value		0x02		// 0x12 0.96寸屏幕128*64分辨率
																							// 0x02 0.91寸屏屏幕128*32分辨率

// 设置VCOMH取消选择级别
#define Set_Display_VCOMH				0xDB
#define Display_VCOMH_Value			0x40		//[6:4] 000：0.65*vcc
																				//      001：0.77*vcc
																				//			011：0.83*vcc;

#endif
