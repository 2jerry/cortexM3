// 4. 조이스틱을 랜덤하게 여러번 누르고 스위치를 눌렀다 뗏을때 조이스틱이 눌렸던 led가 한꺼번에 켜지게
#include <stdlib.h>
#include <time.h>

#define FIO1DIR (*(volatile int *)0x2009C020)
#define FIO1SET (*(volatile int *)0x2009C038)
#define FIO1CLR (*(volatile int *)0x2009C03C)

#define FIO2DIR (*(volatile int *)0x2009C040)
#define FIO2SET (*(volatile int *)0x2009C058)
#define FIO2CLR (*(volatile int *)0x2009C05C)

#define FIO2PIN (*(volatile int *)0x2009C054) // 스위치
#define FIO1PIN (*(volatile int *)0x2009C034) // joystic

#define IO2IntEnR   (*(volatile int *)0x400280B0) // Enable for Rising edge.
#define IO2IntStatR (*(volatile int *)0x400280A4) // Status for Rising edge.
#define IO2IntClr   (*(volatile int *)0x400280AC) // Edge Clear.

#define ON 1
#define OFF 0

// LED 1~8번
int led[8] = { (1<<28), (1<<29), (1<<31), (1<<2), (1<<3), (1<<4), (1<<5),(1<<6) };

// joystic
int joystic[5] = {(1<<24), (1<<26), (1<<23), (1<<25), (1<<20) }; // 상 하 좌 우 선택
	
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

void delay(double s)
{
	int i;
	int time = s*12000000;
	for(i = 0;i<time;i++);
}

int main(void)
{
	led_init();
	int *array;
	int cnt = 0 , idx = -1, flag = 0;
	
	// 스위치를 rising edge로 설정
	IO2IntClr |= 0x00000400; //(1<<10) edge clear
	IO2IntEnR |= 0x00000400; // rising edge 
	
	while(1)
	{
		if(!(FIO1PIN & joystic[0]))		  { delay(0.3); flag = 1; idx = 0; }
		else if(!(FIO1PIN & joystic[1]))  { delay(0.3); flag = 1; idx = 1; }
		else if(!(FIO1PIN & joystic[2]))  { delay(0.3); flag = 1; idx = 2; }
		else if(!(FIO1PIN & joystic[3]))  { delay(0.3); flag = 1; idx = 3; }
		else if(!(FIO1PIN & joystic[4]))  { delay(0.3); flag = 1; idx = 4; }

		if((idx > -1) && flag == 1) 
		{ 
			led_onoff(ON,idx); delay(0.2); led_onoff(OFF,idx);
			array[cnt] = idx;
			cnt++; flag = 0;
		}
		if(IO2IntStatR)
		{
			IO2IntClr |= (1<<10);
			for(int i = 0;i<cnt; i++)
			{
				led_onoff(ON,array[i]);
				delay(1);
				led_onoff(OFF,array[i]);
				delay(1);
				array[i] = 0;
			}
			cnt = 0;
			idx = -1;
		}
	
	}

	
}















