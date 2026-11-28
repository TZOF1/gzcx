#include "stm32f10x.h"       // Device header
#include "delay.h"
#include "OLED.h"
#include "MyDMA.h"

uint8_t DataA[]={0x01,0x02,0x03,0x04};
uint8_t DataB[]={0,0,0,0};
int main (void)
{
	OLED_Init();
	OLED_ShowHexNum(1,1,DataA[0],2);
	OLED_ShowHexNum(1,4,DataA[1],2);
	OLED_ShowHexNum(1,7,DataA[2],2);
	OLED_ShowHexNum(1,10,DataA[3],2);
	OLED_ShowHexNum(2,1,DataB[0],2);
	OLED_ShowHexNum(2,4,DataB[1],2);
	OLED_ShowHexNum(2,7,DataB[2],2);
	OLED_ShowHexNum(2,10,DataB[3],2);
	MyDMA_Init((uint32_t)DataA,(uint32_t)DataB,4);
	while(1)
	{
		OLED_ShowHexNum(3,1,DataA[0],2);
		OLED_ShowHexNum(3,4,DataA[1],2);
		OLED_ShowHexNum(3,7,DataA[2],2);
		OLED_ShowHexNum(3,10,DataA[3],2);
		OLED_ShowHexNum(4,1,DataB[0],2);
		OLED_ShowHexNum(4,4,DataB[1],2);
		OLED_ShowHexNum(4,7,DataB[2],2);
		OLED_ShowHexNum(4,10,DataB[3],2);
		delay_ms(1000);
		DataA[0]++;
		DataA[1]++;
		DataA[2]++;
		DataA[3]++;
		MyDMA_Transfer();
		OLED_ShowHexNum(4,1,DataB[0],2);
		OLED_ShowHexNum(4,4,DataB[1],2);
		OLED_ShowHexNum(4,7,DataB[2],2);
		OLED_ShowHexNum(4,10,DataB[3],2);
		delay_ms(1000);
	}
}