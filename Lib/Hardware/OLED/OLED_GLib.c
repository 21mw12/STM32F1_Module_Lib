#include "OLED_GLib.h"
#include "delay.h"
#include <math.h>

uint8_t GARM[OLED_GRAM_Size];

void OLED_GLib_Init(void) {
	OLED_Init();
	
	for (uint16_t i = 0; i < OLED_GRAM_Size; i++) {
		GARM[i] = 0x00;
	}
}

void OLED_RefreshRam(void) {
	uint16_t k = 0;
	
	for (uint8_t y = 0; y < OLED_Line / 8; y++) {
		OLED_SetCursor(y, 0);
		
		for (uint8_t x = 0; x < OLED_Column; x++) {
			OLED_WriteData(GARM[k++]);
		}
	}
}

void OLED_Clear(void) {
	uint16_t k = 0;
	
	for (uint8_t y = 0; y < OLED_Line / 8; y++) {
		OLED_SetCursor(y, 0);
		for(uint8_t x = 0; x < OLED_Column; x++) {
			OLED_WriteData(0x00);
			GARM[k++] = 0x00;
		}
	}
}

void OLED_DrawPoint(uint8_t X, uint8_t Y) {
	GARM[Y / 8 * 128 + X] |= 0x01 << (Y % 8);
}

void OLED_ClearPoint(uint8_t X, uint8_t Y) {
	GARM[Y / 8 * 128 + X] &= 0xFE << (Y % 8);
}

void OLED_DrawLine(uint8_t X_start, uint8_t Y_start, uint8_t X_end, uint8_t Y_end, uint8_t step) {
	uint8_t lengthX = (X_end > X_start) ? X_end - X_start : X_start - X_end;	// x轴方向的长度
	uint8_t lengthY = (Y_end > Y_start) ? Y_end - Y_start : Y_start - Y_end;	// x轴方向的长度
	
	uint8_t dm = (lengthX > lengthY) ? lengthX : lengthY;
	
	float dx = (float)lengthX / dm;		// x轴方向每次的变化量
	float dy = (float)lengthY / dm;		// x轴方向每次的变化量
	
	float x = X_start + 0.5;	// 保证四舍五入
	float y = Y_start + 0.5;
	
	for (uint8_t i = 0; i <= dm; i++) {
		if (!(i % step)) {
			OLED_DrawPoint(x, y);
		}
		
		x += dx;
		y += dy;
	}
}

void OLED_ClearLine(uint8_t X_start, uint8_t Y_start, uint8_t X_end, uint8_t Y_end, uint8_t step) {
	uint8_t lengthX = (X_end > X_start) ? X_end - X_start : X_start - X_end;	// x轴方向的长度
	uint8_t lengthY = (Y_end > Y_start) ? Y_end - Y_start : Y_start - Y_end;	// x轴方向的长度
	
	uint8_t dm = (lengthX > lengthY) ? lengthX : lengthY;
	
	float dx = (float)lengthX / dm;		// x轴方向每次的变化量
	float dy = (float)lengthY / dm;		// x轴方向每次的变化量
	
	float x = X_start + 0.5;	// 保证四舍五入
	float y = Y_start + 0.5;
	
	for (uint8_t i = 0; i <= dm; i++) {
		if (!(i % step)) {
			OLED_ClearPoint(x, y);
		}
		
		x += dx;
		y += dy;
	}
}

// 待优化
void OLED_DrawRectangle(uint8_t X_start, uint8_t Y_start, uint8_t X_length, uint8_t Y_length, FillPattern pattern) {
	if (pattern == Fill) {
		for (uint8_t i = 0; i <= X_length; i++) {
			OLED_DrawLine(X_start + i, Y_start, X_start + i, Y_start + Y_length, 1);
		}
	} else {		
		OLED_DrawLine(X_start, Y_start, X_start + X_length, Y_start, 1);
		OLED_DrawLine(X_start, Y_start, X_start, Y_start + Y_length, 1);
		OLED_DrawLine(X_start + X_length, Y_start, X_start + X_length, Y_start + Y_length, 1);
		OLED_DrawLine(X_start, Y_start + Y_length, X_start + X_length, Y_start + Y_length, 1);
	}
}

