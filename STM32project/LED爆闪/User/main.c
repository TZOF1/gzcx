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
		if(KeyNum==2)
		{
			while(1)
			{
				if(Num%2!=0)
				{
					GPIO_ResetBits(GPIOA,GPIO_Pin_0);
				}
				else
				{
					GPIO_SetBits(GPIOA,GPIO_Pin_0);
				}
				KeyNum=Key_GetNum();
				if(KeyNum==2)
				{
					GPIO_SetBits(GPIOA,GPIO_Pin_0);
					break;
				}
			}
			while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0);
		}
	}
}