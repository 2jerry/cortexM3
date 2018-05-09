#include "GPIO.h"

void TIMER0_IRQHandler(void);
void TIMER1_IRQHandler(void);
void TIMER2_IRQHandler(void);
void TIMER3_IRQHandler(void);


void Init_Timer(void)
{	 
	PCONP |= (1<<1) + (1<<2) + (1<<22) + (1<<23); // timer0 setting
	PCLKSEL0 |= (2<<2)+(2<<4)+(2<<12)+(2<<14); //  
	ISER0 |= (1<<1) + (1<<2) + (1<<3) + (1<<4);
	//T0TC = 0; // count start value
	/*---Timer 0------------*/
	T0TCR |= 0x00000001;
	T0MR0 = 12000000;  // 1초 값 (= 12000000 = 12MHZ) 설정
	T0MCR |= 0x00000001; //
	//T0IR |= 0x00000001; 
	
	/*---Timer 1------------*/
	T1TCR |= 0x00000001;
	T1MR0 = 2200000*3;  // 1초 값 (= 12000000 = 12MHZ) 설정
	T1MCR |= 0x00000001; //
	
	/*---Timer 2------------*/
	T2TCR |= 0x00000001;
	T2MR0 = 1300000*3;  // 1초 값 (= 12000000 = 12MHZ) 설정
	T2MCR |= 0x00000001; //
	
	/*---Timer 3------------*/
	T3TCR |= 0x00000001;
	T3MR0 = 3200000*4;  // 1초 값 (= 12000000 = 12MHZ) 설정
	T3MCR |= 0x00000001; //
}

