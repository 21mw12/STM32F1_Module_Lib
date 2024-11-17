#include "InkScreen.h"
#include "InkScreen_Font.h"
#include "SPISoftware.h"
#include "Delay.h"

#define InkScreen_Pin_RES_Set(BitVal)		GPIO_WriteBit(Ink_Screen_Port, Ink_Screen_Pin_RES, BitVal)
#define InkScreen_Pin_DC_Set(BitVal)		GPIO_WriteBit(Ink_Screen_Port, Ink_Screen_Pin_DC, BitVal)
#define InkScreen_Pin_CS_Set(BitVal)		GPIO_WriteBit(Ink_Screen_Port, Ink_Screen_Pin_CS, BitVal)

#define InkScreen_Wide		152 
#define InkScreen_High		152

typedef struct {
	CanvasLayer *layer;
	uint16_t width;
	uint16_t height;
	uint16_t widthByte;
	uint16_t heightByte;
	CanvasColourType color;
	uint16_t rotate;
} CANVAS_Info;

CANVAS_Info CanvasInfo;
uint8_t InkScreen_BlackLayer[2888];	// 黑色图层
uint8_t InkScreen_RedLayer[2888];		// 红色图层
void InkScreen_CanvasInit(void);

CanvasColourType CANVAS_Colourless = 0xFF;	// 无色	
CanvasColourType CANVAS_Coloured = 0x00;		// 着色

/**
  * @brief 墨水屏写字节
  * @param ComType 0表示指令，1表示数据
  * @param Data  写入的字节
  * @return 无
  */
void InkScreen_Write(uint8_t ComType, uint8_t Data) {
	InkScreen_Pin_DC_Set(ComType);
	InkScreen_Pin_CS_Set(0);
	SPI_Software_SwapByte(Data);
	InkScreen_Pin_CS_Set(1);	
	InkScreen_Pin_DC_Set(1);
}

/**
  * @brief 墨水屏等待空闲
  * @return 无
  */
void InkScreen_WaitBusy(void) {
	while(1) {
    if (0 == GPIO_ReadInputDataBit(Ink_Screen_Port, Ink_Screen_Pin_BUSY)) {
      break;
    }
  }
}

void InkScreen_Init(void) {
	/* 时钟初始化 */
	RCC_APB2PeriphClockCmd(Ink_Screen_GPIOPeriph, ENABLE);
	
	/* 端口初始化 */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = Ink_Screen_Pin_RES | Ink_Screen_Pin_DC | Ink_Screen_Pin_CS;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Ink_Screen_Port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = Ink_Screen_Pin_BUSY;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(Ink_Screen_Port, &GPIO_InitStructure);
	
	/* 画布初始化 */
	InkScreen_CanvasInit();
	InkScreen_SelectLayer(InkScreen_BlackLayer);
	InkScreen_LayerClear();
	InkScreen_SelectLayer(InkScreen_RedLayer);
	InkScreen_LayerClear();
}

void InkScreen_Wakeup(void) {
	/* 硬件复位 */
  Delay_ms(100);
  InkScreen_Pin_RES_Set(0);
  Delay_ms(10);
  InkScreen_Pin_RES_Set(1);
  Delay_ms(10);
  InkScreen_WaitBusy();
	
  /* SWRESET */
	// 调整E-Paper默认显示方向?
  InkScreen_Write(0, 0x12);
  InkScreen_WaitBusy();   
}

void InkScreen_DeepSleep(void) {
  InkScreen_Write(0, 0x10);
  InkScreen_Write(1, 0x01);
  Delay_ms(200);
}

void InkScreen_Clear(void) {
	// E-Paper刷白屏
  InkScreen_Write(0, 0x24);
  for(uint16_t i = 0; i < 2888; i++) {
    InkScreen_Write(1, 0xFF);
  }
	
  InkScreen_WaitBusy();
	
  InkScreen_Write(0, 0x26);
  for(uint16_t i = 0; i < 2888; i++) {
    InkScreen_Write(1, 0x00);
  }
}

