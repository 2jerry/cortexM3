#include "gpio.h"

#ifndef __LED_H__
#define __LED_H__

int led[8] = { (1<<28), (1<<29), (1<<31), (1<<2), (1<<3), (1<<4), (1<<5),(1<<6) };

void delay(double s)
{
	int i;
	int time = s*12000000;
	for(i = 0;i<time;i++);
}	
	
void led_init()
{
	FIO1DIR |= (led[0] | led[1] | led[2]); // led? ??(ouput?? ??)
	//FIO1CLR |= (led[0] | led[1] | led[2]);
	
	FIO2DIR |= (led[3] | led[4] | led[5] | led[6] | led[7]);
	//FIO2CLR |= (led[3] | led[4] | led[5] | led[6] | led[7]);
}

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

void led_all(int value)
{
		for(int i = 0;i<8;i++)
				led_onoff(value,i);
}

void led_blink(int num)
{
	led_onoff(ON,num);
	delay(0.1);
	led_onoff(OFF,num);
	delay(0.1);
}

#endif