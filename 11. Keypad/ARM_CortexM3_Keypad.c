#include "gpio.h"
#include "led_.h"
#include "fnd_.h"

void keypad_hex()
{
	int num = 0;
	num = keypad();
	if(num & 0x01) led_onoff(ON,1);
  else led_onoff(OFF,1);	
	if(num >> 1 & 0x01) led_onoff(ON,2);
  else led_onoff(OFF,2);	
	if(num >> 2 & 0x01) led_onoff(ON,3);
  else led_onoff(OFF,3);	
	if(num >> 3 & 0x01) led_onoff(ON,4);
  else led_onoff(OFF,4);	
	if(num >> 4 & 0x01) led_onoff(ON,5);
  else led_onoff(OFF,5);	
	if(num >> 5 & 0x01) led_onoff(ON,6);
  else led_onoff(OFF,6);	
	if(num >> 6 & 0x01) led_onoff(ON,7);
  else led_onoff(OFF,7);	
	if(num >> 7 & 0x01) led_onoff(ON,8);
  else led_onoff(OFF,8);	
	
}

int main()
{
	led_Init();
	EXT_IO_C_Init();
	Keypad_DIR_Input();

	// ROW 1 검사
	for(;;)
	{
		keypad_hex();
	}	
}

//int main()
//{
// led_Init();
// EXT_IO_C_Init();
// Keypad_DIR_Input();
// 
// // ROW 1 검사
// while(1)
// {
//	 
//  Keypad_DIR_Output();


//	FIO2PIN |= (1<<11); // CS Clock High Edge
//	FIO2PIN &= ~(1<<11); 
//	 
//	FIO0PIN &= ~(1<<5);
//	FIO0PIN |= (1<<10);
//	FIO2PIN |= (1<<12);
//	FIO2PIN |= (1<<13);

// 


//  if(!(FIO3PIN & (1<<26)))   led_onoff(ON,1);
//  if(!(FIO3PIN & (1<<25)))   led_onoff(ON,2);
//  if(!(FIO0PIN & (1<<24)))   led_onoff(ON,3);
//  if(!(FIO0PIN & (1<<23)))   led_onoff(ON,4); 
//	 

// }
//}

