#include "stm32f10x.h"       // Device header
#include "PWM.h"
#include "delay.h"
#include "Key.h"


int main(void)
{
	uint16_t duty=0;
	int8_t a=1;
	uint16_t angle=0;
	int8_t b=1;
	PWM_Init();
	while (1)
	{
		duty+=a;
		if (duty>=100)
		{                                                
			a=-1; 
		}
		if (duty==0)
		{
			a=1; 
		}
		PWM_SetCompare1(duty*200);
		angle+=b;
		if(angle>=180) 
		{
			b=-1; 
		}
		if(angle==0)   
		{ 
			b=1; 
		}
		PWM_SetCompare2(500+angle*2000/180); 
		delay_ms(10);
	}
}