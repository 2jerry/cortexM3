#include <stdio.h>
#include <stdlib.h>

#include "init.h"
#include "led.h"
#include "fnd.h"


void TIMER0_IRQHandler(void);
void EINT0_IRQHandler(void);

int joystic[5] = {(1<<24), (1<<26), (1<<23), (1<<25), (1<<20) }; // 상 하 좌 우 선택

int ans[7] ={0}; // 정답 배열
int ans_num = 1;

int direction = 0; // joystic 방향
int t_flag = 0; // 타이머 인터럽트 flag
int n_flag = 0;
int lev = 1; // 레벨
int score = 0; // 점수


int clk_cnt = 0;

void control_joystic()
{
	if(!(FIO1PIN & joystic[3])) // 조이스틱 오른쪽
	{
		delay(0.1); 
		direction++;
	}
	if(!(FIO1PIN & joystic[2])) // 조이스틱 왼쪽
	{
		delay(0.1); 
		direction--;
	}
	
	led_onoff(ON,direction%8);
	delay(0.3);
	led_onoff(OFF,direction%8);
}

void make_quiz()
{
	if (lev %2 ==0) // 짝수 레벨 (2,4)
	{
		ans_num += 2;
	}
	else
	{
		ans_num = lev +2;
			
	}
	
	for(int i = 0;i<ans_num;i++)
	{
		int num;	
		num = rand() % 7;
		ans[num]++; // led  number 0~7
		delay(0.5);
		led_onoff(ON,num);
		delay(0.5);
		led_onoff(OFF,num);
	}
}

void check_ans(int ans[])
{
	
		int cnt = 0;
		for(int i = 0;i<8;i++)
		{
			if(ans[i] != 0) break;
			cnt ++;
		}
		if (cnt  == 7) // array all zero
		{	
			led_all(ON); // success
			delay(1);
			score += lev*10;
			led_all(OFF); // success
			lev++;
			t_flag = 0;
			direction = 0;
			clk_cnt = 0;

		}
		else
		{
			led_all(OFF); // success
			delay(1);
			t_flag = -1;
			direction = -1;
		}
	
}



int main()
{
	ISR_init();
	led_init();
	FND_init();
	ans[0] = 0;	 
	
	while(1)
	{
		display(score); 
	}
	{
		if(n_flag)
			
		if(t_flag)
		{	
			check_ans(ans);
			t_flag = 0;
			n_flag = 2; // 다음 단계
		}
		if(n_flag == 2)
		{	
			make_quiz();
			n_flag = 0;
		}
	}
	
	while(lev<=5)
	{
		//timer_init(); 
		make_quiz();
	
	
		
		for(int i = 0;i<1000;i++)
		{
			display(score); 
		}
	  
		
		
	}
}

void TIMER0_IRQHandler(void)
{
	T0IR |= 0; // interrupt flag clear
	T0TC = 0; // 카운트 값 clear
	//led_blink(1);
	
	t_flag = 1;
	
}


void EINT0_IRQHandler(void)
{
	EXTINT |= (1<<0); // 0번 인터럽트 사용
	led_blink(direction % 8);
	ans[direction % 8]--;
	clk_cnt++;
	
	control_joystic();
	if(clk_cnt == ans_num)
		n_flag = 1;
}