/**
 * @file    SysTick_Handler.c
 * @brief   LED的翻转.软件实现PWM
 * @board   Blue Pill, STM32F103C8T6, 8MHz HSI
 * @note    标志位的清零
 			向量表明确函数名为SysTick_Handler不可更改
 			ISR要短，只清标志和翻转，禁止延时等阻塞操作
 */
 #include "all.h"
 
 static unsigned int g_PWM_cnt=0;//计数标志
 volatile unsigned int g_PWM_Circle_Flag=0;
 void SysTick_Handler(void)
 {
 	if(SysTick->CSR & SysTick_CSR_COUNTFLAG)
 	{
 		if(++g_PWM_cnt >= g_PWM_Steps) 
 		{
 			g_PWM_cnt=0;
 			g_PWM_Circle_Flag=1;
 			
 		}
 		if(g_PWM_cnt < g_Duty_Cycle)
 		{
 			GPIOC->BSRR = GPIOC_BSRR_P13_LED_ON;
 		}
 		else
 		{
 			GPIOC->BSRR = GPIOC_BSRR_P13_LED_OFF;
 		}
 	}
 }