#include "gpio_jy.h"

#define PINSEL4 	(*(volatile unsigned int *)0x4002C010)		// Pin ��� ����

#define PCONP			(*(volatile unsigned int *)0x400FC0C4)		// PWM1 ���� ����
#define PCLKSEL0	(*(volatile unsigned int *)0x400FC1A8)		// PWM1 Ŭ�� ����
	
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
	
	// 1. ���� �ܼ� GPIO�� �ƴ� PWM���� ����ϱ� ���� ��� ����.
	PINSEL4 |= (1 << 4);
	PINSEL4 |= (1 << 6);
	PINSEL4 |= (1 << 8);
	PINSEL4 |= (1 << 10);
	
	// 2. Ÿ�̸� ����� ���� Prescale(1us) �� ����.
	PCLKSEL0 |= (0x3 << 12);
	PWM1PR = (72000000/8) / 1000000;
	
	// 3. PWM1�� ����� �� �ֵ��� �ʱ�ȭ(���� ����, �������� �ʱ�ȭ)
	PCONP |= (1 << 6);		// �ʱ� ���� 1�̶� ���� ����
	
	PWM1IR = 0x0000073F;	// Write 1�� ���ͷ�Ʈ �ʱ�ȭ
	PWM1TCR = 0x00;
	PWM1MCR = 0x00;
	PWM1CCR = 0x00;
	PWM1PCR = 0x00;
	PWM1LER = 0x00;
	PWM1CTCR = 0x00;
	
	// 4. ��Ƽ�� ������ ���� match�� ����.
	// ä�� 0 ���� (MR, LER, TCR)
	PWM1MR0 = 500;					// ��ġ ��: 500
	PWM1LER |= (1 << 0);		// Ÿ�̸Ӱ� ���µǰ� �� �� ���ο� ��ġ �� ���
	PWM1TCR |= (1 << 1);		// TC�� PC ����
	
	// 5. ä�� 0�� match ���� �����ϸ� ��� ���� ����.
	PWM1MCR |= (1 << 1);		// TC ����
	
	// 6. ä�� 3, 4, 5, 6 PWM ���� ��� ����
	PWM1PCR &= ~0x000000F0;	// Single Edge ����
	
	// 7. ä�� 3, 4, 5, 6 PWM match �� ����
	PWM1MR3 = 50;					// ��ġ ��: 50
	PWM1LER |= (1 << 3);	// Ÿ�̸Ӱ� ���µǰ� �� �� ���ο� ��ġ �� ���
	PWM1TCR |= (1 << 1);	// TC�� PC ����
	
	PWM1MR4 = 150;				// ��ġ ��: 150
	PWM1LER |= (1 << 4);	// Ÿ�̸Ӱ� ���µǰ� �� �� ���ο� ��ġ �� ��� 
	PWM1TCR |= (1 << 1);	// TC�� PC ����
	
	PWM1MR5 = 250;				// ��ġ ��: 250
	PWM1LER |= (1 << 5);	// Ÿ�̸Ӱ� ���µǰ� �� �� ���ο� ��ġ �� ���
	PWM1TCR |= (1 << 1);	// TC�� PC ����
	
	PWM1MR6 = 400;				// ��ġ ��: 400
	PWM1LER |= (1 << 6);	// Ÿ�̸Ӱ� ���µǰ� �� �� ���ο� ��ġ �� ���
	PWM1TCR |= (1 << 1);	// TC�� PC ����
	
	// 8. ä�� 3, 4, 5, 6 match ���� �����ϸ� ��� ���� ����.
	// �ƹ��͵� ���� �ʴ´�. ���� Disable.
	PWM1MCR &= ~(0xFFF << 9);
	
	// 9. ä�� 3, 4, 5, 6 ��� Ȱ��ȭ
	PWM1PCR |= (0xF << 11);
	
	// 10. ī���� �ʱ�ȭ
	PWM1TCR |= (1 << 1);		// TC�� PC ����
	PWM1TCR &= (0 << 0);		// ī���͸� ���½�Ű�� �ڵ����� ī���Ͱ� Enable�ǳ�? �� �� �� ���� �� �ʿ����� �𸣰ڴ�.
	
	// 11. ī���� ����
	PWM1TCR |= (1 << 0);		// TC�� PC Enable
	 
	while(1){}
}
