#ifndef __GPIO_H__
#define __GPIO_H__

#define FIO0DIR (*(volatile int *)0x2009C000)
#define FIO1DIR (*(volatile int *)0x2009C020)
#define FIO2DIR (*(volatile int *)0x2009C040)
#define FIO3DIR (*(volatile int *)0x2009C060)
	
#define FIO0CLR (*(volatile int *)0x2009C01C)
#define FIO1CLR (*(volatile int *)0x2009C03C)
#define FIO2CLR (*(volatile int *)0x2009C05C)
#define FIO3CLR (*(volatile int *)0x2009C07C)

#define FIO0SET (*(volatile int *)0x2009C018)
#define FIO1SET (*(volatile int *)0x2009C038)
#define FIO2SET (*(volatile int *)0x2009C058)
#define FIO3SET (*(volatile int *)0x2009C078)

#define FIO2PIN (*(volatile int *)0x2009C054) // 스위치
#define FIO1PIN (*(volatile int *)0x2009C034) // joystic

/* --- interrput ----*/
#define ISER0 (*(volatile int *)0xE000E100) // 인터럽트 0번 set 레지스터 18번
#define ICER0 (*(volatile int *)0xE000E180) // 인터럽트 0번 clear 레지스터
#define ISPR0 (*(volatile int *)0xE000E200) // 인터럽트 0번 pending 레지스터 18번
#define ICPR0 (*(volatile int *)0xE000E280) // 인터럽트 0번 pending clear 레지스터 18번
#define IPR4  (*(volatile int *)0xE000E410) // 인터럽트 0번 우선순위 레지스터 18번

#define EXTINT   (*(volatile int *)0x400FC140) // 인터럽트 flag 레지스터 -> 인터럽트가 발생하면 1이 써진다.
#define EXTMODE  (*(volatile int *)0x400FC148) // 인터럽트 Mode 레지스터 -> 엣지 사용시 1로 써준다.
#define EXTPOLAR (*(volatile int *)0x400FC14C) // 모드 엣지 선택시에만 사용가능 -> rising (1)? falling(0)?

/* --- timer ----*/
#define PCLKSEL0 (*(volatile int *)0x400FC1A8) // Peripheral clock (Timer 0,1)
#define PCONP    (*(volatile int *)0x400FC0C4) // power register
#define ISER0    (*(volatile int *)0xE000E100) //
#define T0IR     (*(volatile int *)0x40004000) // interrupt register
#define T0TC     (*(volatile int *)0x40004008) // timer counter register
#define T0TCR    (*(volatile int *)0x40004004) // timer control register
#define T0MR0    (*(volatile int *)0x40004018) // match register
#define T0MCR    (*(volatile int *)0x40004014) // match control register

#define PCLKSEL1 (*(volatile int *)0x400FC1AC) // Peripheral clock (Timer 0,1)
#define PCONP    (*(volatile int *)0x400FC0C4) // power register
#define ISER0    (*(volatile int *)0xE000E100) //
#define T1IR     (*(volatile int *)0x40008000) // interrupt register
#define T1TC     (*(volatile int *)0x40008008) // timer counter register
#define T1TCR    (*(volatile int *)0x40008004) // timer control register
#define T1MR0    (*(volatile int *)0x40008018) // match register
#define T1MCR    (*(volatile int *)0x40008014) // match control register

#define PINSEL4 (*(volatile int *)0x4002C010) 

#define ON 1
#define OFF 0

#endif