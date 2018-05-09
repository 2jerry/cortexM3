#define FIO0SET  (*(volatile int *)0x2009C018)
#define FIO1SET  (*(volatile int *)0x2009C038)
#define FIO2SET  (*(volatile int *)0x2009C058)

#define FIO0CLR  (*(volatile int *)0x2009C01C)
#define FIO1CLR  (*(volatile int *)0x2009C03C)
#define FIO2CLR  (*(volatile int *)0x2009C05C)

#define FIO0DIR   (*(volatile int *)0x2009C000)
#define FIO1DIR   (*(volatile int *)0x2009C020)
#define FIO2DIR   (*(volatile int *)0x2009C040)
#define FIO3DIR   (*(volatile int *)0x2009C060)

#define FIO0PIN   (*(volatile int *)0x2009C014) // DIR input
#define FIO1PIN   (*(volatile int *)0x2009C034) // DIR input
#define FIO2PIN   (*(volatile int *)0x2009C054) // DIR input
#define FIO3PIN   (*(volatile int *)0x2009C074)
	

void EXT_IO_A_Init()
{
	FIO0CLR |= (1<<19); // 확장보드 A 활성화
	FIO0SET |= (1<<20);
	FIO0SET |= (1<<21);
	
	FIO0DIR |= (1<<4) | (1<<5) | (1<<10) | (1<<11) |  (1<<19) |(1<<23) | (1<<24);
	FIO1DIR |= (1<<21);
	FIO2DIR |= (1<<11) | (1<<12) | (1<<13);
	FIO3DIR |= (1<<25) | (1<<26);	
}

void Motor_set(int n)
{
	for(int i = 0;i<2;i++)
	{
		FIO0SET |= (1<<5);
		FIO0CLR |= (1<<10);
		FIO0SET |= (1<<23);
		FIO0CLR |= (1<<24);
		for(int i = 0;i<100000;i++); // delay
		
		FIO0CLR |= (1<<5);
		FIO0SET |= (1<<10);
		FIO0SET |= (1<<23);
		FIO0CLR |= (1<<24);
		for(int i = 0;i<100000;i++); // delay
		
		FIO0CLR |= (1<<5);
		FIO0SET |= (1<<10);
		FIO0CLR |= (1<<23);
		FIO0SET |= (1<<24);
		for(int i = 0;i<100000;i++); // delay
		
		FIO0SET |= (1<<5);
		FIO0CLR |= (1<<10);
		FIO0CLR |= (1<<23);
		FIO0SET |= (1<<24);
		for(int i = 0;i<100000;i++); // delay
	}
}

int main()
{
		EXT_IO_A_Init();
		while(1)
		{
				Motor_set(1);
			  for(int i = 0;i<12000000;i++); // delay
		}
	
}