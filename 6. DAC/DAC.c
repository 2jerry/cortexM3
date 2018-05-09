
#define PCLKSEL0 (*(volatile int *)0x400FC1A8) // Peripheral Clock Selection register
#define PINSEL1  (*(volatile int *)0x4002C004) // Pin Function Select register
	
#define DACR 	 (*(volatile int *)0x4008C000) // D/A Converter Register


void init_DAC()
{
	PCLKSEL0 |= (1<<22) + (1<<23); // Set clock
	PINSEL1 |= (0<<20) + (1<<21); // Set pin function to AOUT (speaker GPIO 0.26 )
	DACR |= (0<<16); // Set DAC conversion speed 1Mhz
}

int main()
{
	int value,a,tmp;
	float rate = 0.0;
	
	init_DAC();
	while(1)
	{
		  // 0~1024 까지의 랜덤한 값을 넣어 스피커로 소리를 출력한다.
			for(value = 0; value < 1024; value++)
			{
        a = value * rate;
				tmp = DACR & (0<<16);
				tmp |= (a & 0x3FF) << 6; // 0x3FF : Value bit(6~15bit)
				DACR = tmp;
			}
			
	   rate += 0.2;		
     if(rate == 2)
        rate = 0.0;		
	}

	
	return 0;
}