
#include "led.h"

int main(void)
{	
	Led_Init();	//	LED 전체 초기화
  // 계속 깜빡거리는 동작
	while(1)
	{
		Led_OnOff(ON,1);
		for(int i =0;i<12000000;i++);
		Led_OnOff(OFF,1);
		for(int i =0;i<12000000;i++);
		
	}
	
}










