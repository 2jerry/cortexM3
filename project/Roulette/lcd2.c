#include "lcd.h"
#include <math.h>
#define PI 3.14

void draw_circle(int x,int y,int r)
{
	int i,j;
	for( i = 0;i<WIDTH;i++)
	{
		for(j = 0;j<HEIGHT;j++)
		{
			int v = i-x;
			int w = j-y;
			if((r*r) > v*v+w*w)
					LCD_PutPixel(i,j,0xFB0A);
		}
	}
}

void part_Circle(int x,int y,int r,double theta,unsigned int color)
{
	int i,j;
	for( i = 0;i<WIDTH;i++)
	{
		for(j = 0;j<HEIGHT;j++)
		{		
			if(((r*r) > i*i+j*j))
			{
				int x_ = i*cos((PI*theta)/180)+j*sin((PI*theta)/180);
				int y_ = -i*sin((PI*theta)/180)+j*cos((PI*theta)/180);
				
					LCD_PutPixel(x_+x,y+y_,color);
			}
		}
	}
}

int main()
{
	LCD_Init();  // LCD √ ±‚»≠
	LCD_clear();
//	part_Circle(190,120,100,90,RED);
//	part_Circle(190,120,100,180,GREEN);
//	part_Circle(190,120,100,270,BLUE);
//	part_Circle(190,120,100,360,RED+GREEN);
	//draw_circle(190,120,100);
	LCD_displayString(20,"Hello World");
}
