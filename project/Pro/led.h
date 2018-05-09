#include "GPIO.h"

#define ON 1
#define OFF 0
#define ALL 8
#define MAX 0xFFF

// LED 1~8번
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
