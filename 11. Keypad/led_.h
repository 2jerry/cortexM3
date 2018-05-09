#define ON 1
#define OFF 0
#define ALL 8
#define MAX 0xFFF

// LED 1~8��
int led[8] = { (1<<28), (1<<29), (1<<31), (1<<2), (1<<3), (1<<4), (1<<5),(1<<6) };

// led �ʱ�ȭ �Լ�
void led_Init()
{
	FIO1DIR |= (led[0] | led[1] | led[2]); // led�� ���(ouput���� ����)
	FIO2DIR |= (led[3] | led[4] | led[5] | led[6] | led[7]);
}

// led ���� �Լ�
void led_onoff(int value,int num)
{
   if(value) // ON
   {
      if(num>3)
         FIO2SET |= led[num-1];
      else
         FIO1SET |= led[num-1];
   }      
   else // OFF
   {
      if(num>3)
         FIO2CLR |= led[num-1];
      else
         FIO1CLR |= led[num-1];
   }
}