void InkScreen_Display(void) {
  uint16_t Width = (InkScreen_Wide % 8 == 0) ? (InkScreen_Wide / 8) : (InkScreen_Wide / 8 + 1);
  uint16_t Height = InkScreen_High;
	
	/* 数组数据更新到E-Paper */
  InkScreen_Write(0, 0x24);
  for (uint16_t i = 0; i < Height; i++) {
    for (uint16_t j = 0; j < Width; j++) {
      InkScreen_Write(1, InkScreen_BlackLayer[i * Width + j]);
    }
  }
  InkScreen_Write(0, 0x26);
  for (uint16_t i = 0; i < Height; i++) {
    for (uint16_t j = 0; j < Width; j++) {
      InkScreen_Write(1, ~InkScreen_RedLayer[i * Width + j]);
    }
  }
	
	/* 更新显示内容到E-Paper */
	InkScreen_Write(0, 0x20);
  InkScreen_WaitBusy();
}

/*****************************************画布绘制函数************************************************/

/**
  * @brief 指数运算
  * @param m 底数
  * @param n 指数
  * @return m的n次方
  */
uint32_t Pow(uint16_t m,uint16_t n) {
	uint32_t result = 1;
	while(n--) {
	  result *= m;
	}
	return result;
}

/**
  * @brief 墨水屏画布参数初始化
  * @return 无
  */
void InkScreen_CanvasInit(void) {
	CanvasInfo.layer = 0x00;		// 不绑定任何图层
	CanvasInfo.color = CANVAS_Colourless;
	CanvasInfo.width = InkScreen_Wide;
	CanvasInfo.height = InkScreen_High;
	CanvasInfo.widthByte = (InkScreen_Wide % 8 == 0) ? (InkScreen_Wide / 8 ) : (InkScreen_Wide / 8 + 1);
	CanvasInfo.heightByte = InkScreen_High;     
	CanvasInfo.rotate = Rotation;
	
	if(Rotation == 0 || Rotation == 180) {
		CanvasInfo.width = InkScreen_High;
		CanvasInfo.height = InkScreen_Wide;
	} else {
		CanvasInfo.width = InkScreen_Wide;
		CanvasInfo.height = InkScreen_High;
	}
}

void InkScreen_SelectLayer(CanvasLayer *layer) {
	CanvasInfo.layer = layer;
}

void InkScreen_LayerClear(void) {
	uint32_t index;
  for(uint16_t Y = 0; Y < CanvasInfo.heightByte; Y++) {
    for(uint16_t X = 0; X < CanvasInfo.widthByte; X++) {   
      index = Y * CanvasInfo.widthByte + X;
      CanvasInfo.layer[index] = CANVAS_Colourless;
    }
  }
}

void InkScreen_DrawPoint(uint8_t X, uint8_t Y, CanvasColourType ColorType) {	
	switch (CanvasInfo.rotate) {
		case 0:
				Y = CanvasInfo.height - Y - 1;		
				break;
		case 90:
				X = CanvasInfo.width - Y - 1;
				Y = CanvasInfo.height - X - 1;
				break;
		case 180:
				X = CanvasInfo.width - X - 1;
				break;
		case 270:
				break;
		default:
				return;
	}
	
	/* 计算对应下标，取出内存中的数据 */
	uint16_t index = X / 8 + Y * CanvasInfo.widthByte;
	uint8_t RamData = CanvasInfo.layer[index];
	
	/* 修改指定位置数据 */
	if(ColorType == CANVAS_Coloured) {    
		CanvasInfo.layer[index] = RamData & ~(0x80 >> (X % 8));
	} else {
		CanvasInfo.layer[index] = RamData | (0x80 >> (X % 8));
	}
}

void InkScreen_DrawLine(uint8_t X_start, uint8_t Y_start, uint8_t X_end, uint8_t Y_end, uint8_t step, CanvasColourType ColorType) {
	uint8_t lengthX = (X_end > X_start) ? X_end - X_start : X_start - X_end;	// x轴方向的长度
	uint8_t lengthY = (Y_end > Y_start) ? Y_end - Y_start : Y_start - Y_end;	// x轴方向的长度
	
	uint8_t dm = (lengthX > lengthY) ? lengthX : lengthY;
	
	float dx = (float)lengthX / dm;		// x轴方向每次的变化量
	float dy = (float)lengthY / dm;		// x轴方向每次的变化量
	
	float x = X_start + 0.5;	// 保证四舍五入
	float y = Y_start + 0.5;
	
	for (uint8_t i = 0; i <= dm; i++) {
		if (!(i % step)) {
			InkScreen_DrawPoint(x, y, CANVAS_Coloured);
		}
		
		x += dx;
		y += dy;
	}
}

