#define FIO0SET  (*(volatile int *)0x2009C018)
#define FIO1SET  (*(volatile int *)0x2009C038)
#define FIO2SET  (*(volatile int *)0x2009C058)

#define FIO0CLR  (*(volatile int *)0x2009C01C)
#define FIO1CLR  (*(volatile int *)0x2009C03C)
#define FIO2CLR  (*(volatile int *)0x2009C05C)
	
#define FIO0DIR (*(volatile int *)0x2009C000)
#define FIO1DIR (*(volatile int *)0x2009C020)
#define FIO2DIR (*(volatile int *)0x2009C040)
#define FIO3DIR (*(volatile int *)0x2009C060)

#define FIO0PIN (*(volatile int *)0x2009C014) // DIR input
#define FIO1PIN (*(volatile int *)0x2009C034) // DIR input
#define FIO2PIN (*(volatile int *)0x2009C054) // DIR input
#define FIO3PIN (*(volatile int *)0x2009C074)
