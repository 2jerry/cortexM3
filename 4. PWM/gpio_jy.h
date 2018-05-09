#define FIO0DIR		(*(volatile unsigned int *)0x2009C000)
#define FIO0PIN		(*(volatile unsigned int *)0x2009C014)
#define FIO0SET		(*(volatile unsigned int *)0x2009C018)
#define FIO0CLR		(*(volatile unsigned int *)0x2009C01C)
	
#define FIO1DIR		(*(volatile unsigned int *)0x2009C020)
#define FIO1PIN		(*(volatile unsigned int *)0x2009C034)
#define FIO1SET		(*(volatile unsigned int *)0x2009C038)
#define FIO1CLR		(*(volatile unsigned int *)0x2009C03C)

#define FIO2DIR		(*(volatile unsigned int *)0x2009C040)
#define FIO2PIN		(*(volatile unsigned int *)0x2009C054)
#define FIO2SET		(*(volatile unsigned int *)0x2009C058)
#define FIO2CLR		(*(volatile unsigned int *)0x2009C05C)

#define IOIntStatus (*(volatile unsigned int *)0x40028080)	// 1이면 Pending Interrupt 발생

#define IO0IntStatR	(*(volatile unsigned int *)0x400280A4)	// 1이면 Edge 발생
#define IO0IntStatF	(*(volatile unsigned int *)0x400280A8)	
#define IO0IntClr		(*(volatile unsigned int *)0x400280AC)	// 1을 쓰면 초기화
#define IO0IntEnR		(*(volatile unsigned int *)0x400280B0)	// 1을 쓰면 Enable
#define IO0IntEnF		(*(volatile unsigned int *)0x400280B4)
	
#define IO2IntStatR	(*(volatile unsigned int *)0x400280A4)	// 1이면 Edge 발생
#define IO2IntStatF	(*(volatile unsigned int *)0x400280A8)	
#define IO2IntClr		(*(volatile unsigned int *)0x400280AC)	// 1을 쓰면 초기화
#define IO2IntEnR		(*(volatile unsigned int *)0x400280B0)	// 1을 쓰면 Enable
#define IO2IntEnF		(*(volatile unsigned int *)0x400280B4)

#define SEC1	24000000

#define OFF		0
#define ON		1
#define BLK		2

#define BUTTON		(1 << 10)	// Port 2
#define SELECT		(1 << 20)	// Port 1
#define LEFT			(1 << 23)
#define UP				(1 << 24)
#define RIGHT			(1 << 25)
#define DOWN			(1 << 26)
#define POTENTIO	(1 << 25)	// Port 0

/* LED */
unsigned int LED[8] = {0x10000000, 0x20000000, 0x80000000,							  						// Port 1
											 0x00000004, 0x00000008, 0x00000010, 0x00000020, 0x00000040}; 	// Port 2

void Delay(int sec)
{
	for(int i = 0; i < sec; i++);
}

void LED_Init()	// LED 전체 초기화
{
	for(int i = 0; i < 8; i++)
	{
		if(i < 3)	FIO1DIR |= LED[i];
		else			FIO2DIR |= LED[i];
	}
}

void LED_C(unsigned char lednum, unsigned char onoff, unsigned int sec)
{
	if(onoff == ON)
	{
		if(lednum < 3)			FIO1SET |= LED[lednum];
		else if(lednum < 8)	FIO2SET |= LED[lednum];
		else 
		{
			FIO1SET |= (LED[0] | LED[1] | LED[2]);
			FIO2SET |= (LED[3] | LED[4] | LED[5] | LED[6] | LED[7]);
		}
		
		if(sec)		Delay(sec);
	}
	else if(onoff == OFF)
	{
		if(lednum < 3)			FIO1CLR |= LED[lednum];
		else if(lednum < 8)	FIO2CLR |= LED[lednum];
		else 
		{
			FIO1CLR |= (LED[0] | LED[1] | LED[2]); 
			FIO2CLR |= (LED[3] | LED[4] | LED[5] | LED[6] | LED[7]);
		}
		
		if(sec)		Delay(sec);
	}
	else
	{
		if(lednum < 3)
		{
			FIO1SET |= LED[lednum];
			Delay(sec);
			FIO1CLR |= LED[lednum];
			Delay(sec);
		}
		else if(lednum < 8)
		{
			FIO2SET |= LED[lednum];
			Delay(sec);
			FIO2CLR |= LED[lednum];
			Delay(sec);
		}
		else 
		{
			FIO1SET |= (LED[0] | LED[1] | LED[2]);
			FIO2SET |= (LED[3] | LED[4] | LED[5] | LED[6] | LED[7]);
			Delay(sec);
			FIO1CLR |= (LED[0] | LED[1] | LED[2]); 
			FIO2CLR |= (LED[3] | LED[4] | LED[5] | LED[6] | LED[7]);
			Delay(sec);
		}
	}
}
