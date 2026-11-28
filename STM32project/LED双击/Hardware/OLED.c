#include "stm32f10x.h"
#include "delay.h"
#include "OLED.h"
#include "OLED_Font.h"

/*==================== 引脚 / 地址 ====================*/
#define OLED_SCL_PORT   GPIOB
#define OLED_SCL_PIN    GPIO_Pin_8
#define OLED_SDA_PORT   GPIOB
#define OLED_SDA_PIN    GPIO_Pin_9
#define OLED_I2C_ADDR   0x78        /* 0x3C<<1；不亮可试 0x7A */

#define OLED_SCL_H()    GPIO_SetBits(OLED_SCL_PORT, OLED_SCL_PIN)
#define OLED_SCL_L()    GPIO_ResetBits(OLED_SCL_PORT, OLED_SCL_PIN)
#define OLED_SDA_H()    GPIO_SetBits(OLED_SDA_PORT, OLED_SDA_PIN)
#define OLED_SDA_L()    GPIO_ResetBits(OLED_SDA_PORT, OLED_SDA_PIN)

/* 你 OLED_Font.h 里 8x16 ASCII 数组叫什么就填什么 */
#define FONT_8X16       F8X16

static uint8_t OLED_GRAM[8][128];   /* 显存：8 页 × 128 列 = 1KB */

/*==================== 软件 I2C ====================*/
static void OLED_I2C_Delay(void)
{
    volatile uint16_t i = 10;
    while (i--);
}

static void OLED_I2C_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_OD;   /* I2C 必须开漏 */
    GPIO_InitStructure.GPIO_Pin   = OLED_SCL_PIN | OLED_SDA_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    OLED_SCL_H();
    OLED_SDA_H();
}

static void OLED_I2C_Start(void)
{
    OLED_SDA_H(); OLED_I2C_Delay();
    OLED_SCL_H(); OLED_I2C_Delay();
    OLED_SDA_L(); OLED_I2C_Delay();
    OLED_SCL_L(); OLED_I2C_Delay();
}

static void OLED_I2C_Stop(void)
{
    OLED_SDA_L(); OLED_I2C_Delay();
    OLED_SCL_H(); OLED_I2C_Delay();
    OLED_SDA_H(); OLED_I2C_Delay();
}

static void OLED_I2C_SendByte(uint8_t Byte)
{
    uint8_t i;

    for (i = 0; i < 8; i++)
    {
        if (Byte & 0x80) OLED_SDA_H();
        else             OLED_SDA_L();
        Byte <<= 1;
        OLED_I2C_Delay();

        OLED_SCL_H(); OLED_I2C_Delay();
        OLED_SCL_L(); OLED_I2C_Delay();
    }

    /* 第 9 个时钟：ACK，这里不检测，直接放过 */
    OLED_SDA_H(); OLED_I2C_Delay();
    OLED_SCL_H(); OLED_I2C_Delay();
    OLED_SCL_L(); OLED_I2C_Delay();
}

static void OLED_WriteCommand(uint8_t Command)
{
    OLED_I2C_Start();
    OLED_I2C_SendByte(OLED_I2C_ADDR);
    OLED_I2C_SendByte(0x00);            /* 命令 */
    OLED_I2C_SendByte(Command);
    OLED_I2C_Stop();
}

/*==================== 初始化 ====================*/
void OLED_Init(void)
{
    OLED_I2C_Init();
    delay_ms(100);

    OLED_WriteCommand(0xAE);    /* 关显示 */
    OLED_WriteCommand(0xD5); OLED_WriteCommand(0x80);   /* 时钟分频 */
    OLED_WriteCommand(0xA8); OLED_WriteCommand(0x3F);   /* 复用率 1/64 */
    OLED_WriteCommand(0xD3); OLED_WriteCommand(0x00);   /* 显示偏移 */
    OLED_WriteCommand(0x40);                            /* 起始行 */
    OLED_WriteCommand(0x8D); OLED_WriteCommand(0x14);   /* 电荷泵 */
    OLED_WriteCommand(0x20); OLED_WriteCommand(0x00);   /* 水平寻址 */
    OLED_WriteCommand(0xA1);                            /* 列重映射 */
    OLED_WriteCommand(0xC8);                            /* 行扫描反向 */
    OLED_WriteCommand(0xDA); OLED_WriteCommand(0x12);   /* COM 引脚 */
    OLED_WriteCommand(0x81); OLED_WriteCommand(0xCF);   /* 对比度 */
    OLED_WriteCommand(0xD9); OLED_WriteCommand(0xF1);   /* 预充电 */
    OLED_WriteCommand(0xDB); OLED_WriteCommand(0x40);   /* VCOMH */
    OLED_WriteCommand(0xA4);                            /* 按显存显示 */
    OLED_WriteCommand(0xA6);                            /* 正常显示 */
    OLED_WriteCommand(0x2E);                            /* 关滚动 */
    OLED_WriteCommand(0xAF);                            /* 开显示 */

    OLED_Clear();
}

/*==================== 刷屏 / 清屏 ====================*/
void OLED_Update(void)
{
    uint8_t page, i;

    for (page = 0; page < 8; page++)
    {
        OLED_WriteCommand((uint8_t)(0xB0 + page));  /* 页地址 */
        OLED_WriteCommand(0x00);                    /* 列低 4 位 */
        OLED_WriteCommand(0x10);                    /* 列高 4 位 */

        OLED_I2C_Start();
        OLED_I2C_SendByte(OLED_I2C_ADDR);
        OLED_I2C_SendByte(0x40);
        for (i = 0; i < 128; i++)
        {
            OLED_I2C_SendByte(OLED_GRAM[page][i]);
        }
        OLED_I2C_Stop();
    }
}

