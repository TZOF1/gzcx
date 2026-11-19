#include "stm32f10x.h"       // Device header
#include "delay.h"
#include "Key.h"
#include "LED.h"

uint8_t KeyNum;
volatile uint16_t Num;

int main (void)
{
	Timer_Init();
	LED_Init();
	Key_Init();
	while(1)
	{
		KeyNum=Key_GetNum();
		if(KeyNum==1)
		{
			LED0_Turn();
		}
	}
}