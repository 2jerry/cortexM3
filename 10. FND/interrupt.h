
#define ISER0 (*(volatile int *)0xE000E100) // 인터럽트 0번 set 레지스터 18번
#define ICER0 (*(volatile int *)0xE000E180) // 인터럽트 0번 clear 레지스터
#define ISPR0 (*(volatile int *)0xE000E200) // 인터럽트 0번 pending 레지스터 18번
#define ICPR0 (*(volatile int *)0xE000E280) // 인터럽트 0번 pending clear 레지스터 18번
#define IPR4  (*(volatile int *)0xE000E410) // 인터럽트 0번 우선순위 레지스터 18번

#define EXTINT   (*(volatile int *)0x400FC140) // 인터럽트 flag 레지스터 -> 인터럽트가 발생하면 1이 써진다.
#define EXTMODE  (*(volatile int *)0x400FC148) // 인터럽트 Mode 레지스터 -> 엣지 사용시 1로 써준다.
#define EXTPOLAR (*(volatile int *)0x400FC14C) // 모드 엣지 선택시에만 사용가능 -> rising (1)? falling(0)?

#define PINSEL4 (*(volatile int *)0x4002C010) 

void Init_ISR()
{
	PINSEL4 |= (1<<20); // 스위치 GPIO 기능 -> interrupt 기능으로 활성화 
	ISER0 |= (1<<18);   // 인터럽트 set
	
	EXTMODE |= (1<<0); // 0번 인터럽트 엣지 모드 사용
	EXTPOLAR |= (1<<0); // rising edge
//	EXTPOLAR |= (0<<0); // falling edge
}

