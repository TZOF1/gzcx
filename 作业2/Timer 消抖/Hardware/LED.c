#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Key.h"
uint16_t Num=0;
extern uint16_t A;
extern uint16_t Key;
void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1);
}
void LED0_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
}
void LED0_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
}
void LED0_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_0)==0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	}
}
void LED1_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}
void LED1_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
}
void LED1_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1)==0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	}
}
void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM2, ENABLE) ;
	TIM_InternalClockConfig (TIM2);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 10 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit (TIM2, &TIM_TimeBaseInitStructure);
	TIM_ITConfig (TIM2, TIM_IT_Update, ENABLE) ;
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init (&NVIC_InitStructure);
	TIM_Cmd(TIM2, ENABLE);
}
void TIM2_IRQHandler (void)
{
	A++;
	if (TIM_GetITStatus (TIM2, TIM_IT_Update) == SET)
	{
		if(Key_GetNum()==0)
		{
			Num=Num+1;
		}
		else 
		{
			if(Num>=1000)
			{
				Key=2;
				Num=0;
			}
			else if(Num>=20)
			{
				Key=1;
				Num=0;
			}
			else
			{
				Num=0;
			}
		}
		TIM_ClearITPendingBit (TIM2, TIM_IT_Update);
	}
}


