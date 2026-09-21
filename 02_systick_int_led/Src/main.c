/**
 * @file    main.c
 * @brief   SysTick以及GPIOC的初始化
 * @board   Blue Pill, STM32F103C8T6, 8MHz HSI
 * @note    写CVR清计数器并从RVR重载
 * 			RVR减1：数到0也算一拍
 */
#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "all.h"

/**
 * @brief    SysTick以及GPIOC的初始化
 * @param    void
 * @return   void
 * @note     写CVR清计数器并从RVR重载
 * 			 RVR减1：数到0也算一拍
 */
int main(void)
{
	*RCC_APB2ENR |=1u<<4;//时钟使能GPIOC
	GPIOC->CRH &=~(0xFu<<20);//GPIOC端口13配置清空
	GPIOC->CRH |=1u<<21;//GPIOC端口13配置为推挽输出2MHZ
	SysTick->RVR=4000000-1;/* 8MHz下500ms的计数；减1：数到0也算一拍 */
	SysTick->CVR=0;//初始化清零。写读自动清零并从RVR自动重载
	(void)(SysTick->CSR & SYSTICK_CSR_COUNTFLAG);
	SysTick->CSR|=SYSTICK_CSR_TICKINT | SYSTICK_CSR_CLKSOURCE | SYSTICK_CSR_ENABLE;

	while(1)
	{

	}

}
