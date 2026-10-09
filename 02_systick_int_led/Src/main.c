/**
 * @file    main.c
 * @brief   主程序：初始化 GPIOC（PC13 推挽输出）与 SysTick（500ms 定时中断），主循环为空
 * @board   Blue Pill, STM32F103C8T6, 8MHz HSI
 * @note    1. 写 CVR 清计数器，计数器自动从 RVR 重载；
 *          2. RVR 要减 1：数到 0 也算一拍（重装值 N 实际计 N+1 拍）。
 */
#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "all.h"

/**
 * @brief    SysTick 以及 GPIOC 的初始化
 * @param    void
 * @return   void
 * @note     写 CVR 清计数器并从 RVR 重载；
 * 			 RVR 减 1：数到 0 也算一拍。
 */
int main(void)
{
	*RCC_APB2ENR |=1u<<4;//RCC_APB2ENR 位4(IOPCEN)：使能 GPIOC 外设时钟，时钟不开 IO 口不响应
	GPIOC->CRH &=~(0xFu<<20);//PC13 配置位在 CRH 的 [23:20]，先清零 MODE13/CNF13，避免旧配置干扰
	GPIOC->CRH |=1u<<21;//MODE13=01：输出模式、最大速度 2MHz；CNF13=00：通用推挽输出
	SysTick->RVR=4000000-1;/* 时钟源选内核时钟(8MHz)，500ms 需计 4000000 拍；减1：数到0也算一拍 */
	SysTick->CVR=0;//写当前值寄存器清零，写后自动从 RVR 重载
	(void)(SysTick->CSR & SYSTICK_CSR_COUNTFLAG);//读 CSR 清除 COUNTFLAG(位16)，防止残留标志导致误进中断
	SysTick->CSR|=SYSTICK_CSR_TICKINT | SYSTICK_CSR_CLKSOURCE | SYSTICK_CSR_ENABLE;//使能SysTick异常+选内核时钟+启动计数

	while(1)
	{

	}

}
