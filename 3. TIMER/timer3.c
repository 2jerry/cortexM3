/* Register Define ------------*/
#define FIO1DIR (*(volatile int *)0x2009C020)
#define FIO1SET (*(volatile int *)0x2009C038)
#define FIO1CLR (*(volatile int *)0x2009C03C)

#define FIO2DIR (*(volatile int *)0x2009C040)
#define FIO2SET (*(volatile int *)0x2009C058)
#define FIO2CLR (*(volatile int *)0x2009C05C)

#define PCLKSEL0 (*(volatile int *)0x400FC1A8) // Peripheral clock (Timer 0,1)
#define PCONP    (*(volatile int *)0x400FC0C4) // power register
#define ISER0    (*(volatile int *)0xE000E100) //
#define T0IR     (*(volatile int *)0x40004000) // interrupt register
#define T0TC     (*(volatile int *)0x40004008) // timer counter register
#define T0TCR    (*(volatile int *)0x40004004) // timer control register
#define T0MR0    (*(volatile int *)0x40004018) // match register
#define T0MCR    (*(volatile int *)0x40004014) // match control register

#define FIO2PIN (*(volatile int *)0x2009C054) // 스위치

#define ON 1
#define OFF 0
#define ALL 9

void TIMER0_IRQHandler(void);

// LED 1~8번
int led[8] = { (1<<28), (1<<29), (1<<31), (1<<2), (1<<3), (1<<4), (1<<5),(1<<6) };
   
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
      if(num>3)
         FIO2SET |= led[num-1];
      else
         FIO1SET |= led[num-1];
   }      
   else // OFF
   {
      if(num>3)
         FIO2CLR |= led[num-1];
      else
         FIO1CLR |= led[num-1];
   }

}
void led_all(int value)
{
   for(int i = 1;i<9;i++)
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

void led_blink(int value)
{
   if(value == ALL)
   {
	   led_all(ON);
	   delay(0.5);
	   led_all(OFF);
	   delay(0.5); 
   }
   else
   {
	   led_onoff(ON,value);
	   delay(0.5);
	   led_onoff(OFF,value);
	   delay(0.5);
   }
   

}

void Init_Timer(void)
{	 
	PCONP |= (1<<1); // timer0 setting
	PCLKSEL0 |= (1<<2)+(1<<3); //  
	ISER0 |= (1<<1);
	//T0TC = 0; // count start value
	T0TCR |= 0x00000001;
	T0MR0 = 12000000/4;  // 1초 값 (= 12000000 = 12MHZ) 설정
	T0MCR |= 0x00000001; //
	//T0IR |= 0x00000001; 
}

int flag = 0, cnt = 0;
int main()
{
   led_init();
   Init_Timer();
   while(1)
   {
	   if(flag)
	   {
			if(cnt > 8)
			{   
				led_all(OFF);
				cnt = 0;
				flag = 0;
			}
			else
				led_onoff(ON,cnt);
	   }
		
   }
}

// Interrupt Reqzeust Timer 일치할 때 진입
void TIMER0_IRQHandler(void)
{
	flag = 1;
	cnt++;
	T0IR |= 0; // interrupt flag clear
	T0TC = 0; // 카운트 값 clear
}