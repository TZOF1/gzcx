#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f10x.h"

void Timer_Init(void);
/* 上电以来经过的毫秒数（由 TIM2 每 1ms 中断累加） */
extern volatile uint32_t Timer_Ms;

void Timer_Init(void);                  /* 初始化 TIM2，产生 1ms 中断 */
uint32_t Timer_GetMs(void);             /* 读取当前毫秒计数 */
void Timer_DelayMs(uint32_t ms);        /* 毫秒级延时（不占用 CPU 空转判断） */

/* 用户钩子：每 1ms 被调用一次，需要做周期任务时改这个函数即可 */
void Timer_1ms_Callback(void);

#endif