void InkScreen_DrawRectangle(uint8_t X_start, uint8_t Y_start, uint8_t X_length, uint8_t Y_length, uint8_t wide, CanvasColourType ColorType) {
	if (wide == 1) {
		InkScreen_DrawLine(X_start, Y_start, X_start + X_length, Y_start, 1, ColorType);
		InkScreen_DrawLine(X_start, Y_start, X_start, Y_start + Y_length, 1, ColorType);
		InkScreen_DrawLine(X_start + X_length, Y_start, X_start + X_length, Y_start + Y_length, 1, ColorType);
		InkScreen_DrawLine(X_start, Y_start + Y_length, X_start + X_length, Y_start + Y_length, 1, ColorType);
	} else {
		/* 绘制横向边框 */
		for (uint8_t i = 0; i <= X_length; i++) {
			InkScreen_DrawLine(X_start + i, Y_start, X_start + i, Y_start + wide, 1, ColorType);
			InkScreen_DrawLine(X_start + i, Y_length - wide, X_start + i, Y_length, 1, ColorType);
		}
		/* 绘制纵向边框 */
		for (uint8_t i = 0; i <= Y_length - wide * 2; i++) {
			InkScreen_DrawLine(X_start, Y_start + wide + i, X_start + wide, Y_start + wide + i, 1, ColorType);
			InkScreen_DrawLine(X_start + X_length - wide, Y_start + wide + i, X_start + X_length, Y_start + wide + i, 1, ColorType);
		}
	}
}


