#include <string.h>

void set_Baudrate(int baudrate)
{
	int div,high,low;
	
	div = 12000000/(16*baudrate*1.5);
	low = div & 0x000000ff; // 하위 8비트 검출
	high = div & 0x0000ff00; // 상위 8비트 검출
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
	PCONP |= (1<<3); // reset 값이 enable 되어있다.
	PINSEL0 |= (1<<4) | (1<<6); // tx bit + rx bit ,AF 01
	PCLKSEL0 |= (1<<6) | (1<<7); 
	U0FCR |= (1<<0) | (1<<1) | (1<<2); // FIFO enable
	U0LCR |= (1<<0) | (1<<1);// Data 8 bit
}

void Uart_Tx_char(char c)
{
	// 보내는 데이터가 없을 때 까지 기다린다.
	while(!(U0LSR & 0x00000020)); 
	U0THR = c; // 보낼 데이터를 THR 레지스터에 저장 후 보낸다.
}

void Uart_Tx_string(char *s)
{
	int idx = 0;
	while(s[idx] != 0)
	{
		Uart_Tx_char(s[idx]); // 한 글자씩 보낸다.
		idx++;
	}
}

unsigned char Uart_Rx_char()
{
	return U0RBR; // 받은 데이터를 전송
}

unsigned char Uart_Rx_String()
{
	
	return U0RBR; // 받은 데이터를 전송
}

int main()
{
	unsigned char c;
	unsigned char buffer[10];
	int cnt = 0;
	int num = 0;
	
	//led_Init(); // led 초기화
	UART0_Init(); // UART0 초기화
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
				//led_onoff(ON,buffer[0]-'0'); // 입력한 숫자의 번호의 led ON
				cnt = 0;
			    memset(buffer,0x00,sizeof(buffer)); // 버퍼 초기화
			}			
			else
			cnt++;
		}
	}
}





