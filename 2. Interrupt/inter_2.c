/* �ܺ� ���ͷ�Ʈ�� �̿��� ���� */

#include "led.h"

/* 
 * ����ġ(GPIO 2 -10��)�� �Ϲ����� GPIO ����� �ƴ� ���ͷ�Ʈ�� ����ϱ� ���ؼ���
 * pin function�� ������ �־�� �Ѵ�. GPIO ����� 00 , ���ͷ�Ʈ ����� 01
*/
#define ISER0 (*(volatile int *)0xE000E100) // ���ͷ�Ʈ 0�� set �������� 18��
#define ICER0 (*(volatile int *)0xE000E180) // ���ͷ�Ʈ 0�� clear ��������
#define ISPR0 (*(volatile int *)0xE000E200) // ���ͷ�Ʈ 0�� pending �������� 18��
#define ICPR0 (*(volatile int *)0xE000E280) // ���ͷ�Ʈ 0�� pending clear �������� 18��
#define IPR4  (*(volatile int *)0xE000E410) // ���ͷ�Ʈ 0�� �켱���� �������� 18��

#define EXTINT   (*(volatile int *)0x400FC140) // ���ͷ�Ʈ flag �������� -> ���ͷ�Ʈ�� �߻��ϸ� 1�� ������.
#define EXTMODE  (*(volatile int *)0x400FC148) // ���ͷ�Ʈ Mode �������� -> ���� ���� 1�� ���ش�.
#define EXTPOLAR (*(volatile int *)0x400FC14C) // ��� ���� ���ýÿ��� ��밡�� -> rising (1)? falling(0)?

#define PINSEL4 (*(volatile int *)0x4002C010) 

void Init_ISR()
{
	PINSEL4 |= (1<<20); // ����ġ GPIO ��� -> interrupt ������� Ȱ��ȭ 
	ISER0 |= (1<<18);   // ���ͷ�Ʈ set
	
	EXTMODE |= (1<<0); // 0�� ���ͷ�Ʈ ���� ��� ���
	EXTPOLAR |= (1<<0); // rising edge
//	EXTPOLAR |= (0<<0); // falling edge
}
int cnt = -1;
int main()
{
	Init_ISR();
	led_init();
	
	while(1)
	{
		led_onoff(ON,cnt);
		
	}
	
	return 0;
}


void EINT0_IRQHandler(void)
{
	EXTINT |= (1<<0); // 0�� ���ͷ�Ʈ ���
	//for(int i =0;i<200000;i++);
  cnt ++;
}