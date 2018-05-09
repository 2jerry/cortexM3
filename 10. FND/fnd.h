#define FIO0DIR (*(volatile int *)0x2009C000)
#define FIO1DIR (*(volatile int *)0x2009C020)
#define FIO2DIR (*(volatile int *)0x2009C040)
#define FIO3DIR (*(volatile int *)0x2009C060)
	
#define FIO0CLR (*(volatile int *)0x2009C01C)
#define FIO1CLR (*(volatile int *)0x2009C03C)
#define FIO2CLR (*(volatile int *)0x2009C05C)
#define FIO3CLR (*(volatile int *)0x2009C07C)

#define FIO0SET (*(volatile int *)0x2009C018)
#define FIO1SET (*(volatile int *)0x2009C038)
#define FIO2SET (*(volatile int *)0x2009C058)
#define FIO3SET (*(volatile int *)0x2009C078)
	
void Init_FND()
{
	FIO0SET |= (1<<19); // 확장보드 PORT 2번 사용
	FIO0CLR |= (1<<20); // 확장보드 PORT 2번 사용
	FIO0SET |= (1<<21); // 확장보드 PORT 2번 사용
	// 확장보드 2번 모든 port 활서성화
	FIO0DIR |= (1<<4) | (1<<5) | (1<<10) | (1<<11) | (1<<19) | (1<<20) | (1<<21) | (1<<23) | (1<<24);
	FIO1DIR |= (1<<21);
	FIO2DIR |= (1<<11) | (1<<12) | (1<<13);
	FIO3DIR |= (1<<25) | (1<<26);
}

void FND_COM_init()
{
	FIO0CLR |= (1<<23) | (1<<24);
	FIO1CLR |= (1<<21);
	FIO2CLR |= (1<<11) | (1<<12) | (1<<13);
	FIO3CLR |= (1<<25) | (1<<26);	
}

void FND_DATA_init()
{
	FIO0SET |= (1<<23) | (1<<24);
	FIO1SET |= (1<<21);
	FIO2SET |= (1<<11) | (1<<12) | (1<<13);
	FIO3SET |= (1<<25) | (1<<26);	
}

void FND_COM_SEL(int seg) // 어떤 세그먼트에 숫자를 쓸건지?
{
	 if(seg == 1)   FIO0SET |= (1 << 23);
   if(seg == 2)   FIO0SET |= (1 << 24);
   if(seg == 3)   FIO1SET |= (1 << 21);
   if(seg == 4)   FIO2SET |= (1 << 11);
   if(seg == 5)   FIO2SET |= (1 << 12);
   if(seg == 6)   FIO2SET |= (1 << 13);
   if(seg == 7)   FIO3SET |= (1 << 25);
   if(seg == 8)   FIO3SET |= (1 << 26);
}

void FND_DATA_SEL(int num)
{
   if(num == 0)
   {
      FIO0CLR |= (1 << 23) | (1 << 24);
      FIO1CLR |= (1 << 21);
      FIO2CLR |= (1 << 11) | (1 << 12) | (1 << 13);
   }
   if(num == 1)
   {
      FIO0CLR |= (1 << 24);
      FIO1CLR |= (1 << 21);
   }
   if(num == 2)
   {
      FIO0CLR |= (1 << 23) | (1 << 24);
      FIO2CLR |= (1 << 11) | (1 << 12);
      FIO3CLR |= (1 << 25);
   }
   if(num == 3)
   {
      FIO0CLR |= (1 << 23) | (1 << 24);
      FIO1CLR |= (1 << 21);
      FIO2CLR |= (1 << 11);
      FIO3CLR |= (1 << 25);
   }
   if(num == 4)
   {
      FIO0CLR |= (1 << 24);
      FIO1CLR |= (1 << 21);
      FIO2CLR |= (1 << 13);
      FIO3CLR |= (1 << 25);
   }
   if(num == 5)
   {
      FIO0CLR |= (1 << 23);
      FIO1CLR |= (1 << 21);
      FIO2CLR |= (1 << 11) | (1 << 13);
      FIO3CLR |= (1 << 25);
   }
   if(num == 6)
   {
      FIO0CLR |= (1 << 23);
      FIO1CLR |= (1 << 21);
      FIO2CLR |= (1 << 11)| (1 << 12) | (1 << 13);
      FIO3CLR |= (1 << 25);
   }
   if(num == 7)
   {
      FIO0CLR |= (1 << 23) | (1 << 24);
      FIO1CLR |= (1 << 21);
   }
   if(num == 8)
   {
      FIO0CLR |= (1 << 23) | (1 << 24);
      FIO1CLR |= (1 << 21);
      FIO2CLR |= (1 << 11) | (1 << 12) | (1 << 13);
      FIO3CLR |= (1 << 25);
   }
   if(num == 9)
   {
      FIO0CLR |= (1 << 23) | (1 << 24);
      FIO1CLR |= (1 << 21);
      FIO2CLR |= (1 << 13);
      FIO3CLR |= (1 << 25);
   }	
}

void FND_COM_CLK()
{
   FIO0SET |= (1 << 10);
   FIO0CLR |= (1 << 10);
}

void FND_DATA_CLK()
{
   FIO0SET |= (1 << 5);
   FIO0CLR |= (1 << 5);
}

void display(int num,int data)
{
	FND_COM_init();
	FND_COM_SEL(num);
	FND_COM_CLK();
	
	FND_DATA_init();
	FND_DATA_SEL(data);
	FND_DATA_CLK();
	
	for(int i = 0;i<10000;i++);
}