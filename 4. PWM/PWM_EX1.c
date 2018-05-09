#include "gpio_jy.h"
#include "interrupt_jy.h"

#define PINSEL3 	(*(volatile unsigned int *)0x4002C00C)		// Pin ��� ����
	
#define PCONP			(*(volatile unsigned int *)0x400FC0C4)		// MCPWM ���� ����
#define PCLKSEL1	(*(volatile unsigned int *)0x400FC1AC)		// MCPWM Ŭ�� ����.

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
	
	// 0. GPIO ���ͷ�Ʈ ����
	IO0IntEnR |= POTENTIO;
	//IO0IntEnF |= POTENTIO;
	ISER0 |= (1<<21);	
	
	// 1. �ܼ� GPIO ����� �ƴ� MCPWM ��� ��� ����.
	PINSEL3 |= (1 << 24);		// MCOA2
	PINSEL3 |= (1 << 26);		// MCOB2
	
	//  2. MCPWM�� ����� �� �ֵ��� �ʱ�ȭ
	PCONP |= (1 << 17);				// MCPWM ����
	PCLKSEL1 |= (0x3 << 30);	// MC Ŭ��
	
	// 3. MCPWM �� ����.
	MCCON_CLR |= (1 << 17); 			// Edge ���
	MCCON_CLR |= (1 << 18); 			// Passive Low ���
	MCCON_CLR |= (1 << 3);	 			// ����Ÿ�� Disable
	MCCON_CLR |= (1 << 20); 			// �� Update Enable
	
	MCDT 	 |= (0x000 << 20);	// ����Ÿ�� �� 0
	MCTC2 	= 0;							// Timer/Counter ���� ��
	MCLIM2 	= PWMMAX;					// Timer/Counter �ִ� ��
	MCMAT2	= PWMVAL;					// ���� ��Ƽ��
		
	// 4. MCPWM ä��2 ����
	MCCON_SET |= (1 << 16);
	
	while(1);
}
