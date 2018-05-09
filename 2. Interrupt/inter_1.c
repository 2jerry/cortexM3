/* GPIO 인터럽트를 이용한 예제 */
#include "led.h"

/* 
 * 스위치(GPIO 2 -10번)를 일반적인 GPIO 기능이 아닌 인터럽트로 사용하기 위해서는
 * pin function을 설정해 주어야 한다. GPIO 기능은 00 , 인터럽트 기능은 01
*/
#define ISER0 (*(volatile int *)0xE000E100) // 인터럽트 0번 set 레지스터 18번
#define ICER0 (*(volatile int *)0xE000E180) // 인터럽트 0번 clear 레지스터
#define ISPR0 (*(volatile int *)0xE000E200) // 인터럽트 0번 pending 레지스터 18번
#define ICPR0 (*(volatile int *)0xE000E280) // 인터럽트 0번 pending clear 레지스터 18번
#define IPR4  (*(volatile int *)0xE000E410) // 인터럽트 0번 우선순위 레지스터 18번

#define EXTINT   (*(volatile int *)0x400FC140) // 인터럽트 flag 레지스터 -> 인터럽트가 발생하면 1이 써진다.
#define EXTMODE  (*(volatile int *)0x400FC148) // 인터럽트 Mode 레지스터 -> 엣지 사용시 1로 써준다.
#define EXTPOLAR (*(volatile int *)0x400FC14C) // 모드 엣지 선택시에만 사용가능 -> rising (1)? falling(0)?

#define PINSEL4 (*(volatile int *)0x4002C010) 

#define IO2IntStatR (*(volatile int *)0x400280A4) // GPIO PORT2 라이징 엣지 검출
#define IO2IntEnR   (*(volatile int *)0x400280B0) // 라이징 엣지 설정
#define IO2IntClr   (*(volatile int *)0x400280AC)

void Init_ISR()
{
	PINSEL4 |= (1<<20); // 스위치 GPIO 기능 -> interrupt 기능으로 활성화 
  ISER0 |= (1<<21);   // 인터럽트 set
	
	IO2IntEnR |= (1<<10); // GPIO2 10번 interrupt enable
	IO2IntStatR |= (0<<10); // interrupt status 초기화
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

// GPIO 인터럽트를 사용할 때는 인터럽트의 채널을 다르게 설정해 주어야한다.
//  => 채널 3번 이용.
//  엣지 검출 후 다시 엣지를 초기화 시켜주어야지 다음 인터럽트 확인이 가능하다.
void EINT3_IRQHandler(void)
{
	if(IO2IntStatR & (1<<10))
	{
		cnt++;
		IO2IntClr |= (1<<10); //초기화의 위치 확인
	}
}	