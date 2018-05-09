
void EXT_IO_C_Init()
{
	/* P0.4 는 확장보드를 input or output 을 결정한다. */
	/* 확장보드 A -> P0.19 (low = output, high = input) *
	 * 확장보드 B -> P0.20 (low = output, high = input) *
	 * 확장보드 C -> P0.21 (low = output, high = input) */

	
	FIO0DIR |= (1<<4)|(1<<19)|(1<<20) | (1<<21) ; // 확장보드 C input으로 설정
	FIO1DIR |= (1<<21);
	FIO2DIR |= (1<<11);
}

void Keypad_DIR_Output()
{
	// output 설정
	FIO0DIR |= (1<<5);
FIO0DIR |= (1<<10);
	FIO2DIR |= (1<<12);
	FIO2DIR |= (1<<13);
}

void Keypad_DIR_Input()
{
	FIO0PIN |= (1<<4);
	FIO0DIR &= ~(1<<23);
	FIO0DIR &= ~(1<<24);
	FIO3DIR &= ~(1<<25);
	FIO3DIR &= ~(1<<26);
}

void check_ROW1()
{
	Keypad_DIR_Output();
	FIO0PIN &=  ~(1<<5);
	FIO0PIN |= (1<<10);
	FIO2PIN |= (1<<12);
	FIO2PIN |= (1<<13);

	FIO2PIN |= (1<<11); // CS Clock High Edge
	FIO2PIN &= ~(1<<11);
}

void check_ROW2()
{
	Keypad_DIR_Output();
	FIO0PIN |=  (1<<5);
	FIO0PIN &= ~(1<<10);
	FIO2PIN |= (1<<12);
	FIO2PIN |= (1<<13);

	FIO2PIN |= (1<<11); // CS Clock High Edge
	FIO2PIN &= ~(1<<11);	
}

void check_ROW3()
{
	Keypad_DIR_Output();
	FIO0PIN |=  (1<<5);
	FIO0PIN |= (1<<10);
	FIO2PIN &= ~(1<<12);
	FIO2PIN |= (1<<13);

	FIO2PIN |= (1<<11); // CS Clock High Edge
	FIO2PIN &= ~(1<<11);	
}
void check_ROW4()
{
	Keypad_DIR_Output();
	FIO0PIN |=  (1<<5);
	FIO0PIN |= (1<<10);
	FIO2PIN |= (1<<12);
	FIO2PIN &= ~(1<<13);

	FIO2PIN |= (1<<11); // CS Clock High Edge
	FIO2PIN &= ~(1<<11);	
}
int keypad_input(int num)
{
	int flag = 0;
	FIO1PIN &= ~(1<<21);  
	
	if(num == 1)
	{
		if(!(FIO0PIN & (1<<23)))  	flag = 1;
	}
	if(num == 2)
	{
		if(!(FIO0PIN & (1<<24)))  	flag = 1;
	}
	if(num == 3)
	{
		if(!(FIO3PIN & (1<<25)))  	flag = 1;
	}
	if(num == 4)
	{
		if(!(FIO3PIN & (1<<26)))  flag = 1;
	}

	FIO1PIN |= (1<<21);  
	return flag;
}

int keypad()
{
	int flag=0,temp = 0;
	FIO0PIN |= (1<<19); // 확장보드 PORT 2번 사용
	FIO0PIN |= (1<<20); // 확장보드 PORT 2번 사용
	FIO0PIN &= ~(1<<21); // 확장보드 PORT 2번 사용
	

	check_ROW1();
	temp = keypad_input(1);
	if (temp == 1) flag = 3; 
	temp = keypad_input(2);
	if (temp == 1) flag = 2;
	temp = keypad_input(3);
	if (temp == 1) flag = 1;
	temp = keypad_input(4);
	if (temp == 1) flag = 0;
	
	check_ROW2();
	temp = keypad_input(1);
	if (temp == 1) flag = 7; 
	temp = keypad_input(2);
	if (temp == 1) flag = 6;
	temp = keypad_input(3);
	if (temp == 1) flag = 5;
	temp = keypad_input(4);
	if (temp == 1) flag = 4;
	
	check_ROW1();
	temp = keypad_input(1);
	if (temp == 1) flag = 11; 
	temp = keypad_input(2);
	if (temp == 1) flag = 10;
	temp = keypad_input(3);
	if (temp == 1) flag = 9;
	temp = keypad_input(4);
	if (temp == 1) flag = 8;
	
	check_ROW4();
	temp = keypad_input(1);
	if (temp == 1) flag = 15; 
	temp = keypad_input(2);
	if (temp == 1) flag = 14;
	temp = keypad_input(3);
	if (temp == 1) flag = 13;
	temp = keypad_input(4);
	if (temp == 1) flag = 12;
	
	return flag;
}

