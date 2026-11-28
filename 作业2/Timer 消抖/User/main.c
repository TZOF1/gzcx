#include "stm32f10x.h"       // Device header
#include "delay.h"
#include "LED.h"
#include "Key.h"

uint16_t Key=0;
uint16_t A=0;
int main (void)
{
	Key_Init();
	LED_Init();
	Timer_Init();
	while(1)
	{
		if(Key==1)
		{
			Key=0;
			LED0_Turn();
		}
		if(Key==2)
		{
			Key=0;
			A=0;
			while(1)
			{
				if(A==100)
				{
					A=0;
					LED0_Turn();
				}
				if(Key==2)
				{
				break;
				}
			}
			GPIO_SetBits(GPIOA,GPIO_Pin_0);
			Key=0;
		}
	}
}