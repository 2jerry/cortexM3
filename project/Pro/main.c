#include "GPIO.h"
#include "fnd.h"
#include "timer.h"
#include "interrupt.h"
#include "led.h"

void TIMER0_IRQHandler(void);
void EINT0_IRQHandler(void);

unsigned char t1 = 1, t2 = 1, t3 = 1, t4= 1;
unsigned char tmp_t = 0, tmp_t10 = 0, tmp_m = 0, tmp_m10 = 0;


int main()
{
	led_Init();
	Init_FND();
	
  Init_ISR();
	Init_Timer();
	
	while(1)
	{
			
		display(8,t4);
		display(7,t3);
		display(6,t2);
		display(5,t1);
		
		display(4,tmp_t);
		display(3,tmp_t10);
		display(2,tmp_m);
		display(1,tmp_m10);
		
		if(t1 == t2 && t2 == t3 && t3 == t4)
		{
				tmp_t = t1;
				tmp_t10 = t2;
			  tmp_m = t1;
			  tmp_m10 = t1;
			
		}
	}
}

// Interrupt Reqzeust Timer 일치할 때 진입
void TIMER0_IRQHandler(void)
{
	T0IR |= 0; // interrupt flag clear
	T0TC = 0; // 카운트 값 clear

	t1 ++;
	if(t1 == 10)
		t1 = 1;
	
}
void TIMER1_IRQHandler(void)
{
	T1IR |= 0; // interrupt flag clear
	T1TC = 0; // 카운트 값 clear
	
	t2 ++;
	if(t2 == 10)
		t2 = 1;
	
}
void TIMER2_IRQHandler(void)
{
	T2IR |= 0; // interrupt flag clear
	T2TC = 0; // 카운트 값 clear
	
	t3 ++;
	if(t3 == 10)
		t3 = 1;
	
}
void TIMER3_IRQHandler(void)
{
	T3IR |= 0; // interrupt flag clear
	T3TC = 0; // 카운트 값 clear
	
	t4 ++;
	if(t4 == 10)
		t4 = 1;
	
}

void EINT0_IRQHandler(void)
{
	EXTINT |= (1<<0); // 0번 인터럽트 사용
		
	led_all(OFF);
	
	tmp_t = t4;
	tmp_t10 = t3;
	tmp_m = t2;
	tmp_m10 =t1;
	
	led_onoff(ON,tmp_m10);
	led_onoff(ON,tmp_m);
	led_onoff(ON,tmp_t10);
	led_onoff(ON,tmp_t);
	
	
}
