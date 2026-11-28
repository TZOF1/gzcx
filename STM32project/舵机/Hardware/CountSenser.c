#include "stm32f10x.h"   // Device header
#include "delay.h"
uint16_t CountSenser_Count;
void CountSenser_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_14;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line=EXTI_Line14;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_Structure;
	NVIC_Structure.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_Structure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Structure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Structure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_Structure);
}
uint16_t CountSenser_Get(void)
{
	return CountSenser_Count;
}
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line14)==SET)
	{
		CountSenser_Count++;
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}

