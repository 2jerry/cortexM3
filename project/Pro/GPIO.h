#ifndef __GPIO_H__
#define __GPIO_H__

#define FIO0SET  (*(volatile int *)0x2009C018)
#define FIO1SET  (*(volatile int *)0x2009C038)
#define FIO2SET  (*(volatile int *)0x2009C058)
#define FIO3SET (*(volatile int *)0x2009C078)

#define FIO0CLR  (*(volatile int *)0x2009C01C)
#define FIO1CLR  (*(volatile int *)0x2009C03C)
#define FIO2CLR  (*(volatile int *)0x2009C05C)
#define FIO3CLR (*(volatile int *)0x2009C07C)

#define FIO0DIR   (*(volatile int *)0x2009C000)
#define FIO1DIR   (*(volatile int *)0x2009C020)
#define FIO2DIR   (*(volatile int *)0x2009C040)
#define FIO3DIR   (*(volatile int *)0x2009C060)

#define FIO0PIN   (*(volatile int *)0x2009C014) // DIR input
#define FIO1PIN   (*(volatile int *)0x2009C034) // DIR input
#define FIO2PIN   (*(volatile int *)0x2009C054) // DIR input
#define FIO3PIN   (*(volatile int *)0x2009C074)


/*----timer 0----------------*/
#define PCLKSEL0 (*(volatile int *)0x400FC1A8) // Peripheral clock (Timer 0,1)
#define PCONP    (*(volatile int *)0x400FC0C4) // power register
#define ISER0    (*(volatile int *)0xE000E100) //
#define T0IR     (*(volatile int *)0x40004000) // interrupt register
#define T0TC     (*(volatile int *)0x40004008) // timer counter register
#define T0TCR    (*(volatile int *)0x40004004) // timer control register
#define T0MR0    (*(volatile int *)0x40004018) // match register
#define T0MCR    (*(volatile int *)0x40004014) // match control register

/*----timer 1----------------*/
#define PCONP    (*(volatile int *)0x400FC0C4) // power register
#define T1IR     (*(volatile int *)0x40008000) // interrupt register
#define T1TC     (*(volatile int *)0x40008008) // timer counter register
#define T1TCR    (*(volatile int *)0x40008004) // timer control register
#define T1MR0    (*(volatile int *)0x40008018) // match register
#define T1MCR    (*(volatile int *)0x40008014) // match control register

/*----timer 2----------------*/
#define PCLKSEL1 (*(volatile int *)0x400FC1AC) // Peripheral clock (Timer 2,3)
#define T2IR     (*(volatile int *)0x40090000) // interrupt register
#define T2TC     (*(volatile int *)0x40090008) // timer counter register
#define T2TCR    (*(volatile int *)0x40090004) // timer control register
#define T2MR0    (*(volatile int *)0x40090018) // match register
#define T2MCR    (*(volatile int *)0x40090014) // match control register

/*----timer 3----------------*/
#define T3IR     (*(volatile int *)0x40094000) // interrupt register
#define T3TC     (*(volatile int *)0x40094008) // timer counter register
#define T3TCR    (*(volatile int *)0x40094004) // timer control register
#define T3MR0    (*(volatile int *)0x40094018) // match register
#define T3MCR    (*(volatile int *)0x40094014) // match control register

#define PINSEL7   (*(volatile int *)0x4002C01C) // PWM AF 11

#define PCLKSEL0  (*(volatile int *)0x400FC1A8)
#define PCONP	    (*(volatile int *)0x400FC0C4) // PWM power
#define PWM1IR	  (*(volatile int *)0x40018000) // PWM interrupt	
#define PWM1TCR	  (*(volatile int *)0x40018004) // PWM Timer/Counter
#define PWM1PR    (*(volatile int *)0x4001800C)	// PWM prescale   
#define PWM1MCR	  (*(volatile int *)0x40018014) // PWM Match Control 
#define PWM1CCR	  (*(volatile int *)0x40018028)	// PWM Capture Control
#define PWM1PCR	  (*(volatile int *)0x4001804C) // PWM Control
#define PWM1LER	  (*(volatile int *)0x40018050) // Load Enable
#define PWM1MR0   (*(volatile int *)0x40018018)
#define PWM1MR2   (*(volatile int *)0x40018020)


#endif