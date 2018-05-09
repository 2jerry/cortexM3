// FIODIR : fast GPIO 의 방향 설정 레지스터 output or input
// In general fast GPIO is about 2.5 times faster and also has a mask register.

#define FIO1DIR (*(volatile int *)0x2009C020)
#define FIO1SET (*(volatile int *)0x2009C038)
#define FIO1CLR (*(volatile int *)0x2009C03C)

#define FIO2DIR (*(volatile int *)0x2009C040)
#define FIO2SET (*(volatile int *)0x2009C058)
#define FIO2CLR (*(volatile int *)0x2009C05C)

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

void led_all(int value)
{
	if(value) // ON
	{
		FIO1SET |= led[0];
		FIO1SET |= led[1];
		FIO1SET |= led[2];
		for(int i = 3;i<8;i++)
		{
			FIO1SET |= led[i];
		}
	}		
	else // OFF
	{
		FIO1CLR |= led[0];
		FIO1CLR |= led[1];
		FIO1CLR |= led[2];
		for(int i = 3;i<8;i++)
		{
			FIO2CLR |= led[i];
		}
	}
}

int main(void)
{
	led_init();
	while(1)
	{
		if(!(FIO1PIN & joystic[0]))
			led_onoff(ON,0);
		else if(!(FIO1PIN & joystic[1]))
			led_onoff(ON,1);
		else if(!(FIO1PIN & joystic[2]))
			led_onoff(ON,2);
		else if(!(FIO1PIN & joystic[3]))
			led_onoff(ON,3);
		else if(!(FIO1PIN & joystic[4]))
			led_onoff(ON,4);
		else
			led_all(OFF);

	}
	
}

  




