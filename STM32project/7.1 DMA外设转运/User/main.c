#include "stm32f10x.h"       // Device header
#include "delay.h"
#include "OLED.h"
#include "MyDMA.h"
#include "AD.h"

int main (void)
{
	OLED_Init();
	AD_Init();
	while(1)
	{
		AD_GetValue();
		OLED_ShowNum(1,1,ADValue[0],4);
		OLED_ShowNum(2,1,ADValue[1],4);
	}
}