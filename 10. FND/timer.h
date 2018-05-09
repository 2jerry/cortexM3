/* Register Define ------------*/
#define FIO1DIR (*(volatile int *)0x2009C020)
#define FIO1SET (*(volatile int *)0x2009C038)
#define FIO1CLR (*(volatile int *)0x2009C03C)

#define FIO2DIR (*(volatile int *)0x2009C040)
#define FIO2SET (*(volatile int *)0x2009C058)
#define FIO2CLR (*(volatile int *)0x2009C05C)

#define PCLKSEL0 (*(volatile int *)0x400FC1A8) // Peripheral clock (Timer 0,1)
#define PCONP    (*(volatile int *)0x400FC0C4) // power register
#define ISER0    (*(volatile int *)0xE000E100) //
#define T0IR     (*(volatile int *)0x40004000) // interrupt register
#define T0TC     (*(volatile int *)0x40004008) // timer counter register
#define T0TCR    (*(volatile int *)0x40004004) // timer control register
#define T0MR0    (*(volatile int *)0x40004018) // match register
#define T0MCR    (*(volatile int *)0x40004014) // match control register

#define FIO2PIN (*(volatile int *)0x2009C054) // 스위치


void TIMER0_IRQHandler(void);
void Init_Timer(void)
{	 
	PCONP |= (1<<1); // timer0 setting
	PCLKSEL0 |= (1<<2)+(1<<3); //  
	ISER0 |= (1<<1);
	//T0TC = 0; // count start value
	T0TCR |= 0x00000001;
	T0MR0 = 12000000;  // 1초 값 (= 12000000 = 12MHZ) 설정
	T0MCR |= 0x00000001; //
	//T0IR |= 0x00000001; 
}

