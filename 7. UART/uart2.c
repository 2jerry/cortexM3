#define PCONP 	 (*(volatile int *)0x400FC0C4) // UART0 = bit 3
#define PCLKSEL0 (*(volatile int *)0x400FC1A8) // bit 6,7
#define PINSEL0  (*(volatile int *)0x4002C000) // bit 2,3 AF 01

#define U0LCR  	(*(volatile int *)0x4000C00C) // UART Line Control Register 7�� bit 1����
#define U0FCR  	(*(volatile int *)0x4000C008) // UART FIFO Control Register 0�� bit 1�� ���� (FIFO enable)
#define U0LSR	  (*(volatile int *)0x4000C014) // receive register ������ ������ 1
#define U0RBR	  (*(volatile int *)0x4000C000) // receive register 0~7 bit�ȿ� ���� ������ ����
#define U0THR	  (*(volatile int *)0x4000C000) // transmitter holding register ���� ������ ����
#define U0DLL   (*(volatile int *)0x4000C000) // baudrate register
#define U0DLM   (*(volatile int *)0x4000C004) // baudrate register
#define U0FDR 	(*(volatile int *)0x4000C028) // baudrate register

#include <string.h>
#include "led.h" // led ���� ��� �Լ� ����

void set_Baudrate(int baudrate)
{
	int div,high,low;
	
	div = 12000000/(16*baudrate*1.5);
	low = div & 0x000000ff; // ���� 8��Ʈ ����
	high = div & 0x0000ff00; // ���� 8��Ʈ ����
	high = high >> 8;
	U0LCR |= (1 << 7); // DLAB = 1
	U0DLL = low; 
	U0DLM = high;
	U0FDR = (8 << 4) | 5; // MULVAL = 8 , DIVADDVAL = 5
	U0LCR &= ~(0x00000080); // DLAB = 0
}
void UART0_Init()
{
	set_Baudrate(115200);
	PCONP |= (1<<3); // reset ���� enable �Ǿ��ִ�.
	PINSEL0 |= (1<<4) | (1<<6); // tx bit + rx bit ,AF 01
	PCLKSEL0 |= (1<<6) | (1<<7); 
	U0FCR |= (1<<0) | (1<<1) | (1<<2); // FIFO enable
	U0LCR |= (1<<0) | (1<<1);// Data 8 bit
}

void Uart_Tx_char(char c)
{
	// ������ �����Ͱ� ���� �� ���� ��ٸ���.
	while(!(U0LSR & 0x00000020)); 
	U0THR = c; // ���� �����͸� THR �������Ϳ� ���� �� ������.
}

void Uart_Tx_string(char *s)
{
	int idx = 0;
	while(s[idx] != 0)
	{
		Uart_Tx_char(s[idx]); // �� ���ھ� ������.
		idx++;
	}
}

unsigned char Uart_Rx_char()
{
	return U0RBR; // ���� �����͸� ����
}

unsigned char Uart_Rx_String()
{
	
	return U0RBR; // ���� �����͸� ����
}

int main()
{
	unsigned char c;
	unsigned char buffer[128];
	int cnt = 0;
	int num = 0;
	
	led_Init(); // led �ʱ�ȭ
	UART0_Init(); // UART0 �ʱ�ȭ
	//Uart_Tx_char('A');
	Uart_Tx_string("LED Control program\r\n");
	
	while(1)
	{
		c = Uart_Rx_char(); // �� ���ھ� �ޱ�
		if(c)
		{
			buffer[cnt] = c;
			Uart_Tx_char(c);
			if(buffer[cnt] == 0x0D) // ASCII 0x0D = Enter
			{
				if(!strcmp(buffer,"LED ALL ON\r"))
				{
					Uart_Tx_string("\r\n");
					led_all(ON); // �Է��� ������ ��ȣ�� led ON
				}
				else if (!strcmp(buffer,"LED ALL OFF\r"))
				{
					Uart_Tx_string("\r\n");
					led_all(OFF); // �Է��� ������ ��ȣ�� led ON
				}
				else
				{Uart_Tx_string("\r\n");
					Uart_Tx_string("Error\r\n");
				}
				cnt = 0;
			  memset(buffer,0x00,sizeof(buffer)); // ���� �ʱ�ȭ
			}			
			else
			cnt++;
		}
	}
}