void OLED_DrawCircle(uint8_t X_center, uint8_t Y_center, uint8_t radius, FillPattern pattern) {
	uint8_t x0 = 0;
	uint8_t y0 = radius;
	int8_t d = 3 - 2 * radius;
	
	while (x0 <= y0) {
		if (pattern == Fill) {
			OLED_DrawLine(X_center - x0, Y_center + y0, X_center + x0, Y_center + y0, 1);
			OLED_DrawLine(X_center - y0, Y_center + x0, X_center + y0, Y_center + x0, 1);
			OLED_DrawLine(X_center - y0, Y_center - x0, X_center + y0, Y_center - x0, 1);
			OLED_DrawLine(X_center - x0, Y_center - y0, X_center + x0, Y_center - y0, 1);
		} else {
			/* 极坐标打印顺序 */
			OLED_DrawPoint(X_center + y0, Y_center - x0);
			OLED_DrawPoint(X_center + x0, Y_center - y0);
			OLED_DrawPoint(X_center - x0, Y_center - y0);
			OLED_DrawPoint(X_center - y0, Y_center - x0);
			OLED_DrawPoint(X_center - y0, Y_center + x0);
			OLED_DrawPoint(X_center - x0, Y_center + y0);
			OLED_DrawPoint(X_center + x0, Y_center + y0);
			OLED_DrawPoint(X_center + y0, Y_center + x0);
		}
		
		if (d < 0) {
			d += 4 * x0 + 6;
		} else {
			d += 4 * (x0 - y0) + 10;
			y0--;
		}
		x0++;
	}
}

void OLED_DrawEllipse(uint8_t X_center, uint8_t Y_center, uint8_t X_radius, uint8_t Y_radius, FillPattern pattern) {
	double Rad, x0, y0;
	
	for (uint16_t angle = 0; angle < 360; angle++) {
		Rad = angle * 3.14 / 180;
		
		x0 = X_radius * cos(Rad);
		y0 = Y_radius * sin(Rad);
		
		OLED_DrawPoint(X_center + x0, Y_center + y0);
	}
}

void OLED_DrawRoundedRectangle(uint8_t X_start, uint8_t Y_start, uint8_t X_length, uint8_t Y_length, uint8_t radius, uint8_t wide) {
	uint8_t A, B, C, D;
	uint8_t x0 = 0;
	uint8_t y0 = radius;
	int8_t d = 3 - 2 * radius;

	if (radius * 2 > X_length || radius * 2 > Y_length)
		radius = (X_length > Y_length) ? (Y_length / 2) : (X_length / 2);
	if (wide > radius)
		wide = radius;

	/** 四个坐标值，组合形成拆分后的四个圆的圆心坐标
			右上圆心坐标（B, A）
			左上圆心坐标（C, A）
			左下圆心坐标（B, D）
			右下圆心坐标（C, D）
	*/	
	A = Y_start + radius;
	B = X_start + radius;
	C = X_start + X_length - radius;
	D = Y_start + Y_length - radius;
	
	while (x0 <= y0) {
		if (wide == 1) {
			/* 极坐标打印顺序 */
			OLED_DrawPoint(C + y0, A - x0);
			OLED_DrawPoint(C + x0, A - y0);
			OLED_DrawPoint(B - x0, A - y0);
			OLED_DrawPoint(B - y0, A - x0);
			OLED_DrawPoint(B - y0, D + x0);
			OLED_DrawPoint(B - x0, D + y0);
			OLED_DrawPoint(C + x0, D + y0);
			OLED_DrawPoint(C + y0, D + x0);
		} else {
			/* 极坐标打印顺序 */
			OLED_DrawLine(C + y0 - wide, A - x0, C + y0, A - x0, 1);
			OLED_DrawLine(C + x0, A - y0, C + x0, A - y0 + wide, 1);
			OLED_DrawLine(B - x0, A - y0, B - x0, A - y0 + wide, 1);
			OLED_DrawLine(B - y0, A - x0, B - y0 + wide, A - x0, 1);
			OLED_DrawLine(B - y0, D + x0, B - y0 + wide, D + x0, 1);
			OLED_DrawLine(B - x0, D + y0 - wide, B - x0, D + y0, 1);
			OLED_DrawLine(C + x0, D + y0 - wide, C + x0, D + y0, 1);
			OLED_DrawLine(C + y0 - wide, D + x0, C + y0, D + x0, 1);
		}
		
		if (d < 0) {
			d += 4 * x0 + 6;
		} else {
			d += 4 * (x0 - y0) + 10;
			y0--;
		}
		x0++;
	}
	
	for (int i = 0; i < wide; i++) {
		OLED_DrawLine(B, A - radius + i, C, A - radius + i, 1);
		OLED_DrawLine(C + radius - i, A, C + radius - i, D, 1);
		OLED_DrawLine(B, D + radius - i, C, D + radius - i, 1);
		OLED_DrawLine(B - radius + i, A, B - radius + i, D, 1);
	}
}

