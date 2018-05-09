#include "gpio.h"

void ISR_init()
{
	PINSEL4 |= (1<<20); // ����ġ GPIO ��� -> interrupt ������� Ȱ��ȭ 
	ISER0 |= (1<<18);   // ���ͷ�Ʈ set
	
	EXTMODE |= (1<<0); // 0�� ���ͷ�Ʈ ���� ��� ���
	EXTPOLAR |= (1<<0); // rising edge
//	EXTPOLAR |= (0<<0); // falling edge
}

void timer_init(void)
{	 
	PCONP |= (1<<1); // timer0 setting
	PCLKSEL0 |= (1<<2)+(1<<3); //  
	ISER0 |= (1<<1);
	//T0TC = 0; // count start value
	T0TCR |= 0x00000001;
	T0MR0 = 12000000*10;  // 1�� �� (= 12000000 = 12MHZ) ����
	T0MCR |= 0x00000001; //
	//T0IR |= 0x00000001; 
}

void timer_stop(void)
{	 
	PCONP |= (0<<1); // timer0 setting
	PCLKSEL0 |= (0<<2)+(0<<3); //  
	ISER0 |= (0<<0);
	//T0TC = 0; // count start value
	T0TCR |= 0x00000000;
	T0MR0 = 0;  // 1�� �� (= 12000000 = 12MHZ) ����
	T0MCR |= 0x00000000; //
	//T0IR |= 0x00000001; 
}

