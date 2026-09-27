/*
 * all_c
 *
 *  Created on: 2026年9月27日
 *      Author: 16326
 */

#ifndef ALL_H
#define ALL_H

extern const unsigned int g_PWM_Steps;
extern volatile unsigned int g_Duty_Cycle;
extern volatile unsigned int g_PWM_Circle_Flag;
extern const unsigned char g_Brightness_Table[100];
typedef struct
{
	volatile unsigned int CSR;//控制及状态寄存器
	volatile unsigned int RVR;//重装载数值寄存器
	volatile unsigned int CVR;//当前数值寄存器
	volatile unsigned int CALIB;//校准数值寄存器
}SysTick_t;
#define SysTick_CSR_COUNTFLAG (1u<<16)
#define SysTick_CSR_CLKSOURCE (1u<<2)
#define SysTick_CSR_TICKINT (1u<<1)
#define SysTick_CSR_ENABLE (1u<<0)
#define SysTick ((SysTick_t *)0xE000E010)
#define SYS_CLK_FREQ (8)
typedef struct
{
	volatile unsigned int CR;//时钟控制寄存器
	volatile unsigned int CFGR;//时钟配置寄存器
	volatile unsigned int CIR;//时钟中断寄存器
	volatile unsigned int APB2RSTR;//APB2 外设复位寄存器
	volatile unsigned int APB1RSTR;//APB1 外设复位寄存器
	volatile unsigned int AHBENR;//AHB外设时钟使能寄存器
	volatile unsigned int APB2ENR;//APB2 外设时钟使能寄存器
	volatile unsigned int APB1ENR;//APB1 外设时钟使能寄存器
	volatile unsigned int BDCR;//备份域控制寄存器
	volatile unsigned int CSR;//控制/状态寄存器
}RCC_t;
#define RCC ((RCC_t *)0x40021000)
#define RCC_APB2ENR_IOPCEN (1u<<4)//1使能0关闭
typedef struct
{
	volatile unsigned int CRL;//端口配置低寄存器
	volatile unsigned int CRH;//端口配置高寄存器
	volatile unsigned int IDR;//端口输入数据寄存器
	volatile unsigned int ODR;//端口输出数据寄存器
	volatile unsigned int BSRR;//端口位设置/清除寄存器
	volatile unsigned int BRR;//端口位清除寄存器
	volatile unsigned int LCKR;//端口配置锁定寄存器
}GPIO_t;
#define GPIOC ((GPIO_t *)0x40011000)//参考手册P115
#define GPIOC_CRH_P13_INIT (~(0xFu<<20))//P13清空
#define GPIOC_CRH_P13_CONFIG (2u<<20)//P13配置为通用推挽输出模式，最大速度2MHz
#define GPIOC_BSRR_P13_LED_OFF (1u<<13)
#define GPIOC_BSRR_P13_LED_ON (1u<<29)
#endif /* ALL_C_ */
