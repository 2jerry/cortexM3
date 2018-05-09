#include "gpio_jy.h"
#include "interrupt_jy.h"

#define PINSEL3 	(*(volatile unsigned int *)0x4002C00C)		// Pin 기능 설정
	
#define PCONP			(*(volatile unsigned int *)0x400FC0C4)		// MCPWM 전원 설정
#define PCLKSEL1	(*(volatile unsigned int *)0x400FC1AC)		// MCPWM 클럭 설정.

#define MCCON					(*(volatile unsigned int *)0x400B8000)
#define MCCON_SET			(*(volatile unsigned int *)0x400B8004)
#define MCCON_CLR			(*(volatile unsigned int *)0x400B8008)
#define MCTC2					(*(volatile unsigned int *)0x400B8020)
#define MCLIM2				(*(volatile unsigned int *)0x400B802C)
#define MCCNTCON			(*(volatile unsigned int *)0x400B805C)
#define MCCNTCON_SET	(*(volatile unsigned int *)0x400B8060)
#define MCCNTCON_CLR	(*(volatile unsigned int *)0x400B8064)
#define MCMAT2				(*(volatile unsigned int *)0x400B8038)
#define MCDT					(*(volatile unsigned int *)0x400B803C)

int PWMVAL = 100;
int PWMMAX = 300;

void EINT3_IRQHandler()
{
	IO0IntClr |= POTENTIO;
	
	if(IO0IntStatR & POTENTIO)
	{
		MCMAT2 = PWMVAL;
		PWMVAL+=10;
		LED_C(7, ON, 0);
	}
	else if(IO0IntStatF & POTENTIO)
	{
		MCMAT2 = PWMVAL;
		PWMVAL-=10;
		LED_C(7, OFF, 0);
	}
}

int main()
{	
	LED_Init();
	
	// 0. GPIO 인터럽트 설정
	IO0IntEnR |= POTENTIO;
	//IO0IntEnF |= POTENTIO;
	ISER0 |= (1<<21);	
	
	// 1. 단순 GPIO 기능이 아닌 MCPWM 기능 사용 설정.
	PINSEL3 |= (1 << 24);		// MCOA2
	PINSEL3 |= (1 << 26);		// MCOB2
	
	//  2. MCPWM을 사용할 수 있도록 초기화
	PCONP |= (1 << 17);				// MCPWM 전원
	PCLKSEL1 |= (0x3 << 30);	// MC 클럭
	
	// 3. MCPWM 값 설정.
	MCCON_CLR |= (1 << 17); 			// Edge 모드
	MCCON_CLR |= (1 << 18); 			// Passive Low 모드
	MCCON_CLR |= (1 << 3);	 			// 데드타임 Disable
	MCCON_CLR |= (1 << 20); 			// 값 Update Enable
	
	MCDT 	 |= (0x000 << 20);	// 데드타임 값 0
	MCTC2 	= 0;							// Timer/Counter 시작 값
	MCLIM2 	= PWMMAX;					// Timer/Counter 최대 값
	MCMAT2	= PWMVAL;					// 현재 듀티비
		
	// 4. MCPWM 채널2 시작
	MCCON_SET |= (1 << 16);
	
	while(1);
}
