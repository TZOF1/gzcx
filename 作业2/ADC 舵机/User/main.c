#include "stm32f10x.h"       // Device header
#include "delay.h"
#include "OLED.h"
#include "AD.h"
#include "PWM.h"

float ADValue;
float Angle=0;
int main (void)
{
	PWM_Init();
	AD_Init();
	while(1)
	{
		ADValue=AD_GetValue();
		Angle=ADValue*1.0/4095*180;
		PWM_SetCompare2 (500+(int)(Angle/180*2000));
	}
}