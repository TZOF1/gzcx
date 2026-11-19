#include "stm32f10x.h" // Device header
#include "Timer.h"
volatile uint16_t Num;
int main (void)
{
	Timer_Init();
	
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
		if(Num%2!=0)
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_0);
		}
		else
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_0);
		}
	  //GPIO_ResetBits(GPIOA,GPIO_Pin_0);
		//GPIO_WriteBit(GPIOA,GPIO_Pin_0,0);
		//GPIO_SetBits(GPIOA,GPIO_Pin_0);
		//GPIO_WriteBit(GPIOA,GPIO_Pin_0,1);

	}
}


