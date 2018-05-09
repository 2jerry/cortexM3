#include "fnd.h"
#include "timer.h"
#include "interrupt.h"
#include "led.h"

void TIMER0_IRQHandler(void);
void EINT0_IRQHandler(void);

unsigned char t = 0, t10 = 0, m = 0, m10 = 0;
unsigned char tmp_t = 0, tmp_t10 = 0, tmp_m = 0, tmp_m10 = 0;


int main()
{
	led_Init();
	Init_FND();
	
  Init_ISR();
	Init_Timer();
	

	while(1)
	{
		display(8,t);
		display(7,t10);
		display(6,m);
		display(5,m10);
		
		display(4,tmp_t);
		display(3,tmp_t10);
		display(2,tmp_m);
		display(1,tmp_m10);
	}
	
}

// Interrupt Reqzeust Timer 일치할 때 진입
void TIMER0_IRQHandler(void)
{
	T0IR |= 0; // interrupt flag clear
	T0TC = 0; // 카운트 값 clear
	
	t++;
	if(t == 10)
	{
		t10++;
		t = 0;
	}
	if(t10 == 6) // 1분
	{
		m++;
		t10 = 0;
	}
	if(m == 10) // 1분
	{
		m10++;
		m = 0;
	}
	if(m10 == 6) // 1분
	{
		m = 0;
		m10 = 0;
		t = 0;
		t10 = 0;
	}
}

void EINT0_IRQHandler(void)
{
	EXTINT |= (1<<0); // 0번 인터럽트 사용
	led_onoff(ON,1);
	
	tmp_t = t;
	tmp_t10 = t10;
	tmp_m = m;
	tmp_m10 = m10;
	
}