#include "stm32f10x.h"                  // Device header
#include "delay.h"

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitSructure;
	GPIO_InitSructure.GPIO_Mode= GPIO_Mode_IPU;
	GPIO_InitSructure.GPIO_Pin= GPIO_Pin_1|GPIO_Pin_11;
	GPIO_InitSructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitSructure);
}
uint8_t Key_GetNum(void)
{
	uint8_t KeyNum=0;
	//Num=0;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
	{
		delay_ms(20);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
		{
			while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0){}
			delay_ms(20);
			delay_ms(20);
			uint16_t t=0;
			while(t<500)
			{
				if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
				{
					delay_ms(20);
					if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
					{
						while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0){}
						delay_ms(20);
						KeyNum=1;
						break;
					}
				}
				delay_ms(10);
				t=t+10;
			}
		}
	}
	return KeyNum;
}


