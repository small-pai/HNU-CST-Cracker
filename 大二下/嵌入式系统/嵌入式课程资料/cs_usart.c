#include"cs_usart.h"
//usart1-tx-PA9 rx-PA10
void usart_init(void)
{
//0.clk-enable PA-AHB1 USART1-APB2
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
//1.GPIO AF 50M NOUPDN
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode	=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Pin	=GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStruct.GPIO_PuPd	=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed	=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin	=GPIO_Pin_10|GPIO_Pin_11;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	//PA9,10-AF-USART1
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10,GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11,GPIO_AF_USART3);
//2.USART INIT
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate					=9600;
	USART_InitStruct.USART_HardwareFlowControl		=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode						=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity					=USART_Parity_No;
	USART_InitStruct.USART_StopBits					=USART_StopBits_1;
	USART_InitStruct.USART_WordLength				=USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStruct);
	USART_Init(USART3, &USART_InitStruct);
//3.USART-IT
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
//4.NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//2 bits for pre-emption priority 0-3
												   //2 bits for subpriority 0-3

	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel							=USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd						=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority		=2;//0-3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority				=2;//0-3
	NVIC_Init(&NVIC_InitStruct);
	NVIC_InitStruct.NVIC_IRQChannel							=USART3_IRQn;
	NVIC_Init(&NVIC_InitStruct);
//5.USART-CMD
	USART_Cmd(USART1, ENABLE);
	USART_Cmd(USART3, ENABLE);

}

uint8_t recv_byte=0;
void USART1_IRQHandler(void)
{
	if(SET==USART_GetITStatus(USART1, USART_IT_RXNE))
		{
			recv_byte=USART_ReceiveData(USART1)&(uint8_t)0xff;
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		}
}

void USART3_IRQHandler(void)
{
	if(SET==USART_GetITStatus(USART3, USART_IT_RXNE))
		{
			recv_byte=USART_ReceiveData(USART3)&(uint8_t)0xff;
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
		}
}
int fputc(int c, FILE *stream)
{
	USART1->SR;
	USART_SendData(USART1, c & 0xff);
	while( USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);	
	return(c);
}



