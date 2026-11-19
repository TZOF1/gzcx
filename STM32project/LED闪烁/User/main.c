#include "stm32f10x.h"       // Device header
#include "delay.h"

int main (void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitSructure;
	GPIO_InitSructure.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_InitSructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitSructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitSructure);
	//GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	//GPIO_SetBits(GPIOA,GPIO_Pin_0);
	//GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
	while(1)
	{
	  //GPIO_ResetBits(GPIOA,GPIO_Pin_0);
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,0);
		delay_ms(250);
		//GPIO_SetBits(GPIOA,GPIO_Pin_0);
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,1);
		delay_ms(250);
	}
}