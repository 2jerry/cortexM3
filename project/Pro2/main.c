#include "led.h"
#include "StepMotor.h"
#include "uart.h"
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
int flag = 0;
int main(void)
{
	led_init();
	Init_ADC();
	EXT_IO_A_Init(); // 확장보드 A 활성화
	UART0_Init();
	unsigned char c;
	unsigned char buffer[10];
	
	// 31번 bit가 1이 되면 ad변환이 완료
	Uart_Tx_string("Uart start\r\n");
	while(1)
	{
		
		AD0CR |= (1<<24); // adc conversion start
	//val = (val/(MAX/6));
		
		
			if (val == 3000 || val == 1000 || val == 2000)
			{
				Motor_set();
				for(int i = 0;i<12000000;i++); // delay
				
				prev_val = val;
				val = 0;
			}
				
		//; // led 번호 설정 
		
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
		flag = 1;
	
	//	for(int i = 0;i<12000000;i++); // delay
	}
}
