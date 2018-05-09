// 2. 스위치 누르면 켜지고 조이스틱 누르면 꺼지고 동시에 누르면 블링크 동시에 누른거 두개다 떼면 꺼지기
#define FIO1DIR (*(volatile int *)0x2009C020)
#define FIO1SET (*(volatile int *)0x2009C038)
#define FIO1CLR (*(volatile int *)0x2009C03C)

#define FIO2DIR (*(volatile int *)0x2009C040)
#define FIO2SET (*(volatile int *)0x2009C058)
#define FIO2CLR (*(volatile int *)0x2009C05C)

#define FIO1PIN (*(volatile int *)0x2009C034) // joystic
#define FIO2PIN (*(volatile int *)0x2009C054) // 스위치

#define ON 1
#define OFF 0

// LED 1~8번
int led[8] = { (1<<28), (1<<29), (1<<31), (1<<2), (1<<3), (1<<4), (1<<5),(1<<6) };
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

void led_all(int value)
{
		for(int i = 0;i<8;i++)
		{
			led_onoff(value,i);
		}
}
void delay(double s)
{
	int i;
	int time = s*12000000;
	for(i = 0;i<time;i++);
}

void led_blink()
{
	led_all(ON);
	delay(0.5);
	led_all(OFF);
	delay(0.5);
}


int main(void)
{
	led_init();
/*
	while(1)
	{
		if(!(FIO2PIN & (1<<10))) // 스위치가 눌렸고
		{
			if(!(FIO1PIN & joystic[4])) // 조이스틱도 눌려있으면
				led_blink();
			else
				led_all(ON);
		}
		if(!(FIO1PIN & joystic[4]))
		{
			led_all(OFF);
		}
	}*/
	
	while(1)
	{
		if(!(FIO2PIN & (1<<10)) &&(!(FIO1PIN & joystic[4])))// 스위치가 눌렸고
		{
				led_blink();
		}
		if(!(FIO2PIN & (1<<10)))
		{
			led_all(ON);
		}
		if(!(FIO1PIN & joystic[4]))
		{
			led_all(OFF);
		}
	}
}

