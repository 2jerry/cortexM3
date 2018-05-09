// ���ѹα� ����
#include <stdlib.h>
#include <time.h>

#define FIO1DIR (*(volatile int *)0x2009C020)
#define FIO1SET (*(volatile int *)0x2009C038)
#define FIO1CLR (*(volatile int *)0x2009C03C)

#define FIO2DIR (*(volatile int *)0x2009C040)
#define FIO2SET (*(volatile int *)0x2009C058)
#define FIO2CLR (*(volatile int *)0x2009C05C)

#define FIO2PIN (*(volatile int *)0x2009C054) // ����ġ

#define ON 1
#define OFF 0

// LED 1~8��
int led[8] = { (1<<28), (1<<29), (1<<31), (1<<2), (1<<3), (1<<4), (1<<5),(1<<6) };
	
// led �ʱ�ȭ �Լ�
void led_init()
{
	FIO1DIR |= (led[0] | led[1] | led[2]); // led�� ���(ouput���� ����)
	//FIO1CLR |= (led[0] | led[1] | led[2]);
	
	FIO2DIR |= (led[3] | led[4] | led[5] | led[6] | led[7]);
	//FIO2CLR |= (led[3] | led[4] | led[5] | led[6] | led[7]);
}

// led ���� �Լ�
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
	
	int start[20];
	int end[20];
	int push = 0;
	int time_cnt = 0;
	int count = 0;
	
	int cnt = 0;
	int flag = 0;
	int flag2 = 0;
	
	while(1)
	{
		if(!(FIO2PIN & (1<<10))) // �Է��� �������� ����
		{
			delay(0.3); // ä�͸� ����
			push++; // ������ �ִ� �ð��� ����
			flag = 1;
		}
		if(flag) // �Է��� �ѹ� �������� �迭�� �����Ѵ�.
		{
			start[cnt] = push;
			cnt++; // ���� index ����
			flag = push = 0; 
		}
		else
		{
			delay(0.3);
			if(time_cnt > 50) // 10�� �� 1.5�� ����? 
			{
				//led_all(ON);
				for(int i = 0;i<cnt;i++)
				{
					led_all(ON);
					delay(start[i]);
					led_all(OFF);
					delay(0.5);
					
					start[i] = 0;
				}
				cnt = time_cnt = 0;
			}
			time_cnt++; // ������ �ʴ� �ð��� ī��Ʈ
		
		}
	}
}
/*
	if(flag) // �Է��� �ѹ� �������� �迭�� �����Ѵ�.
	{
		led_all(ON);
		delay(time1); // ���� �ð���ŭ delay
		led_all(OFF);
		flag = 0;
	}
*/













