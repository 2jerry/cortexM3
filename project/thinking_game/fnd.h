#ifndef __FND_H__
#define __FND_H__

void FND_init()
{
	FIO0SET |= (1<<19); // Ȯ�庸�� PORT 2�� ���
	FIO0CLR |= (1<<20); // Ȯ�庸�� PORT 2�� ���
	FIO0SET |= (1<<21); // Ȯ�庸�� PORT 2�� ���
	// Ȯ�庸�� 2�� ��� port Ȱ����ȭ
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

void FND_COM_SEL(int seg) // � ���׸�Ʈ�� ���ڸ� ������?
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

void display_num(int num,int data)
{
	FND_COM_init();
	FND_COM_SEL(num);
	FND_COM_CLK();
	
	FND_DATA_init();
	FND_DATA_SEL(data);
	FND_DATA_CLK();
	
	//for(int i = 0;i<10000000;i++);
}


void FND_DATA_LEV(char c)
{
	if(c == 'L')
	{
		FIO2CLR |= (1 << 11) | (1 << 12) | (1 << 13);
	}
	if(c == 'E')
	{
		FIO0CLR |= (1 << 23);
		FIO2CLR |= (1 << 11) | (1 << 12) | (1 << 13);
		FIO3CLR |= (1 << 25);
	}
	if(c == 'V')
	{
		FIO0CLR |= (1 << 24);
		FIO1CLR |= (1 << 21);
		FIO2CLR |= (1 << 11) | (1 << 12) | (1 << 13);
	}
	if(c == '.')
	{
		FIO3CLR |= (1 << 26);
	}
	
}

void display_char(int num, char c)
{
	FND_COM_init();
	FND_COM_SEL(num);
  FND_COM_CLK();
	
	FND_DATA_init();
	FND_DATA_LEV(c);
	FND_DATA_CLK();
	
	for(int i = 0;i<10000;i++);
}

void display(int score)
{
	/* 1�� �ڸ� */
	FND_COM_init();
	FND_COM_SEL(8);
	FND_COM_CLK();
	
	FND_DATA_init();
	FND_DATA_SEL(score%10);
	FND_DATA_CLK();
	
	for(int i = 0;i<10000;i++);
	
	/* 10�� �ڸ� */
	FND_COM_init();
	FND_COM_SEL(7);
	FND_COM_CLK();
	
	FND_DATA_init();
	FND_DATA_SEL((score%100)/10);
	FND_DATA_CLK();
	
	for(int i = 0;i<10000;i++);
	
	/* 100�� �ڸ� */
	FND_COM_init();
	FND_COM_SEL(6);
	FND_COM_CLK();
	
	FND_DATA_init();
	FND_DATA_SEL((score%1000)/100);
	FND_DATA_CLK();
	
	for(int i = 0;i<10000;i++);
	
	/* 1000�� �ڸ�*/
	FND_COM_init();
	FND_COM_SEL(5);
	FND_COM_CLK();
	
	FND_DATA_init();
	FND_DATA_SEL(score/1000);
	FND_DATA_CLK();
	
	for(int i = 0;i<10000;i++);
	//
}
#endif