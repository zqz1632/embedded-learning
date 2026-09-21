#ifndef ALL_H
#define ALL_H
typedef struct
	{
		volatile unsigned int CRL;
		volatile unsigned int CRH;
		volatile unsigned int IDR;
		volatile unsigned int ODR;
		volatile unsigned int BSRR;
		volatile unsigned int BRR;
		volatile unsigned int LCKR;
	}GPIO_t;

typedef struct
	{
		volatile unsigned int CSR;
		volatile unsigned int RVR;
		volatile unsigned int CVR;
		volatile unsigned int CALIB;
	}SysTick_t;

#define RCC_BASE (0x40021000)
#define RCC_APB2ENR ((volatile unsigned int*)(RCC_BASE+0x18))
#define GPIOC ((GPIO_t *)0x40011000)
#define SysTick ((SysTick_t *)0xE000E010)
#define SYSTICK_CSR_ENABLE    (1u << 0)
#define SYSTICK_CSR_TICKINT   (1u << 1)
#define SYSTICK_CSR_CLKSOURCE   (1u << 2)//0：外部时钟1：内部时钟
#define SYSTICK_CSR_COUNTFLAG   (1u << 16)
#endif
