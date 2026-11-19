#include "stm32f10x.h"                  // Device header

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_Inistructure;
	GPIO_Inistructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Inistructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_Inistructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_Inistructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
	//GPIO_ResetBits(GPIOC,GPIO_Pin_13);
	while (1)
	{
		
	}
}
