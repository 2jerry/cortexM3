#include "gpio_jy.h"
#include "interrupt_jy.h"

#define PINSEL4 	(*(volatile unsigned int *)0x4002C010)		// Pin 기능 설정

#define PCONP			(*(volatile unsigned int *)0x400FC0C4)		// PWM1 전원 설정
#define PCLKSEL0	(*(volatile unsigned int *)0x400FC1A8)		// PWM1 클럭 설정
	
#define PWM1IR		(*(volatile unsigned int *)0x40018000)		
#define PWM1TCR		(*(volatile unsigned int *)0x40018004)		
#define PWM1TC		(*(volatile unsigned int *)0x40018008)		
#define PWM1PR		(*(volatile unsigned int *)0x4001800C)		
#define PWM1PC		(*(volatile unsigned int *)0x40018010)		
#define PWM1MCR		(*(volatile unsigned int *)0x40018014)
#define PWM1MR0   (*(volatile unsigned int *)0x40018018)
#define PWM1MR3   (*(volatile unsigned int *)0x40018024)
#define PWM1CCR		(*(volatile unsigned int *)0x40018028)		
#define PWM1PCR		(*(volatile unsigned int *)0x4001804C)
#define PWM1MR4   (*(volatile unsigned int *)0x40018040)
#define PWM1MR5   (*(volatile unsigned int *)0x40018044)
#define PWM1MR6   (*(volatile unsigned int *)0x40018048)
#define PWM1LER		(*(volatile unsigned int *)0x40018050)		
#define PWM1CTCR	(*(volatile unsigned int *)0x40018070)		


/* MAIN */
int main()
{	
	LED_Init();
	
	// 1. 타이머 사용을 위한 Prescale(1us) 값 설정.
	PCLKSEL0 |= (0x3 << 12);
	PWM1PR = (72000000/8) / 1000000;
	
	// 2. PWM1을 사용할 수 있도록 초기화(전원 설정, 레지스터 초기화)
	PCONP |= (1 << 6);		// 초기 값이 1이라 생략 가능
	
	PWM1IR = 0x0000073F;	// Write 1이 인터럽트 초기화
	PWM1TCR = 0x00;
	PWM1MCR = 0x00;
	PWM1CCR = 0x00;
	PWM1PCR = 0x00;
	PWM1LER = 0x00;
	PWM1CTCR = 0x00;
	
	// 3. 채널 당 match 값 설정.
	PWM1MR3 = 10000;			// match  값
	PWM1LER |= (1 << 3);	// 타이머가 리셋되고 난 후 새로운 매치 값 사용
	PWM1TCR |= (1 << 1);	// TC와 PC 리셋
	
	PWM1MR4 = 20000;		
	PWM1LER |= (1 << 4);
	PWM1TCR |= (1 << 1);
	
	PWM1MR5 = 30000;		
	PWM1LER |= (1 << 5);
	PWM1TCR |= (1 << 1);
	
	PWM1MR6 = 40000;		
	PWM1LER |= (1 << 6);
	PWM1TCR |= (1 << 1);
	
	// 4. 채널 3, 4, 5, 6 match 값에 도달하면 어떻게 할 지 설정.
	// 인터럽트 발생. (6채널 인터럽트 발생과 동시에 카운터 리셋)
	PWM1MCR |= (1 << 9)|(1 << 12)|(1 << 15)|(1 << 18)|(1 << 19);
	
	
	// 5. IRQ PWM 인터럽트 Enable
	ISER0 |= (1 << 9);
	
	// 6. 카운터 초기화 & 시작
	PWM1TCR |= (1 << 1);		// TC와 PC 리셋
	PWM1TCR &= (0 << 0);
	PWM1TCR |= (1 << 0);		// TC와 PC Enable
	
	while(1){}
}

// IRQ 함수 작성
void PWM1_IRQHandler()
{
	if(PWM1IR & (1 << 3))
	{
		LED_C(0, BLK, SEC1);
		PWM1IR = (1 << 3);	// 인터럽트 초기화
	}
	if(PWM1IR & (1 << 8))
	{
		LED_C(1, BLK, SEC1);
		PWM1IR = (1 << 8);
	}
	if(PWM1IR & (1 << 9))
	{
		LED_C(2, BLK, SEC1);
		PWM1IR = (1 << 9);
	}
	if(PWM1IR & (1 << 10))
	{
		LED_C(3, BLK, SEC1);
		PWM1IR = (1 << 10);
	}
}
