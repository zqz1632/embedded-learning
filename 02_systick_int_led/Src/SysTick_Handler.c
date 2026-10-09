/**
 * @file    SysTick_Handler.c
 * @brief   SysTick 中断服务程序：翻转 LED（PC13）
 * @board   Blue Pill, STM32F103C8T6, 8MHz HSI
 * @note    1. 标志位的清零：读 CSR 自动清除 COUNTFLAG；
 *          2. 向量表明确函数名为 SysTick_Handler，不可更改；
 *          3. ISR 要短，只清标志和翻转，禁止延时等阻塞操作。
 */
#include "all.h"

/**
 * @brief    SysTick 中断服务函数：每 500ms 翻转一次 PC13 上的 LED
 * @param    void
 * @return   void
 * @note     标志位的清零。
 			向量表明确函数名为 SysTick_Handler 不可更改
 			ISR 要短，只清标志和翻转，禁止延时等阻塞操作
 * @warning  Blue Pill 板载 LED 为低电平点亮（PC13 输出 0 亮、1 灭）。
 */
void SysTick_Handler(void)
{
	(void)(SysTick->CSR & SYSTICK_CSR_COUNTFLAG);//读 CSR 清除 COUNTFLAG(位16)，不清会反复触发
	if(GPIOC->ODR & 1u<<13)//读取 ODR 位13，判断 PC13 当前输出电平
	{
		GPIOC->BSRR =0x20000000;//BSRR 高 16 位写 1：复位 ODR 位13，PC13 输出低电平，点亮 LED
	}
	else
	{
		GPIOC->BSRR =0x00002000;//BSRR 低 16 位写 1：置位 ODR 位13，PC13 输出高电平，熄灭 LED
	}
}
