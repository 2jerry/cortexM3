#include "GPIO.h"
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

void Motor_set()
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
/*
int main()
{
		EXT_IO_A_Init();
		while(1)
		{
				Motor_set(1);
			  for(int i = 0;i<12000000;i++); // delay
		}
	
}*/