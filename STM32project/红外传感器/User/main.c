#include "stm32f10x.h"       // Device header
#include "delay.h"
#include "OLED.h"
#include "CountSenser.h"

int main (void)
{
	OLED_Init();
	CountSenser_Init();
	OLED_ShowString(1,1,"Count:");
	while(1)
	{
		OLED_ShowNum(1,7,CountSenser_Get(),5);
	}
}