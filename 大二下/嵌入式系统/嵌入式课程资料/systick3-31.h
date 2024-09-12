#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "stm32f4xx.h"

#define rSysTickCtrl 		*((volatile unsigned long*)0xE000E010)
#define rSysTickLoad 		*((volatile unsigned long*)0xE000E014)
#define rSysTickVal 		*((volatile unsigned long*)0xE000E018)

void systick_cfg(uint32_t);
void Delay_ms(uint32_t);
void Delay_us(uint32_t);

#endif
