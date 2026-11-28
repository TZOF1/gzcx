#include "stm32f10x.h"       // Device header
#include "PWM.h"
#include "delay.h"

uint16_t i;
int main (void)
{
	PWM_Init();
	while(1)
	{
		for (i=0;i<=100;i++)
		{
			PWM_SetComparel (i);
			delay_ms(10);
		}
		for (i=0;i<=100;i++)
		{
			PWM_SetComparel (100-i);
			delay_ms(10);
		}
	}
}