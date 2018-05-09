#include "init_gpio.h"

struct value
{
	uint8_t PORT_NUM; // GPIO 포트 번호
	uint32_t PIN_NUM; // GPIO 핀 번호
}; 
struct value LED[8];

/*-----------led function-------------*/
void Led_Init()
{

	LED[0]. PIN_NUM = GPIO_PIN_28;
	LED[1]. PIN_NUM = GPIO_PIN_29;
	LED[2]. PIN_NUM = GPIO_PIN_31;
	for(int i = 2;i<8;i++)
	{
		LED[i].PIN_NUM = (GPIO_PIN_0 << i);
	}	
	for(int i = 0;i<8;i++)
	{
		if(i>2)
			LED[i].PORT_NUM = 2;
		else
			LED[i].PORT_NUM = 1;
	}
	
	GPIO_SetDir(GPIO_PORT_1, (1<<28) | (1<<29) | (1<<31), OUTPUT); 
	GPIO_SetDir(GPIO_PORT_2, (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6), OUTPUT); 
	GPIO_ClearValue(GPIO_PORT_1,  (1<<28) | (1<<29) | (1<<31));		
	GPIO_ClearValue(GPIO_PORT_2,  (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6));		
}
// switch case 문을 구조체로 바꾸어 다시 설계
void Led_OnOff(int value,int led)
{
	if(value) // ON
	{
		GPIO_SetValue(LED[led-1].PORT_NUM,LED[led-1].PIN_NUM);
	}
	else
	{
		GPIO_ClearValue(LED[led-1].PORT_NUM,LED[led-1].PIN_NUM);
	}
}