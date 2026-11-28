#include "stm32f10x.h"       // Device header
#include "delay.h"
#include "Key.h"
#include "OLED.h"
#include "Motor.h"

uint16_t KeyNum;
int16_t Speed;
int main (void)
{
	Motor_Init();
	Key_Init();
	OLED_Init();
	Motor_SetSpeed(0);
	Key_Init();
	while(1)
	{
		KeyNum=Key_GetNum();
		if(KeyNum==1)
		{
			Speed=Speed+20;
			if(Speed>100)
			{
				Speed=-100;
			}
		}
		Motor_SetSpeed(Speed);
		OLED_ShowSignedNum(1,1,Speed,3);
	}
}