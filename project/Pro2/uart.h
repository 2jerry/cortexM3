#include <string.h>

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
	unsigned char buffer[10];
	int cnt = 0;
	int num = 0;
	
	//led_Init(); // led �ʱ�ȭ
	UART0_Init(); // UART0 �ʱ�ȭ
	//Uart_Tx_char('A');
	Uart_Tx_string("Input LED number (1~8)\r\n");
	
	while(1)
	{
		c = Uart_Rx_char();
		if(c)
		{
			buffer[cnt] = c;
			Uart_Tx_char(c);
			if(buffer[cnt] == 0x0D) // ASCII 0x0D = Enter
			{
				Uart_Tx_string("\r\n");
				//led_onoff(ON,buffer[0]-'0'); // �Է��� ������ ��ȣ�� led ON
				cnt = 0;
			    memset(buffer,0x00,sizeof(buffer)); // ���� �ʱ�ȭ
			}			
			else
			cnt++;
		}
	}
}





