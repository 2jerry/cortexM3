
#include "led.h"

int main(void)
{	
	Led_Init();	//	LED ��ü �ʱ�ȭ
  // ��� �����Ÿ��� ����
	while(1)
	{
		Led_OnOff(ON,1);
		for(int i =0;i<12000000;i++);
		Led_OnOff(OFF,1);
		for(int i =0;i<12000000;i++);
		
	}
	
}










