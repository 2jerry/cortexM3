// FIODIR : fast GPIO �� ���� ���� �������� output or input
// In general fast GPIO is about 2.5 times faster and also has a mask register.

#define FIO1DIR (*(volatile int *)0x2009C020)
#define FIO1SET (*(volatile int *)0x2009C038)
#define FIO1CLR (*(volatile int *)0x2009C03C)

#define FIO2DIR (*(volatile int *)0x2009C040)
#define FIO2SET (*(volatile int *)0x2009C058)
#define FIO2CLR (*(volatile int *)0x2009C05C)

#define FIO2PIN (*(volatile int *)0x2009C054)

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


int main(void)
{
	
	led_init();
	 
    // led 0~8�� �����Ǹ鼭 ������ �ڵ�
	while(1)
	{
		for(int i = 0;i<8;i++)
		{
			led_onoff(ON,i);
			for(int i = 0;i<12000000;i++);
		}
		for(int i = 8;i>=0;i--)
		{
			led_onoff(OFF,i);
			for(int i = 0;i<12000000;i++);
		}
	}
	
	
	/*
    //	����ġ�� ������ led ������ �ڵ� 
	while(1)
	{
		if(!(FIO2PIN & 0x00000400))  // �Է°��� ��������
			led_onoff(ON,1); 
		else
			led_onoff(OFF,1);
	}
	*/
		
	
	
	
}

  




