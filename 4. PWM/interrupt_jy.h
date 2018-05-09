#define PINSEL4 	(*(volatile unsigned int *)0x4002C010)		// Pin 기능 설정
	
#define EXTINT 		(*(volatile unsigned int *)0x400FC140)
#define EXTMODE 	(*(volatile unsigned int *)0x400FC148)
#define EXTPOLAR	(*(volatile unsigned int *)0x400FC14C)
	
#define ISER0			(*(volatile unsigned int *)0xE000E100)
#define ISPR0			(*(volatile unsigned int *)0xE000E200)
#define ICPR0			(*(volatile unsigned int *)0xE000E280)
	
void EXTI_Init()
{
	EXTINT = 0x0;
	EXTMODE = 0x0;
	EXTPOLAR = 0x0;
}
