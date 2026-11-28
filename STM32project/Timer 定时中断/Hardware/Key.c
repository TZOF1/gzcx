#include "stm32f10x.h"                  // Device header
#include "delay.h"

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitSructure;
	GPIO_InitSructure.GPIO_Mode= GPIO_Mode_IPU;
	GPIO_InitSructure.GPIO_Pin= GPIO_Pin_0;
	GPIO_InitSructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitSructure);
}
uint8_t Key_GetNum(void)
{
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0);
}


