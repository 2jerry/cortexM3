//  1. 두개를 동시에 누르고 있다가 스위치를 떼면 led블링크 두개다 떼어진 상태에서 스위치 누르면 꺼지기
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
	int flag = 0;
	while(1)
	{
		if(!(FIO1PIN & joystic[4])) // joystic 이 눌렸을경우
		{
			if(!(FIO2PIN & (1<<10))) // 스위치도 눌렸으면
			{	flag = 1;	} // 둘다 눌렸음을 표시 
			
			if((flag == 1) && (FIO2PIN & (1<<10)))
			{
				flag = 0;
				while(1)
				{
					led_blink();
					if(!(FIO2PIN & (1<<10))) { led_all(OFF); break;	}
				}
				
		}
	}

	}
}

