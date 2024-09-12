#include "motor.h"

void Motor_Init(void)
{
//CLK-ENABLE PC
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);

//PF6,PF7,PF8,PF9
GPIO_InitTypeDef  GPIO_InitStruct;
GPIO_InitStruct.GPIO_Mode   =GPIO_Mode_OUT;
GPIO_InitStruct.GPIO_OType  =GPIO_OType_PP;
GPIO_InitStruct.GPIO_Pin    =GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
GPIO_InitStruct.GPIO_PuPd   =GPIO_PuPd_NOPULL;
GPIO_InitStruct.GPIO_Speed  =GPIO_Speed_50MHz;
GPIO_Init(GPIOC, &GPIO_InitStruct);
}


int m=80;

//配置电机电平
uint8_t value;
static void Set_La(uint8_t value)
{
	if(value==1)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_6);
	}
	else
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_6);
	}
}
static void Set_Lb(uint8_t value)
{
	if(value==1)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_7);
	}
	else
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_7);
	}

}
static void Set_Ra(uint8_t value)
{
	if(value==1)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_8);
	}
	else
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	}	
}
static void Set_Rb(uint8_t value)
	{
	if(value==1)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_9);
	}
	else
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	}

	}
//小车前进
void Go_Up(void)
{
	Set_La(1);
	Delay_ms(65);
	Set_La(0);
	Delay_ms(35);
	
	Set_Lb(0);
	
	Set_Ra(1);
	Delay_ms(45);
	Set_Ra(0);
	Delay_ms(55);
	Set_Rb(0);
}
//小车后退
void Go_Back(void)
{
	Set_La(0);
	
	Set_Lb(1);
	Delay_ms(65);
	Set_Lb(0);
	Delay_ms(35);
	
	Set_Ra(0);
	Set_Rb(1);
	Delay_ms(45);
	Set_Rb(0);
	Delay_ms(55);
}
//小车停止
void Stop(void)
{
	Set_La(0);
	Set_Lb(0);
	Set_Ra(0);
	Set_Rb(0);
}

//小车右转
void Go_Right(void)
{
Set_La(1);
Delay_ms(65);
Set_La(0);
Delay_ms(35);

Set_Lb(0);

Set_Ra(0);
Set_Rb(1);
Delay_ms(m);
Set_Rb(0);
Delay_ms(100-m);
}
//小车左转
void Go_Left(void)
{
Set_Ra(1);
Set_Rb(0);

Set_La(0);
Set_Lb(1);
Delay_ms(m);
Set_Lb(0);
Delay_ms(100-m);
}


