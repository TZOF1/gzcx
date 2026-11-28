#include "stm32f10x.h"       // Device header
#include "delay.h"
#include "OLED.h"
#include "AD.h"

uint16_t ADValue;
float Voltage;
int main (void)
{
	AD_Init();
	OLED_Init();
	OLED_ShowString(1,1,"AD:");
	OLED_ShowString(2,1,"V:");
	while(1)
	{
		ADValue=AD_GetValue();
		OLED_ShowNum(1,4,ADValue,4);
		Voltage=(float)ADValue/4095*3.3;
		OLED_ShowNum(2,3,Voltage,1);
		OLED_ShowString(2,4,".");
		OLED_ShowNum(2,5,(uint16_t)(Voltage*100)%100,2);
		delay_ms(100);
	}
}