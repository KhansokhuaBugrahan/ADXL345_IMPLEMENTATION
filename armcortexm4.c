/*
 * armcortexm4.c
 *
 *  Created on: Dec 1, 2024
 *      Author: khans
 */

#include "armcortexm4.h"


void fpuInit(void)
{
	  CPACR();
}


volatile uint32_t sysTickCounter = 0;
void nvicInterruptEnable(IRQ_NUMBER_e position)
{
	if(position >= 0 && position < 32)
		NVIC_ISER->NVIC_ISER0 |= (1u << position);

	else if(position >= 32 && position < 64)
		NVIC_ISER->NVIC_ISER1 |= (1u << (position % 32));

	else if(position >= 64 && position < 96)   		// STM407G 82 adet kesme desteklediği için bu kadar
		NVIC_ISER->NVIC_ISER2 |= (1u << (position % 32));

}
void nvicInterruptDisable(IRQ_NUMBER_e position) // use direct assignment for disabling interrupts
{
	if(position >= 0 && position < 32)
		NVIC_ICER->NVIC_ICER0 = (1u << position);

	else if(position >= 32 && position < 64)
		NVIC_ICER->NVIC_ICER1 = (1u << (position % 32));

	else if(position >= 64 && position < 96)   		// STM407G 82 adet kesme desteklediği için bu kadar
		NVIC_ICER->NVIC_ICER2 = (1u << (position % 32));
}
void sysTickInit(void)
{
	 SYSTICK_ENABLE();
	 SYSTICK_EXCEPTION_ENABLE();
	 SYSTICK_CLOCK_INTERNAL();
	 SYSTICK_SET_EACH_1MS_INTERRUPT();
	 SYSTICK_RESET_CURR_VALUE();

}
void SysTick_Handler(void)
{
	sysTickCounter++;
}
uint32_t getTick(void)
{
	return sysTickCounter;
}
void delay_ms(uint32_t delay) // örnek 100 ms için
{
	uint32_t tickStart = getTick(); // get current val
	uint32_t currentVal;
	while(((currentVal = getTick()) - tickStart) < delay)
	{
		// 2 adet unsigned sayının farkı negatif ise 2^n+1 kadarını çıkan sonuca ekle
	}
	int a = 56;
	a++;
}				  							// n = 32;



