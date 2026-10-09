#ifndef ALL_H
#define ALL_H
/**
 * @file    all.h
 * @brief   寄存器映射定义：GPIO / SysTick 寄存器结构体、外设基地址、SysTick 控制位
 * @board   Blue Pill, STM32F103C8T6, 8MHz HSI
 * @note    本工程不使用 HAL/CMSIS，直接按寄存器地址操作硬件；
 *          结构体成员顺序与硬件寄存器偏移一一对应（相邻成员相差 4 字节），
 *          通过“基地址强制转为结构体指针”的方式访问寄存器。
 */

/*------------------------------- GPIO 寄存器 -------------------------------*/

/**
 * @brief   GPIO 端口寄存器组（共 7 个 32 位寄存器，各占 4 字节）
 * @note    CRL/CRH 中每个管脚占 4 位：MODE[1:0] 配置输入/输出方向及输出速度，
 *          CNF[1:0] 配置具体的输入/输出模式。
 */
typedef struct
	{
		volatile unsigned int CRL;  	/*!< 端口配置低寄存器：管脚 0~7，偏移 0x00 */
		volatile unsigned int CRH;  	/*!< 端口配置高寄存器：管脚 8~15，偏移 0x04 */
		volatile unsigned int IDR;  	/*!< 端口输入数据寄存器，偏移 0x08，只读 */
		volatile unsigned int ODR;  	/*!< 端口输出数据寄存器，偏移 0x0C */
		volatile unsigned int BSRR; 	/*!< 端口位设置/清除寄存器，偏移 0x10，只写；低 16 位置 1 置位 ODR，高 16 位置 1 复位 ODR，原子操作 */
		volatile unsigned int BRR;  	/*!< 端口位清除寄存器，偏移 0x14，只写 */
		volatile unsigned int LCKR; 	/*!< 端口配置锁定寄存器，偏移 0x18 */
	}GPIO_t;

/**
 * @brief   SysTick 寄存器组（Cortex-M3 内核私有外设，与芯片厂商无关）
 */
typedef struct
	{
		volatile unsigned int CSR;  	/*!< 控制及状态寄存器，偏移 0x00 */
		volatile unsigned int RVR;  	/*!< 重装载值寄存器，偏移 0x04 */
		volatile unsigned int CVR;  	/*!< 当前值寄存器，偏移 0x08，写任意值清零 */
		volatile unsigned int CALIB;	/*!< 校准值寄存器，偏移 0x0C */
	}SysTick_t;

/*------------------------------ 外设基地址定义 ------------------------------*/

#define RCC_BASE (0x40021000)		/*!< RCC（复位与时钟控制）寄存器组基地址 */
#define RCC_APB2ENR ((volatile unsigned int*)(RCC_BASE+0x18))	/*!< APB2 外设时钟使能寄存器，位 4 = GPIOC 时钟(IOPCEN) */
#define GPIOC ((GPIO_t *)0x40011000)	/*!< GPIOC 基地址，挂载在 APB2 总线上 */
#define SysTick ((SysTick_t *)0xE000E010)	/*!< SysTick 基地址，Cortex-M3 内核外设固定地址 */

/*---------------------------- SysTick 控制位定义 ----------------------------*/

#define SYSTICK_CSR_ENABLE    	(1u << 0)	/*!< 计数器使能位：1 = 启动 SysTick 计数 */
#define SYSTICK_CSR_TICKINT   	(1u << 1)	/*!< 异常请求使能位：1 = 计数到 0 时产生 SysTick 异常 */
#define SYSTICK_CSR_CLKSOURCE 	(1u << 2)	/*!< 时钟源选择位：0 = 外部时钟(内核时钟/8)，1 = 内部时钟(内核时钟) */
#define SYSTICK_CSR_COUNTFLAG 	(1u << 16)	/*!< 计满标志位：计数到 0 时置 1，读 CSR 自动清零 */
#endif