// 绘制动态波形图，循环队列方法？
void OLED_ShowDynamicData(uint32_t data, uint32_t data_Max) {
	float scale = (float)(OLED_Line -1) / data_Max;
	
	for (uint8_t i = OLED_Column - 1; i > 0; i--) {
		for (uint8_t j = 0; j < 8; j++) {
			GARM[j * OLED_Column + i] = GARM[j * OLED_Column + i - 1];
		}
	}
}

/**
  * @brief 画面密度单元（2*2）
  * @param (x, y) 要点亮的单元坐标
	*						————————
  * 				 | (0,0) | (1,0) |
	*						————————
  * 				 | (0,1) | (1,1) |
	*						————————
  * @return 无
  */
void OLED_DensityUnit(uint8_t x, uint8_t y, uint8_t* image) {
	for (uint8_t i = y; i < OLED_Line; i += 2) {
		for(uint8_t j = x; j < OLED_Column; j += 2) {
			GARM[i / 8 * 128 + j] |= ((0x01 << (i % 8)) & image[i / 8 * 128 + j]);
		}
	}
}

void OLED_SetDensity(ShowPercent percent) {
	if (percent == Zero_Percent) {
			return;
	}
	
	uint8_t GGARM[OLED_GRAM_Size];
	
	for (uint16_t i = 0; i < OLED_GRAM_Size; i++) {
		GGARM[i] = GARM[i];
		GARM[i] = 0x00;
	}
	
	switch((uint8_t) percent) {
		case 1:
			OLED_DensityUnit(0, 0, GGARM);
			break;
		case 2:
			OLED_DensityUnit(0, 0, GGARM);
			OLED_DensityUnit(1, 1, GGARM);
			break;
		case 3:
			OLED_DensityUnit(0, 0, GGARM);
			OLED_DensityUnit(1, 0, GGARM);
			OLED_DensityUnit(1, 1, GGARM);
			break;
		case 4:
			OLED_DensityUnit(0, 0, GGARM);
			OLED_DensityUnit(1, 0, GGARM);
			OLED_DensityUnit(0, 1, GGARM);
			OLED_DensityUnit(1, 1, GGARM);
			break;
	}
}

void OLED_ShowImg(uint8_t X, uint8_t Y, uint8_t img_Length, uint8_t img_High, uint8_t* image) {
	uint8_t errValue = Y % 8;									// 计算单个显示单元（高8像素的竖棍）的偏移误差
	uint8_t totalHigh = img_High + errValue;		// 图片实际高度
	uint8_t temp = 0x00;											// 偏移数据临时变量
	
	uint8_t scanLineStart = Y / 8;						// 计算Y轴方向从几行开始
	uint8_t scanLine = totalHigh / 8 + ((totalHigh % 8) ? 1 : 0);	// 计算Y轴方向需要扫描几行
	
	uint16_t GARMIndeInit = scanLineStart * OLED_Column + X;
	uint16_t GARMInde = GARMIndeInit;		// 缓存索引表达式：(i + scanLineStart) * 128 + j + X
	uint16_t imgInde = 0;								// 图片索引表达式：i * imgLength + j
	
	for (uint8_t j = 0; j < img_Length; j++) {
		GARMInde += j;
		imgInde += j;
		
		for (uint8_t i = 0; i < scanLine; i++) {			
			GARM[GARMInde] = temp | (image[imgInde] << errValue);
			temp = image[imgInde] >> (8 - errValue);
			
			GARMInde += 128;
			imgInde += img_Length;
		}
		GARMInde = GARMIndeInit;
		imgInde = 0;
	}
}
