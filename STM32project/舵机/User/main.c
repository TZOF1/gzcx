#include "stm32f10x.h"       // Device header
#include "Servo.h"
#include "delay.h"
#include "Key.h"
#include "OLED.h"

uint16_t KeyNum;
float Angle;
int main (void)
{
	OLED_Init();
	Key_Init();
	Servo_Init();
	Servo_SetAngle(90);
	while(1)
	{
		KeyNum=Key_GetNum();
		if(KeyNum==1)
		{
			Angle=Angle+30;
			if(Angle>180)
			{
				Angle=0;
			}
		}
		Servo_SetAngle(Angle);
		OLED_ShowNum(1,1,Angle,3);
	}
}