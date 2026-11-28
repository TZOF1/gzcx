#include "stm32f10x.h" 
#include "Key.h"
uint16_t Num=0;
extern uint16_t Key;
void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM3, ENABLE) ;
	TIM_InternalClockConfig (TIM3);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 10 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit (TIM3, &TIM_TimeBaseInitStructure);
	TIM_ITConfig (TIM3, TIM_IT_Update, ENABLE) ;
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init (&NVIC_InitStructure);
	TIM_Cmd(TIM3, ENABLE);
}
void TIM3_IRQHandler (void)
{
	if (TIM_GetITStatus (TIM3, TIM_IT_Update) == SET)
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
		TIM_ClearITPendingBit (TIM3, TIM_IT_Update);
	}
}

//void TIM2_IRQHandler (void)
//{
//	if (TIM_GetITStatus (TIM2, TIM_IT_Update) == SET)
//	{
//		Num++;
//		TIM_ClearITPendingBit (TIM2, TIM_IT_Update);
//	}
//}