void OLED_Clear(void)
{
    uint8_t page, x;

    for (page = 0; page < 8; page++)
    {
        for (x = 0; x < 128; x++)
        {
            OLED_GRAM[page][x] = 0x00;
        }
    }
    OLED_Update();
}

/*==================== 字符 ====================*/
static void OLED_PutChar(uint8_t Line, uint8_t Column, char Char)
{
    uint8_t i, Page, X;

    if (Line < 1 || Line > 4 || Column < 1 || Column > 16) return;
    if (Char < ' ' || Char > '~') Char = '?';

    Page = (uint8_t)((Line - 1) * 2);
    X    = (uint8_t)((Column - 1) * 8);

    for (i = 0; i < 8; i++)
    {
        OLED_GRAM[Page][X + i]     = FONT_8X16[(Char - 32) * 16 + i];
        OLED_GRAM[Page + 1][X + i] = FONT_8X16[(Char - 32) * 16 + i + 8];
    }
}

void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{
    OLED_PutChar(Line, Column, Char);
    OLED_Update();
}

void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)
{
    uint8_t i = 0;

    while (String[i] != '\0')
    {
        OLED_PutChar(Line, (uint8_t)(Column + i), String[i]);
        i++;
    }
    OLED_Update();
}

/*==================== 数字 ====================*/
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    char s[12];
    uint8_t i;

    if (Length > 10) Length = 10;

    for (i = 0; i < Length; i++)
    {
        s[Length - 1 - i] = (char)('0' + Number % 10);
        Number /= 10;
    }
    s[Length] = '\0';

    OLED_ShowString(Line, Column, s);
}

void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length)
{
    char s[13];
    uint8_t i;
    uint32_t n;

    if (Length > 10) Length = 10;

    if (Number < 0)
    {
        s[0] = '-';
        n = (uint32_t)(-Number);
        for (i = 0; i < Length; i++)
        {
            s[Length - i] = (char)('0' + n % 10);
            n /= 10;
        }
        s[Length + 1] = '\0';
    }
    else
    {
        n = (uint32_t)Number;
        for (i = 0; i < Length; i++)
        {
            s[Length - 1 - i] = (char)('0' + n % 10);
            n /= 10;
        }
        s[Length] = '\0';
    }

    OLED_ShowString(Line, Column, s);
}

void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    char s[12];
    uint8_t i;
    const char Hex[] = "0123456789ABCDEF";

    if (Length > 8) Length = 8;

    for (i = 0; i < Length; i++)
    {
        s[Length - 1 - i] = Hex[Number & 0x0F];
        Number >>= 4;
    }
    s[Length] = '\0';

    OLED_ShowString(Line, Column, s);
}

void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    char s[33];
    uint8_t i;

    if (Length > 32) Length = 32;

    for (i = 0; i < Length; i++)
    {
        s[Length - 1 - i] = (char)('0' + (Number & 0x01));
        Number >>= 1;
    }
    s[Length] = '\0';

    OLED_ShowString(Line, Column, s);
}

/*==================== 中文 16x16 ====================*/
/* Chinese 指向 32 字节字模：前 16 字节上半部分，后 16 字节下半部分 */
void OLED_ShowChinese(uint8_t Line, uint8_t Column, const uint8_t *Chinese)
{
    uint8_t i, Page, X;

    if (Line < 1 || Line > 4 || Column < 1 || Column > 8) return;

    Page = (uint8_t)((Line - 1) * 2);
    X    = (uint8_t)((Column - 1) * 16);

    for (i = 0; i < 16; i++)
    {
        OLED_GRAM[Page][X + i]     = Chinese[i];
        OLED_GRAM[Page + 1][X + i] = Chinese[i + 16];
    }
    OLED_Update();
}

/*==================== 绘图 ====================*/
void OLED_DrawPoint(uint8_t X, uint8_t Y)
{
    if (X > 127 || Y > 63) return;
    OLED_GRAM[Y / 8][X] |= (uint8_t)(1 << (Y % 8));
}

void OLED_DrawLine(uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2)
{
    int16_t dx = (X2 > X1) ? (int16_t)(X2 - X1) : (int16_t)(X1 - X2);
    int16_t dy = (Y2 > Y1) ? (int16_t)(Y2 - Y1) : (int16_t)(Y1 - Y2);
    int16_t sx = (X1 < X2) ? 1 : -1;
    int16_t sy = (Y1 < Y2) ? 1 : -1;
    int16_t err = dx - dy;
    int16_t x = X1, y = Y1;

    while (1)
    {
        OLED_DrawPoint((uint8_t)x, (uint8_t)y);
        if (x == X2 && y == Y2) break;

        {
            int16_t e2 = 2 * err;
            if (e2 > -dy) { err -= dy; x += sx; }
            if (e2 <  dx) { err += dx; y += sy; }
        }
    }
}

/* 图像按列存储：每列 (Height+7)/8 字节，低位在上 */
void OLED_ShowImage(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image)
{
    uint8_t x, y, page, bit, bytePerCol;

    bytePerCol = (uint8_t)((Height + 7) / 8);

    for (x = 0; x < Width; x++)
    {
        if ((uint16_t)X + x > 127) break;

        for (y = 0; y < Height; y++)
        {
            if ((uint16_t)Y + y > 63) break;

            page = (uint8_t)((Y + y) / 8);
            bit  = (uint8_t)((Y + y) % 8);

            if (Image[x * bytePerCol + y / 8] & (1 << (y % 8)))
                OLED_GRAM[page][X + x] |= (uint8_t)(1 << bit);
            else
                OLED_GRAM[page][X + x] &= (uint8_t)~(1 << bit);
        }
    }
}
