#define FIO0DIR   (*(volatile int *)0x2009C000)
#define FIO1DIR   (*(volatile int *)0x2009C020)
#define FIO2DIR   (*(volatile int *)0x2009C040)
#define FIO3DIR   (*(volatile int *)0x2009C060)

#define FIO0PIN   (*(volatile int *)0x2009C014) // DIR input
#define FIO1PIN   (*(volatile int *)0x2009C034) // DIR input
#define FIO2PIN   (*(volatile int *)0x2009C054) // DIR input
#define FIO3PIN   (*(volatile int *)0x2009C074)

#define PINSEL7   (*(volatile int *)0x4002C01C) // PWM AF 11

#define PCLKSEL0  (*(volatile int *)0x400FC1A8)
#define PCONP	    (*(volatile int *)0x400FC0C4) // PWM power
#define PWM1IR	  (*(volatile int *)0x40018000) // PWM interrupt	
#define PWM1TCR	  (*(volatile int *)0x40018004) // PWM Timer/Counter
#define PWM1PR    (*(volatile int *)0x4001800C)	// PWM prescale   
#define PWM1MCR	  (*(volatile int *)0x40018014) // PWM Match Control 
#define PWM1CCR	  (*(volatile int *)0x40018028)	// PWM Capture Control
#define PWM1PCR	  (*(volatile int *)0x4001804C) // PWM Control
#define PWM1LER	  (*(volatile int *)0x40018050) // Load Enable
#define PWM1MR0   (*(volatile int *)0x40018018)
#define PWM1MR2   (*(volatile int *)0x40018020)

#define ISER0    (*(volatile int *)0xE000E100) // 9

void Motor_Init1()
{
	FIO0DIR |= (1<<4) | (1<<19); // 확장보드 A 활성화
	
	FIO0DIR |= (1<<5) | (1<<10) | (1<<11) | (1<<23) | (1<<24);
	FIO1DIR |= (1<<21);
	FIO2DIR |= (1<<11) | (1<<12) | (1<<13);
	FIO3DIR |= (1<<25) | (1<<26);	
}

void PWM_Init1()
{
	//PCLKSEL0 |= (1<<12) | (1<<13);
	PINSEL7 |= (1<<18) | (1<<19); // PWM 1.2
	PWM1PR = (72000000/4) / 1000000; // 1 us (Microsecond) Prescale 설정	
	
	PCONP |= (1<<6);
	
	PWM1MR0 = 20000;
	PWM1LER |= 0x01;
	PWM1TCR |= (1<<1); // PWM Counter Reset
	PWM1TCR &= (~(1<<1)) & (0x0000000B);
	
	PWM1MCR |= (1<<0) | (1<<1); // interrupt , reset enable
	PWM1MCR &= ~(1<<2); // stop disable
	
	/* --- channel 2 setting ---*/
	PWM1PCR &= ~(1<<2); // PWM Timer 2 Channel single edge mode
	PWM1MCR &= ~((1<<6) | (1<<7) | (1<<8));
	
	ISER0 |= (1<<9); //PWM interrupt set enable
	
	PWM1PCR |= (1<<10);
	PWM1TCR |= (1 << 1);		
	PWM1TCR &= (0 << 0);
	PWM1TCR |= (1 << 0); // PWM counter enable
	
}

int cnt = 0;
int main()
{
	int angle1,angle2;
	
	Motor_Init1();
	PWM_Init1();
	angle1 = 0;
	angle2 = 180;
	
	
	while(1)
	{
		if(cnt == 100)
		{
			PWM1MR2 = 600+(10*angle1); // 600usec 은 -90도
			PWM1LER |= (1<<2);
		}
		else if(cnt == 200)
		{
			PWM1MR2 = 2400+(10*angle2);
			PWM1LER |= (1<<2);
		}
	}
	
}

void PWM1_IRQHandler(void)
{
	if (PWM1IR & (1<<0))	
	{
		if(cnt == 300)
		{
			cnt = 0;
		}
		cnt++;
		PWM1IR = (1 << 0);		// Interrupt 정보를 클리어 하여 다시 대기 상태로 바꾼다.
	}
}







