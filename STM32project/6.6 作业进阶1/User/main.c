#include "stm32f10x.h"       // Device header
#include "Key.h"
#include "delay.h"
#include "PWM.h"
#include "Timer.h"

uint16_t i=0;
uint16_t Compare=0;
uint16_t Key=0;
int main (void)
{
	Key_Init();
	Timer_Init();
	PWM_Init();
	while(1)
	{
		if(Key==1)
		{
			Compare=Compare+25;
			if(Compare>100)
			{
				Compare=0;
			}
			PWM_SetComparel (Compare);
			Key=0;
		}
		if(Key==2)
		{
			Key=0;
			uint16_t run=1;
			while(run)
			{                                                                                                                                                                                                                 
				for (i=0;i<=100&&run;i++)
				{
					PWM_SetComparel (i);
					delay_ms(10);
					if(Key == 2) { Key = 0; run = 0; }
				}
				for (i=0;i<=100&&run;i++)
				{
					PWM_SetComparel (100-i);
					delay_ms(10);                                        
					if(Key == 2) { Key = 0; run = 0; }
				}
			}
			PWM_SetComparel (0);
			Key=0;
		}
	}
}