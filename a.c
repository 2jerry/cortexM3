#define FIO1SET  (*(volatile int *)0x2009C038)
#define FIO1CLR  (*(volatile int *)0x2009C03C)
#define FIO2SET  (*(volatile int *)0x2009C058)
#define FIO2CLR  (*(volatile int *)0x2009C05C)
 
#define FIO0DIR (*(volatile int *)0x2009C000)
#define FIO1DIR (*(volatile int *)0x2009C020)
#define FIO2DIR (*(volatile int *)0x2009C040)
#define FIO3DIR (*(volatile int *)0x2009C060)

#define FIO0PIN (*(volatile int *)0x2009C014) // DIR input
#define FIO1PIN (*(volatile int *)0x2009C034) // DIR input
#define FIO2PIN (*(volatile int *)0x2009C054) // DIR input
#define FIO3PIN (*(volatile int *)0x2009C074)

#define ON 1
#define OFF 0

int led[8] = { (1<<28), (1<<29), (1<<31), (1<<2), (1<<3), (1<<4), (1<<5),(1<<6) };

// led 초기화 함수
void led_Init()
{
 FIO1DIR |= (led[0] | led[1] | led[2]); // led를 출력(ouput으로 설정)
 FIO2DIR |= (led[3] | led[4] | led[5] | led[6] | led[7]);
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
void EXT_IO_C_Init()
{
 /* P0.4 는 확장보드를 input or output 을 결정한다. */
 /* 확장보드 A -> P0.19 (low = output, high = input) *
  * 확장보드 B -> P0.20 (low = output, high = input) *
  * 확장보드 C -> P0.21 (low = output, high = input) */
 FIO0DIR |= (1<<4) | (1<<21); // 확장보드 C input으로 설정
 FIO1DIR |= (1<<21);
 FIO2DIR |= (1<<11);
 

}

void Keypad_DIR_Output()
{
 // output 설정
 FIO0DIR |= (1<<5);
 FIO0DIR |= (1<<10);
 FIO2DIR |= (1<<12);
 FIO2DIR |= (1<<13);
}

void Keypad_DIR_Input()
{

 FIO0PIN |= (1<<4);
 FIO0DIR &= ~(1<<23);
 FIO0DIR &= ~(1<<24);
 FIO3DIR &= ~(1<<25);
 FIO3DIR &= ~(1<<26);
}


int main()
{
 led_Init();
 EXT_IO_C_Init();
 Keypad_DIR_Input();
 
 // ROW 1 검사
 while(1)
 {
  Keypad_DIR_Output();
	FIO0PIN &=  ~(1<<5);
  FIO0PIN |= (1<<10);
  FIO2PIN |= (1<<12);
  FIO2PIN |= (1<<13);
	 
	 
  FIO2PIN |= (1<<11); // CS Clock High Edge
  FIO2PIN &= ~(1<<11);
  
  if(!(FIO3PIN & (1<<26)))   led_onoff(ON,1);
  if(!(FIO3PIN & (1<<25)))   led_onoff(ON,2);
  if(!(FIO0PIN & (1<<24)))   led_onoff(ON,3);
  if(!(FIO0PIN & (1<<23)))   led_onoff(ON,4);
 
 }

 
}
