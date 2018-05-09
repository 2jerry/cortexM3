#define PCONP 	 (*(volatile int *)0x400FC0C4) // 
#define PINSEL1  (*(volatile int *)0x4002C004) 
#define PINSEL3  (*(volatile int *)0x4002C00C) 
#define PINSEL4  (*(volatile int *)0x4002C010) 

#define USBClkCtrl  (*(volatile int *)0x5000CFF4) 


void USB_Init()
{
	PCONP |= (1<<31);
	PINSEL1 |= ((1<<26)|(1<<28));   /* PINSEL1 26.27, 28.29  = 01 */
	PINSEL3 |=  ((1<< 4)|(2<<28));   /* PINSEL3 4.5 = 01, 28.29 = 10 */
	PINSEL4 |=  (1<<18);   /* PINSEL4 18.19 = 01 */
	
	USBClkCtrl |= (1<<1)|(1<<3);
}