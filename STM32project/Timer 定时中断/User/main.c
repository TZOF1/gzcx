#include "stm32f10x.h"       // Device header
#include "delay.h"
#include "OLED.h"
#include "Key.h"
#include "Timer.h"
uint16_t Num=0;

int main (void)
{
	Timer_Init();
	OLED_Init();
	while(1)
	{
		OLED_ShowNum(1,1,Num,5);
	}
}