#include "stm32f10x.h"       // Device header
#include "OLED.h"
#include "delay.h"
#include "PWM.h"
#include "Timer.h"
#include "BianMa.h"


int main (void)
{
	BianMa_Init();
	OLED_Init();
	OLED_ShowString(1,1,"CNT:00000");
	while(1)
	{
		OLED_ShowSignedNum(1,5,BianMa_Get(),5);
		delay_ms(1000);
	}
}