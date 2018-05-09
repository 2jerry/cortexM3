#include "uart.h"
#define FIO1DIR  (*(volatile int *)0x2009C020)
#define FIO1SET  (*(volatile int *)0x2009C038)
#define FIO1CLR  (*(volatile int *)0x2009C03C)

#define FIO2DIR  (*(volatile int *)0x2009C040)
#define FIO2SET  (*(volatile int *)0x2009C058)
#define FIO2CLR  (*(volatile int *)0x2009C05C)

#define PCONP 	 (*(volatile int *)0x400FC0C4) // ADC 12bit
#define PCLKSEL0 (*(volatile int *)0x400FC1A8) // 24,25
#define PINSEL1  (*(volatile int *)0x4002C004) // 18,19
#define ISER0    (*(volatile int *)0xE000E100) // 22
#define ICER0	   (*(volatile int *)0xE000E180)

#define AD0CR 	 (*(volatile int *)0x40034000) // A/D control register
#define AD0DR2 	 (*(volatile int *)0x40034018) // A/D data register

#define ON 1
#define OFF 0
#define MAX 0xFFF


// LED 1~8번
int led[8] = { (1<<28), (1<<29), (1<<31), (1<<2), (1<<3), (1<<4), (1<<5),(1<<6) };

// led 초기화 함수
void led_init()
{
	FIO1DIR |= (led[0] | led[1] | led[2]); // led를 출력(ouput으로 설정)
	FIO2DIR |= (led[3] | led[4] | led[5] | led[6] | led[7]);
}

// led 제어 함수
void led_onoff(int value,int num)
{
	if(value) // ON
	{
		if(num>2)
			FIO2SET |= led[num];
		else
			FIO1SET |= led[num];
	}		
	else // OFF
	{
		if(num>2)
			FIO2CLR |= led[num];
		else
			FIO1CLR |= led[num];
	}
}

void Init_ADC()
{
	PINSEL1 |= (1<<18); // port0 25pin ADC 활성화 (01)	
	PCONP |= (1<<12); 
	PCLKSEL0 |= (1<<24)+(1<<25);
	AD0DR2 |= 0;
	/*---ADCR init---*/
	AD0CR = 0;
	AD0CR |= (1<<2) + (1<<21);	
	ISER0 |= (1<<22); // ADC interrupt 활성화
}

int val =-1;
int prev_val = 0;

int main(void)
{
	led_init();
	UART0_Init();
	Init_ADC();
	// 31번 bit가 1이 되면 ad변환이 완료

	while(1)
	{
		AD0CR |= (1<<24); // adc conversion start

		val = (val/(MAX/8)); // led 번호 설정 
		
		Uart_Tx_char(val+'0');
		//for(int i = 0;i<12000000;i++);
		
		if(val <=0)
			continue;
		else if(prev_val > val) // 값이 감소되고 있으면
			led_onoff(OFF,prev_val-1);
		else
			led_onoff(ON,val-1);
		prev_val = val; // 이전의 값을 저장
		val = 0;
	}
}

// ADC Interrupt Reqest 
void ADC_IRQHandler(void)
{
	if (AD0DR2 & 0x80000000) // ADC 2 Channel 활성화 상태 확인
	{	
		AD0CR &= ~(0x00000004); // ADC 2 Channel disable
		val = (AD0DR2 >> 4); // ADC 결과 값 저장
		ICER0 |= (1<<22);  // ADC interrupt 비활성화
		ISER0 |= (1<<22);  // ADC interrupt 활성화
		AD0CR |= (0x00000004); // ADC 2 Channel enable
	}
}
