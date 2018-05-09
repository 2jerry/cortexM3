#include "gpio_jy.h"
#include "interrupt_jy.h"

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
	
	// 1. Ÿ�̸� ����� ���� Prescale(1us) �� ����.
	PCLKSEL0 |= (0x3 << 12);
	PWM1PR = (72000000/8) / 1000000;
	
	// 2. PWM1�� ����� �� �ֵ��� �ʱ�ȭ(���� ����, �������� �ʱ�ȭ)
	PCONP |= (1 << 6);		// �ʱ� ���� 1�̶� ���� ����
	
	PWM1IR = 0x0000073F;	// Write 1�� ���ͷ�Ʈ �ʱ�ȭ
	PWM1TCR = 0x00;
	PWM1MCR = 0x00;
	PWM1CCR = 0x00;
	PWM1PCR = 0x00;
	PWM1LER = 0x00;
	PWM1CTCR = 0x00;
	
	// 3. ä�� �� match �� ����.
	PWM1MR3 = 10000;			// match  ��
	PWM1LER |= (1 << 3);	// Ÿ�̸Ӱ� ���µǰ� �� �� ���ο� ��ġ �� ���
	PWM1TCR |= (1 << 1);	// TC�� PC ����
	
	PWM1MR4 = 20000;		
	PWM1LER |= (1 << 4);
	PWM1TCR |= (1 << 1);
	
	PWM1MR5 = 30000;		
	PWM1LER |= (1 << 5);
	PWM1TCR |= (1 << 1);
	
	PWM1MR6 = 40000;		
	PWM1LER |= (1 << 6);
	PWM1TCR |= (1 << 1);
	
	// 4. ä�� 3, 4, 5, 6 match ���� �����ϸ� ��� �� �� ����.
	// ���ͷ�Ʈ �߻�. (6ä�� ���ͷ�Ʈ �߻��� ���ÿ� ī���� ����)
	PWM1MCR |= (1 << 9)|(1 << 12)|(1 << 15)|(1 << 18)|(1 << 19);
	
	
	// 5. IRQ PWM ���ͷ�Ʈ Enable
	ISER0 |= (1 << 9);
	
	// 6. ī���� �ʱ�ȭ & ����
	PWM1TCR |= (1 << 1);		// TC�� PC ����
	PWM1TCR &= (0 << 0);
	PWM1TCR |= (1 << 0);		// TC�� PC Enable
	
	while(1){}
}

// IRQ �Լ� �ۼ�
void PWM1_IRQHandler()
{
	if(PWM1IR & (1 << 3))
	{
		LED_C(0, BLK, SEC1);
		PWM1IR = (1 << 3);	// ���ͷ�Ʈ �ʱ�ȭ
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
