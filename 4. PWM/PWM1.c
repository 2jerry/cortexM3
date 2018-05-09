#include "gpio_jy.h"

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
	
	// 1. 핀을 단순 GPIO가 아닌 PWM으로 사용하기 위해 기능 변경.
	PINSEL4 |= (1 << 4);
	PINSEL4 |= (1 << 6);
	PINSEL4 |= (1 << 8);
	PINSEL4 |= (1 << 10);
	
	// 2. 타이머 사용을 위한 Prescale(1us) 값 설정.
	PCLKSEL0 |= (0x3 << 12);
	PWM1PR = (72000000/8) / 1000000;
	
	// 3. PWM1을 사용할 수 있도록 초기화(전원 설정, 레지스터 초기화)
	PCONP |= (1 << 6);		// 초기 값이 1이라 생략 가능
	
	PWM1IR = 0x0000073F;	// Write 1이 인터럽트 초기화
	PWM1TCR = 0x00;
	PWM1MCR = 0x00;
	PWM1CCR = 0x00;
	PWM1PCR = 0x00;
	PWM1LER = 0x00;
	PWM1CTCR = 0x00;
	
	// 4. 듀티비 설정을 위한 match값 설정.
	// 채널 0 설정 (MR, LER, TCR)
	PWM1MR0 = 500;					// 매치 값: 500
	PWM1LER |= (1 << 0);		// 타이머가 리셋되고 난 후 새로운 매치 값 사용
	PWM1TCR |= (1 << 1);		// TC와 PC 리셋
	
	// 5. 채널 0가 match 값에 도달하면 어떻게 할지 설정.
	PWM1MCR |= (1 << 1);		// TC 리셋
	
	// 6. 채널 3, 4, 5, 6 PWM 엣지 모드 설정
	PWM1PCR &= ~0x000000F0;	// Single Edge 설정
	
	// 7. 채널 3, 4, 5, 6 PWM match 값 설정
	PWM1MR3 = 50;					// 매치 값: 50
	PWM1LER |= (1 << 3);	// 타이머가 리셋되고 난 후 새로운 매치 값 사용
	PWM1TCR |= (1 << 1);	// TC와 PC 리셋
	
	PWM1MR4 = 150;				// 매치 값: 150
	PWM1LER |= (1 << 4);	// 타이머가 리셋되고 난 후 새로운 매치 값 사용 
	PWM1TCR |= (1 << 1);	// TC와 PC 리셋
	
	PWM1MR5 = 250;				// 매치 값: 250
	PWM1LER |= (1 << 5);	// 타이머가 리셋되고 난 후 새로운 매치 값 사용
	PWM1TCR |= (1 << 1);	// TC와 PC 리셋
	
	PWM1MR6 = 400;				// 매치 값: 400
	PWM1LER |= (1 << 6);	// 타이머가 리셋되고 난 후 새로운 매치 값 사용
	PWM1TCR |= (1 << 1);	// TC와 PC 리셋
	
	// 8. 채널 3, 4, 5, 6 match 값에 도달하면 어떻게 할지 설정.
	// 아무것도 하지 않는다. 전부 Disable.
	PWM1MCR &= ~(0xFFF << 9);
	
	// 9. 채널 3, 4, 5, 6 출력 활성화
	PWM1PCR |= (0xF << 11);
	
	// 10. 카운터 초기화
	PWM1TCR |= (1 << 1);		// TC와 PC 리셋
	PWM1TCR &= (0 << 0);		// 카운터를 리셋시키면 자동으로 카운터가 Enable되나? 왜 이 한 줄이 꼭 필요한지 모르겠다.
	
	// 11. 카운터 시작
	PWM1TCR |= (1 << 0);		// TC와 PC Enable
	 
	while(1){}
}
