#ifndef __OLED_H
#define __OLED_H

#include "stm32f10x.h"

/*
 * 0.96 寸 I2C OLED（SSD1306，128x64）
 * 软件 I2C：SCL = PB8，SDA = PB9（可在 OLED.c 开头修改）
 */

void OLED_Init(void);
void OLED_Clear(void);
void OLED_Update(void);                 /* 把显存刷到屏幕 */

/* 字符：Line 1~4，Column 1~16（8x16 字体） */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);

/* 数字 */
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

/* 中文：Line 1~4，Column 1~8（16x16 字体，传入 32 字节字模） */
void OLED_ShowChinese(uint8_t Line, uint8_t Column, const uint8_t *Chinese);

/* 绘图：X 0~127，Y 0~63 */
void OLED_DrawPoint(uint8_t X, uint8_t Y);
void OLED_DrawLine(uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2);
void OLED_ShowImage(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image);

#endif
