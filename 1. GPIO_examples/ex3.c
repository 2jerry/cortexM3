// 3. 스위치만 누르고 있는 동안은  꺼지고 조이스틱을누른 상태에서 스위치를 눌렀다가 떼면 2초동안 켜진다. default 는 블링크
#define FIO1DIR (*(volatile int *)0x2009C020)
#define FIO1SET (*(volatile int *)0x2009C038)
#define FIO1CLR (*(volatile int *)0x2009C03C)

#define FIO2DIR (*(volatile int *)0x2009C040)
#define FIO2SET (*(volatile int *)0x2009C058)
#define FIO2CLR (*(volatile int *)0x2009C05C)

#define FIO1PIN (*(volatile int *)0x2009C034) // joystic
#define FIO2PIN (*(volatile int *)0x2009C054) // 스위치

#define IO2IntEnR   (*(volatile int *)0x400280B0) // Enable for Rising edge.
#define IO2IntStatR (*(volatile int *)0x400280A4) // Status for Rising edge.
#define IO2IntClr   (*(volatile int *)0x400280AC) // Edge Clear.

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


// 1초가 12000000라고 가정했을때
int main(void)
{
	led_init();
	int flag = 0;
	
	// 스위치를 rising edge로 설정
	IO2IntClr |= 0x00000400; //(1<<10) edge clear
	IO2IntEnR |= 0x00000400; // rising edge 
	
	while(1)
	{
		led_blink();
		while((!(FIO2PIN & 0x00000400) && (FIO1PIN & joystic[4]))) // 스위치가 눌렸으면
		{
			led_all(OFF);
		}		
		if(!(FIO1PIN & joystic[4])) // 조이스틱이 눌린 상태에서
		{
			if(IO2IntStatR) // rising edge가 검출되면
			{
				led_all(ON);
				delay(2); // 2초동안 켠다
			}
		}
			IO2IntClr |= 0x00000400; //(1<<10) edge clear
	}
}

