#include "track.h"

void Track_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
		
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode   =GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin    =GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStruct.GPIO_PuPd   =GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed  =GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}


uint8_t left=0;
uint8_t right=0;

void Track_Auto(void)
{
left=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1);
right=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2);
//WHITE---0 BLACK---1

	if(left==WHITE&&right==WHITE)
	{
			Go_Up();
	}

	if(left==BLACK&&right==BLACK)
		{
				Stop();
		}

	if(left==WHITE&&right==BLACK)
	{
			Go_Right();
	}

	if(left==BLACK&&right==WHITE)
	{
			Go_Left();
	}

}
