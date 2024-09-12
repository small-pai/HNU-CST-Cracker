#include "r_led.h"

void led_init(void)
{
	unsigned long r_value;
//使能GPIOE GPIOF这两组的时钟
//rRCCAHB1CLKEN[4]--GPIOE rRCCAHB1CLKEN[5]--GPIOF
	rRCCAHB1CLKEN	|= (1<<4)|(1<<5);
	
//PF9,PF10-->输出模式 
//[21:18] 0101
	r_value=rGPIOF_MODER;
	r_value &=~(0xf<<18);
	r_value |=(1<<18)|(1<<20);	
	rGPIOF_MODER=r_value;
	
//PE13,PE14-->输出模式 
//[29:26] 0101
	r_value=rGPIOE_MODER;
	r_value &=~(0xf<<26);
	r_value |=(1<<26)|(1<<28);
	rGPIOE_MODER=r_value;
	
//PF9,PF10-->输出推挽 0
//[10:9] 00
	r_value=rGPIOF_OTYPER;
	r_value	&=~((1<<9)|(1<<10));
	rGPIOF_OTYPER=r_value;
	
//PE13,PE14-->输出推挽 0
	//[14:13] 00
	r_value=rGPIOE_OTYPER;
	r_value	&=~((1<<13)|(1<<14));
	rGPIOE_OTYPER=r_value;
	
//PF9,PF10-->速率50MHZ 10
//[21:18] 1010
	r_value=rGPIOF_OSPEEDR;
	r_value &=~(0xf<<18);//****0000******
	r_value |=(1<<19)|(1<<21);
	rGPIOF_OSPEEDR=r_value;

//PE13,PE14-->速率50MHZ 10
//[29:26] 1010
	r_value=rGPIOE_OSPEEDR;
	r_value &=~(0xf<<26);
	r_value |=(1<<29)|(1<<27);
	rGPIOE_OSPEEDR=r_value;
	
//PF9,PF10-->无上拉无下拉 00
//[21:18] 0000
	r_value=rGPIOF_PUPDR;
	r_value &=~(0xf<<18);
	rGPIOF_PUPDR=r_value;
	
//PE13,PE14-->无上拉无下拉 00
//[29:26] 0000
	r_value=rGPIOE_PUPDR;
	r_value &=~(0xf<<26);
	rGPIOE_PUPDR=r_value;
	
//LED1 LED2熄灭-->PF9,PF10-->BSRR(1)
//[10:9] 11
	r_value=rGPIOF_BSRR;
	r_value	|=(1<<9)|(1<<10);
	rGPIOF_BSRR=r_value;
	
//LED3 LED4熄灭-->PE13,PE14-->BSRR(1)
//[14:13] 11
	r_value=rGPIOE_BSRR;
	r_value	|=(1<<13)|(1<<14);
	rGPIOE_BSRR=r_value;	
}

void led_ctrl( int led_num)
{
	unsigned long r_value;
	switch(led_num)
	{
		case LED1:
		{
			r_value=rGPIOF_BSRR;
			//PF9--0,PF10--1
			r_value	|=(1<<25)|(1<<10);
			rGPIOF_BSRR=r_value;
			
			r_value=rGPIOE_BSRR;
			//PE13--1,PE14--1
			r_value	|=(1<<13)|(1<<14);
			rGPIOE_BSRR=r_value;	
			break;
		}
		
		case LED2:
		{
			r_value=rGPIOF_BSRR;
			//PF9--1,PF10--0
			r_value	|=(1<<9)|(1<<26);
			rGPIOF_BSRR=r_value;
			
			r_value=rGPIOE_BSRR;
			//PE13--1,PE14--1
			r_value	|=(1<<13)|(1<<14);
			rGPIOE_BSRR=r_value;	
			break;
		}
		
		case LED3:
		{
			r_value=rGPIOF_BSRR;
			//PF9--1,PF10--1
			r_value	|=(1<<9)|(1<<10);			
			rGPIOF_BSRR=r_value;
			
			r_value=rGPIOE_BSRR;
			//PE13--0,PE14--1
			r_value	|=(1<<29)|(1<<14);
			rGPIOE_BSRR=r_value;	
			break;
		}
		
		case LED4:
		{
			r_value=rGPIOF_BSRR;
			//PF9--1,PF10--1
			r_value	|=(1<<9)|(1<<10);			
			rGPIOF_BSRR=r_value;
			
			r_value=rGPIOE_BSRR;
			//PE13--1,PE14--0
			r_value	|=(1<<13)|(1<<30);
			rGPIOE_BSRR=r_value;	
			break;
		}
		
		default:
			break;				
	}
}

void delay(int num)
{
		while(num--);
}

int main()
{
	
	led_init();	
	
	while(1)
	{
		for(int led_n=LED1;led_n<=LED4;led_n++)
		{
				led_ctrl(led_n);
				delay(0x666666);
		}
	}
	
	
}
