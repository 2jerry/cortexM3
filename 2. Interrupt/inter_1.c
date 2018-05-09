/* GPIO ���ͷ�Ʈ�� �̿��� ���� */
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

#define IO2IntStatR (*(volatile int *)0x400280A4) // GPIO PORT2 ����¡ ���� ����
#define IO2IntEnR   (*(volatile int *)0x400280B0) // ����¡ ���� ����
#define IO2IntClr   (*(volatile int *)0x400280AC)

void Init_ISR()
{
	PINSEL4 |= (1<<20); // ����ġ GPIO ��� -> interrupt ������� Ȱ��ȭ 
  ISER0 |= (1<<21);   // ���ͷ�Ʈ set
	
	IO2IntEnR |= (1<<10); // GPIO2 10�� interrupt enable
	IO2IntStatR |= (0<<10); // interrupt status �ʱ�ȭ
  IO2IntClr |= (1<<10);
}


int cnt;
int main()
{
	Init_ISR();
	led_init();
	cnt = 0;
	
	while(1)
		led_onoff(ON,cnt);
	
	return 0;
}

// GPIO ���ͷ�Ʈ�� ����� ���� ���ͷ�Ʈ�� ä���� �ٸ��� ������ �־���Ѵ�.
//  => ä�� 3�� �̿�.
//  ���� ���� �� �ٽ� ������ �ʱ�ȭ �����־���� ���� ���ͷ�Ʈ Ȯ���� �����ϴ�.
void EINT3_IRQHandler(void)
{
	if(IO2IntStatR & (1<<10))
	{
		cnt++;
		IO2IntClr |= (1<<10); //�ʱ�ȭ�� ��ġ Ȯ��
	}
}	