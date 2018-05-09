#ifndef __GPIO_H__
#define __GPIO_H__

#define FIO0SET  (*(volatile int *)0x2009C018)
#define FIO1SET  (*(volatile int *)0x2009C038)
#define FIO2SET  (*(volatile int *)0x2009C058)

#define FIO0CLR  (*(volatile int *)0x2009C01C)
#define FIO1CLR  (*(volatile int *)0x2009C03C)
#define FIO2CLR  (*(volatile int *)0x2009C05C)

#define FIO0DIR   (*(volatile int *)0x2009C000)
#define FIO1DIR   (*(volatile int *)0x2009C020)
#define FIO2DIR   (*(volatile int *)0x2009C040)
#define FIO3DIR   (*(volatile int *)0x2009C060)

#define FIO0PIN   (*(volatile int *)0x2009C014) // DIR input
#define FIO1PIN   (*(volatile int *)0x2009C034) // DIR input
#define FIO2PIN   (*(volatile int *)0x2009C054) // DIR input
#define FIO3PIN   (*(volatile int *)0x2009C074)
	

#define PCONP 	 (*(volatile int *)0x400FC0C4) // ADC 12bit
#define PCLKSEL0 (*(volatile int *)0x400FC1A8) // 24,25
#define PINSEL1  (*(volatile int *)0x4002C004) // 18,19
#define ISER0    (*(volatile int *)0xE000E100) // 22
#define ICER0	   (*(volatile int *)0xE000E180)

#define AD0CR 	 (*(volatile int *)0x40034000) // A/D control register
#define AD0DR2 	 (*(volatile int *)0x40034018) // A/D data register

#define PCONP 	 (*(volatile int *)0x400FC0C4) // UART0 = bit 3
#define PCLKSEL0 (*(volatile int *)0x400FC1A8) // bit 6,7
#define PINSEL0  (*(volatile int *)0x4002C000) // bit 2,3 AF 01

#define U0LCR  	(*(volatile int *)0x4000C00C) // UART Line Control Register 7번 bit 1설정
#define U0FCR  	(*(volatile int *)0x4000C008) // UART FIFO Control Register 0번 bit 1로 설정 (FIFO enable)
#define U0LSR	(*(volatile int *)0x4000C014) // receive register 받은게 있으면 1
#define U0RBR	(*(volatile int *)0x4000C000) // receive register 0~7 bit안에 받은 데이터 저장
#define U0THR	(*(volatile int *)0x4000C000) // transmitter holding register 보낸 데이터 저장
#define U0DLL   (*(volatile int *)0x4000C000) // baudrate register
#define U0DLM   (*(volatile int *)0x4000C004) // baudrate register
#define U0FDR 	(*(volatile int *)0x4000C028) // baudrate register

#define ON 1
#define OFF 0
#define MAX 0xFFF

#endif