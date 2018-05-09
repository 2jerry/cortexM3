// 5. 스위치를 누르고 있을때 조이스틱을 오른쪽으로 누르면 led 8개가 오른쪽으로 켜지게 왼쪽 누르면 왼쪽으로 켜지게
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
	int cnt = 0;
	
	while(1)
	{
		if(!(FIO2PIN & (1<<10))) // 스위치를 누르고 있을때
		{
			if(!(FIO1PIN & joystic[3])) // 조이스틱 왼쪽
			{
				delay(0.3); // 조이스틱 채터링 방지
				cnt++;
			}
			if(!(FIO1PIN & joystic[2])) // 조이스틱 오른쪽
			{
				delay(0.3); // 조이스틱 채터링 방지
				cnt--;
			}
			led_onoff(ON,cnt%8);
			delay(0.5);
			led_onoff(OFF,cnt%8);
			led_all(OFF);
		}
	}

	
}
















