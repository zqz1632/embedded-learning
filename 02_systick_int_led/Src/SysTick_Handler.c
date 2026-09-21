/**
 * @file    SysTick_Handler.c
 * @brief   LED的翻转
 * @board   Blue Pill, STM32F103C8T6, 8MHz HSI
 * @note    标志位的清零
 			向量表明确函数名为SysTick_Handler不可更改
 			ISR要短，只清标志和翻转，禁止延时等阻塞操作
 */
#include "all.h"

/**
 * @brief    中断后LED的翻转
 * @param    void
 * @return   void
 * @note     标志位的清零。
 			向量表明确函数名为SysTick_Handler不可更改
 			ISR要短，只清标志和翻转，禁止延时等阻塞操作
 */
void SysTick_Handler(void)
{
	(void)(SysTick->CSR & SYSTICK_CSR_COUNTFLAG);
	if(GPIOC->ODR & 1u<<13)
	{
		GPIOC->BSRR =0x20000000;
	}
	else
	{
		GPIOC->BSRR =0x00002000;
	}
}