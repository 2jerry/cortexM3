// 5. ����ġ�� ������ ������ ���̽�ƽ�� ���������� ������ led 8���� ���������� ������ ���� ������ �������� ������
#include <stdlib.h>
#include <time.h>

#define FIO1DIR (*(volatile int *)0x2009C020)
#define FIO1SET (*(volatile int *)0x2009C038)
#define FIO1CLR (*(volatile int *)0x2009C03C)

#define FIO2DIR (*(volatile int *)0x2009C040)
#define FIO2SET (*(volatile int *)0x2009C058)
#define FIO2CLR (*(volatile int *)0x2009C05C)

#define FIO2PIN (*(volatile int *)0x2009C054) // ����ġ
#define FIO1PIN (*(volatile int *)0x2009C034) // joystic

#define ON 1
#define OFF 0

// LED 1~8��
int led[8] = { (1<<28), (1<<29), (1<<31), (1<<2), (1<<3), (1<<4), (1<<5),(1<<6) };

// joystic
int joystic[5] = {(1<<24), (1<<26), (1<<23), (1<<25), (1<<20) }; // �� �� �� �� ����
	
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
		if(!(FIO2PIN & (1<<10))) // ����ġ�� ������ ������
		{
			if(!(FIO1PIN & joystic[3])) // ���̽�ƽ ����
			{
				delay(0.3); // ���̽�ƽ ä�͸� ����
				cnt++;
			}
			if(!(FIO1PIN & joystic[2])) // ���̽�ƽ ������
			{
				delay(0.3); // ���̽�ƽ ä�͸� ����
				cnt--;
			}
			led_onoff(ON,cnt%8);
			delay(0.5);
			led_onoff(OFF,cnt%8);
			led_all(OFF);
		}
	}

	
}
