void InkScreen_DrawCircle(uint8_t X_center, uint8_t Y_center, uint8_t radius, uint8_t wide, CanvasColourType ColorType) {
	uint8_t x0 = 0;
	uint8_t y0 = radius;
	int8_t d = 3 - 2 * radius;
	
	while (x0 <= y0) {
		if (wide == 1) {
			/* 极坐标打印顺序 */
			InkScreen_DrawPoint(X_center + y0, Y_center - x0, ColorType);
			InkScreen_DrawPoint(X_center + x0, Y_center - y0, ColorType);
			InkScreen_DrawPoint(X_center - x0, Y_center - y0, ColorType);
			InkScreen_DrawPoint(X_center - y0, Y_center - x0, ColorType);
			InkScreen_DrawPoint(X_center - y0, Y_center + x0, ColorType);
			InkScreen_DrawPoint(X_center - x0, Y_center + y0, ColorType);
			InkScreen_DrawPoint(X_center + x0, Y_center + y0, ColorType);
			InkScreen_DrawPoint(X_center + y0, Y_center + x0, ColorType);
		} else {
			/* 极坐标打印顺序 */
			InkScreen_DrawLine(X_center + y0 - wide, Y_center - x0, X_center + y0, Y_center - x0, 1, ColorType);
			InkScreen_DrawLine(X_center + x0, Y_center - y0, X_center + x0, Y_center - y0 + wide, 1, ColorType);
			InkScreen_DrawLine(X_center - x0, Y_center - y0, X_center - x0, Y_center - y0 + wide, 1, ColorType);
			InkScreen_DrawLine(X_center - y0, Y_center - x0, X_center - y0 + wide, Y_center - x0, 1, ColorType);
			InkScreen_DrawLine(X_center - y0, Y_center + x0, X_center - y0 + wide, Y_center + x0, 1, ColorType);
			InkScreen_DrawLine(X_center - x0, Y_center + y0 - wide, X_center - x0, Y_center + y0, 1, ColorType);
			InkScreen_DrawLine(X_center + x0, Y_center + y0 - wide, X_center + x0, Y_center + y0, 1, ColorType);
			InkScreen_DrawLine(X_center + y0 - wide, Y_center + x0, X_center + y0, Y_center + x0, 1, ColorType);
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


void InkScreen_DrawPicture(uint16_t X, uint16_t Y, uint16_t wide, uint16_t high, const uint8_t picture[], CanvasColourType ColorType) {
	uint16_t index = 0;
	uint8_t RamData;
	uint16_t LoopNum = wide * (high / 8 + ((high % 8) ? 1 : 0));	
	uint16_t tempY = Y;
	
  for(uint16_t i = 0; i < LoopNum; i++) {
		RamData = picture[index++];
		
		for(uint8_t j = 0; j < 8; j++) {
		 if(RamData & 0x80){
			 InkScreen_DrawPoint(X, Y, ColorType);
		 } else {
			 InkScreen_DrawPoint(X, Y, !ColorType);
		 }
		 Y++;
		 RamData <<= 1;
		}
		
		if((Y - tempY) == high) {
			Y = tempY;
			X++;
		}
	}
}

void InkScreen_DrawChar(uint8_t X, uint8_t Y, char Char, uint8_t Front_size, CanvasColourType ColorType) {
	uint8_t temp;
	uint8_t tempX = X;
	uint8_t tempY = Y;
	
	uint8_t Front_wide;
	if(Front_size == 8) {
		Front_wide=6;
	} else {
		// 得到字体一个字符对应点阵集所占的字节数
		Front_wide = (Front_size / 8 + ((Front_size % 8) ? 1 : 0)) * (Front_size / 2);
	}
	
	for(uint8_t i = 0; i < Front_wide; i++) {
		switch(Front_size) {
			case 8:
				temp = InkScreen_F8x6[Char-' '][i];
				break;
			case 12:
				temp = InkScreen_F12x6[Char-' '][i];
				break;
			case 16:
				temp = InkScreen_F16x8[Char-' '][i];
				break;
			case 24:
				temp = InkScreen_F24x12[Char-' '][i];
				break;
			case 48:
				temp = InkScreen_F48x24[Char-' '][i];
				break;
			default:
				break;
		}	
		
		for(uint8_t j = 0; j < 8; j++) {
			if (temp & 0x01) InkScreen_DrawPoint(X, Y, ColorType);
			else InkScreen_DrawPoint(X, Y, !ColorType);
			temp >>= 1;
			Y++;
		}
		X++;
		if((Front_size != 8) && ((X - tempX) == Front_size / 2)) {
			X = tempX;
			tempY = tempY + 8;
		}
		
		Y = tempY;
	}
}

void InkScreen_DrawString(uint8_t X, uint8_t Y, char* String, uint8_t Front_size, CanvasColourType ColorType) {
	uint8_t Front_wide = 0;
	switch(Front_size) {
		case 8:
			Front_wide = 6;
			break;
		case 12:
			Front_wide = 6;
			break;
		case 16:
			Front_wide = 8;
			break;
		case 24:
			Front_wide = 12;
			break;
		case 48:
			Front_wide = 24;
			break;
		default:
			break;
	}
	
	for (uint8_t i = 0; String[i] != '\0'; i++) {
		InkScreen_DrawChar(X + i * Front_wide, Y, String[i], Front_size, ColorType);
	}
}

void InkScreen_DrawNum(uint8_t X, uint8_t Y,uint32_t Num, uint16_t Len, uint8_t Front_size, CanvasColourType ColorType) {
	uint8_t param = Front_size / 2;
	if (param == 8) param += 2;
	
	uint8_t temp;
	for(uint8_t i = 0; i < Len; i++) {
		temp = (Num / Pow(10, Len-i-1)) % 10;
		InkScreen_DrawChar(i * param + X, Y, temp + '0',Front_size, ColorType);
  }
}

/* 绘制单个12x12汉字 */ 
void InkScreen_DrawChinese12x12(uint8_t X, uint8_t Y, uint8_t* Chinese, uint8_t Front_size, CanvasColourType ColorType) {
	uint8_t i,j;
	uint16_t k;
	uint16_t HZnum;//汉字数目
	uint16_t TypefaceNum;//一个字符所占字节大小
	uint16_t x0=X;
	TypefaceNum=(Front_size/8+((Front_size%8)?1:0))*Front_size;                    
	HZnum=sizeof(tfont12)/sizeof(typFNT_GB12);	//统计汉字数目
	for(k=0;k<HZnum;k++) {
		if((tfont12[k].Index[0]==*(Chinese))&&(tfont12[k].Index[1]==*(Chinese+1))) { 	
			for(i=0;i<TypefaceNum;i++) {
				for(j=0;j<8;j++) {	
						if(tfont12[k].Msk[i]&(0x01<<j))	InkScreen_DrawPoint(X,Y,ColorType);//画一个点
						X++;
						if((X-x0)==Front_size) {
							X=x0;
							Y++;
							break;
						}
				}
			}
		}				  	
		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
	}
} 

/* 绘制单个16x16汉字 */
void InkScreen_DrawChinese16x16(uint8_t X, uint8_t Y, uint8_t* Chinese, uint8_t Front_size, CanvasColourType ColorType) {
	uint8_t i,j;
	uint16_t k;
	uint16_t HZnum;//汉字数目
	uint16_t TypefaceNum;//一个字符所占字节大小
	uint16_t x0=X;
  TypefaceNum=(Front_size/8+((Front_size%8)?1:0))*Front_size;
	HZnum=sizeof(tfont16)/sizeof(typFNT_GB16);	//统计汉字数目
	for(k=0;k<HZnum;k++) 
	{
		if ((tfont16[k].Index[0]==*(Chinese))&&(tfont16[k].Index[1]==*(Chinese+1)))
		{ 	
			for(i=0;i<TypefaceNum;i++)
			{
				for(j=0;j<8;j++)
				{	
						if(tfont16[k].Msk[i]&(0x01<<j))	InkScreen_DrawPoint(X,Y,ColorType);//画一个点
						X++;
						if((X-x0)==Front_size) {
							X=x0;
							Y++;
							break;
						}
				}
			}
		}				  	
		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
	}
} 


/* 绘制单个24x24汉字 */
void InkScreen_DrawChinese24x24(uint8_t X, uint8_t Y, uint8_t* Chinese, uint8_t Front_size, CanvasColourType ColorType) {
	uint8_t i,j;
	uint16_t k;
	uint16_t HZnum;//汉字数目
	uint16_t TypefaceNum;//一个字符所占字节大小
	uint16_t x0=X;
  TypefaceNum=(Front_size/8+((Front_size%8)?1:0))*Front_size;
	HZnum=sizeof(tfont24)/sizeof(typFNT_GB24);	//统计汉字数目
	for(k=0;k<HZnum;k++) 
	{
		if ((tfont24[k].Index[0]==*(Chinese))&&(tfont24[k].Index[1]==*(Chinese+1)))
		{ 	
			for(i=0;i<TypefaceNum;i++)
			{
				for(j=0;j<8;j++)
				{	
					if(tfont24[k].Msk[i]&(0x01<<j))	InkScreen_DrawPoint(X,Y,ColorType);//画一个点
					X++;
						if((X-x0)==Front_size) {
							X=x0;
							Y++;
							break;
						}
				}
			}
		}				  	
		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
	}
} 

/* 绘制单个32x32汉字 */
void InkScreen_DrawChinese32x32(uint8_t X, uint8_t Y, uint8_t* Chinese, uint8_t Front_size, CanvasColourType ColorType) {
	uint8_t i,j;
	uint16_t k;
	uint16_t HZnum;//汉字数目
	uint16_t TypefaceNum;//一个字符所占字节大小
	uint16_t x0=X;
  TypefaceNum=(Front_size/8+((Front_size%8)?1:0))*Front_size;
	HZnum=sizeof(tfont32)/sizeof(typFNT_GB32);	//统计汉字数目
	for(k=0;k<HZnum;k++) 
	{
		if ((tfont32[k].Index[0]==*(Chinese))&&(tfont32[k].Index[1]==*(Chinese+1)))
		{ 	
			for(i=0;i<TypefaceNum;i++)
			{
				for(j=0;j<8;j++)
				{	
						if(tfont32[k].Msk[i]&(0x01<<j))	InkScreen_DrawPoint(X,Y,ColorType);//画一个点
						X++;
						if((X-x0)==Front_size) {
							X=x0;
							Y++;
							break;
						}
				}
			}
		}				  	
		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
	}
}


void InkScreen_DrawChinese(uint8_t X, uint8_t Y, uint8_t* Chinese, uint8_t Front_size, CanvasColourType ColorType) {
	while(*Chinese != 0) {
		if(Front_size == 12) InkScreen_DrawChinese12x12(X, Y, Chinese, Front_size, ColorType);
		else if(Front_size == 16) InkScreen_DrawChinese16x16(X, Y, Chinese, Front_size, ColorType);
		else if(Front_size == 24) InkScreen_DrawChinese24x24(X, Y, Chinese, Front_size, ColorType);
		else if(Front_size == 32) InkScreen_DrawChinese32x32(X, Y, Chinese, Front_size, ColorType);
		else return;
		Chinese += 2;
		X += Front_size;
	}
}
