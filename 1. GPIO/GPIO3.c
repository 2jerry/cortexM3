// FIODIR : fast GPIO 의 방향 설정 레지스터 output or input
// In general fast GPIO is about 2.5 times faster and also has a mask register.
// 뗐을때가 라이징
#define FIO1DIR (*(volatile int *)0x2009C020)
#define FIO1SET (*(volatile int *)0x2009C038)
#define FIO1CLR (*(volatile int *)0x2009C03C)

#define FIO2DIR (*(volatile int *)0x2009C040)
#define FIO2SET (*(volatile int *)0x2009C058)
#define FIO2CLR (*(volatile int *)0x2009C05C)

#define FIO2PIN 	(*(volatile int *)0x2009C054)

#define IO2IntEnR   (*(volatile int *)0x400280B0) // Enable for Rising edge.
#define IO2IntEnF   (*(volatile int *)0x400280B4) // Enable for Failling edge.
#define IO2IntStatR (*(volatile int *)0x400280A4) // Status for Rising edge.
#define IO2IntStatF (*(volatile int *)0x400280A8) // Status for Failling edge.
#define IO2IntClr   (*(volatile int *)0x400280AC) // Edge Clear.

#define FIO0MASK    (*(volatile int *)0x2009C010) 

#define ON 1
#define OFF 0

// LED 1~8번
int led[8] = { (1<<28), (1<<29), (1<<31), (1<<2), (1<<3), (1<<4), (1<<5),(1<<6) };

// led 초기화 함수
void led_init()
{
	FIO1DIR |= (led[0] | led[1] | led[2]); // led를 출력(ouput으로 설정)
	//FIO1CLR |= (led[0] | led[1] | led[2]);
	
	FIO2DIR |= (led[3] | led[4] | led[5] | led[6] | led[7]);
	//FIO2CLR |= (led[3] | led[4] | led[5] | led[6] | led[7]);
}

// led 제어 함수
void led_onoff(int value,int num)
{
	if(value) // ON
	{
		if(num>2)
			FIO2SET |= led[num];
		else
			FIO1SET |= led[num];
	}		
	else // OFF
	{
		if(num>2)
			FIO2CLR |= led[num];
		else
			FIO1CLR |= led[num];
	}
}

int main(void)
{
	led_init();
	//int flag = 1;
	
	IO2IntClr |= 0x00000400; //(1<<10) edge clear
	IO2IntEnR |= 0x00000400; // rising edge 
	//IO2IntEnF |= 0x00000400; // rising edge
	
	while(1)
	{
		if(IO2IntStatR)
		{
			 led_onoff(ON,0);
			 for(int i = 0;i<5000000;i++);
			 IO2IntClr |= 0x00000400;	
		}
		else
		{
			 led_onoff(OFF,0);
		}

	}
	

	/*
	while(1)
	{
		if(!(FIO2PIN & (1<<10)))
		{	
			led_onoff(ON,0);
			led_onoff(OFF,0);
		}
		else
			led_onoff(ON,7);
	}
	*/

}

  




