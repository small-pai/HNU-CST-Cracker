#ifndef __LED_H__
#define __LED_H__
//include
//define
//func



#define rRCCAHB1CLKEN  *((volatile unsigned long *)0x40023830) 	
#define GPIOE_BASE_ADDR  		0x40021000
#define GPIOF_BASE_ADDR  		0x40021400

#define MODER_OFFSET_ADDR 	0x00
#define OTYPER_OFFSET_ADDR	0x04
#define OSPEEDR_OFFSET_ADDR	0x08
#define PUPDR_OFFSET_ADDR		0x0C
#define BSRR_OFFSET_ADDR		0x18

#define rGPIOF_MODER   			(*(volatile unsigned long*)(GPIOF_BASE_ADDR+MODER_OFFSET_ADDR))
#define rGPIOF_OTYPER   		(*(volatile unsigned long*)(GPIOF_BASE_ADDR+OTYPER_OFFSET_ADDR))	
#define rGPIOF_OSPEEDR		 	(*(volatile unsigned long*)(GPIOF_BASE_ADDR+OSPEEDR_OFFSET_ADDR))
#define rGPIOF_PUPDR				(*(volatile unsigned long*)(GPIOF_BASE_ADDR+PUPDR_OFFSET_ADDR))
#define rGPIOF_BSRR  				(*(volatile unsigned long*)(GPIOF_BASE_ADDR+BSRR_OFFSET_ADDR))

#define rGPIOE_MODER   			(*(volatile unsigned long*)(GPIOE_BASE_ADDR+MODER_OFFSET_ADDR))
#define rGPIOE_OTYPER   		(*(volatile unsigned long*)(GPIOE_BASE_ADDR+OTYPER_OFFSET_ADDR))	
#define rGPIOE_OSPEEDR		 	(*(volatile unsigned long*)(GPIOE_BASE_ADDR+OSPEEDR_OFFSET_ADDR))
#define rGPIOE_PUPDR				(*(volatile unsigned long*)(GPIOE_BASE_ADDR+PUPDR_OFFSET_ADDR))
#define rGPIOE_BSRR  				(*(volatile unsigned long*)(GPIOE_BASE_ADDR+BSRR_OFFSET_ADDR))
	
enum LED_NUM{LED1,LED2,LED3,LED4};

void led_init(void);
void led_ctrl( int led_num);
void delay(int num);

#endif
