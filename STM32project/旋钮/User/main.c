#include "stm32f10x.h"       // Device header
#include "delay.h"
#include "OLED.h"
#include "CountSenser.h"
#include "Encoder.h"

int16_t Num;
int main (void)
{
	Encoder_Init();
	OLED_Init();
	OLED_ShowString(1,1,"Num:");
	while(1)
	{
		Num=Num+Encoder_Get();
		OLED_ShowSignedNum(1,6,Num,5);
	}
}