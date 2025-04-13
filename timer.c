/*
 * timer.c
 *
 *  Created on: Feb 2, 2025
 *      Author: khans
 */

#include "timer.h"
#include "armcortexm4.h"

static void timerxClockEnable(Timer_RegDef_t* selectTimer)
{
	if(selectTimer == TIMER1)
		 TIMER1_CLOCK_ENABLE();
	else if(selectTimer == TIMER2)
		TIMER2_CLOCK_ENABLE();
	else if(selectTimer == TIMER3)
		TIMER3_CLOCK_ENABLE();
	else if(selectTimer == TIMER4)
		TIMER4_CLOCK_ENABLE();
	else if(selectTimer == TIMER5)
		TIMER5_CLOCK_ENABLE();
	else if(selectTimer == TIMER6)
		TIMER6_CLOCK_ENABLE();
	else if(selectTimer == TIMER7)
		TIMER7_CLOCK_ENABLE();
	else if(selectTimer == TIMER8)
		TIMER8_CLOCK_ENABLE();
	else if(selectTimer == TIMER9)
		TIMER9_CLOCK_ENABLE();
	else if(selectTimer == TIMER10)
		TIMER10_CLOCK_ENABLE();
	else if(selectTimer == TIMER11)
		TIMER11_CLOCK_ENABLE();
	else if(selectTimer == TIMER12)
		TIMER12_CLOCK_ENABLE();
	else if(selectTimer == TIMER13)
		TIMER13_CLOCK_ENABLE();
	else if(selectTimer == TIMER14)
		TIMER14_CLOCK_ENABLE();

}

void timerxPeripheralEnable(Timer_RegDef_t* selectTimer)
{
		if(selectTimer == TIMER1)
			 TIMER1_PERIPHERAL_ENABLE();
		else if(selectTimer == TIMER2)
			TIMER2_PERIPHERAL_ENABLE();
		else if(selectTimer == TIMER3)
			TIMER3_PERIPHERAL_ENABLE();
		else if(selectTimer == TIMER4)
			TIMER4_PERIPHERAL_ENABLE();
		else if(selectTimer == TIMER5)
			TIMER5_PERIPHERAL_ENABLE();
		else if(selectTimer == TIMER6)
			TIMER6_PERIPHERAL_ENABLE();
		else if(selectTimer == TIMER7)
			TIMER7_PERIPHERAL_ENABLE();
		else if(selectTimer == TIMER8)
			TIMER8_PERIPHERAL_ENABLE();
		else if(selectTimer == TIMER9)
			TIMER9_PERIPHERAL_ENABLE();
		else if(selectTimer == TIMER10)
			TIMER10_PERIPHERAL_ENABLE();
		else if(selectTimer == TIMER11)
			TIMER11_PERIPHERAL_ENABLE();
		else if(selectTimer == TIMER12)
			TIMER12_PERIPHERAL_ENABLE();
		else if(selectTimer == TIMER13)
			TIMER13_PERIPHERAL_ENABLE();
		else if(selectTimer == TIMER14)
			TIMER14_PERIPHERAL_ENABLE();
}
void timerxConfig(Timer_RegDef_t* selectTimer,uint16_t prescaler, uint32_t autoReload )
{
	timerxClockEnable(selectTimer);
	selectTimer->TIMx_PSC = prescaler - 1;
	selectTimer->TIMx_ARR = autoReload - 1;
	selectTimer->TIMx_EGR |= (1 << 0);
}
void timerxCaptureEnable(Timer_RegDef_t* selectTimer, CC_Channel_e channel, CC_Mode_e mode, CC_Edge_Selection_e edge )
{
	switch(channel)
	{
				case CC1_CH1: selectTimer->TIMx_CCMR1 |= (mode << 0);
							  selectTimer->TIMx_CCER  |= (edge << 1);
							  selectTimer->TIMx_CCER  |= (1u << 0);    break;
				case CC2_CH2: selectTimer->TIMx_CCMR1 |= (mode << 8);
							  selectTimer->TIMx_CCER  |= (edge << 5);
							  selectTimer->TIMx_CCER  |= (1u << 4);    break;
				case CC3_CH3: selectTimer->TIMx_CCMR2 |= (mode << 0);
							  selectTimer->TIMx_CCER  |= (edge << 9);
							  selectTimer->TIMx_CCER  |= (1u << 8);    break;
				case CC4_CH4: selectTimer->TIMx_CCMR2 |= (mode << 8);
							  selectTimer->TIMx_CCER  |= (edge << 13);
							  selectTimer->TIMx_CCER  |= (1u << 12);   break;
				default: break;
	}

	//selectTimer->TIMx_CCMR2 |= (0b01 << 8);  // TI2  capture input
	//selectTimer->TIMx_CCER &= ~(1u << 5); // Ensure CC2P = 0 (rising edge capture)
	//selectTimer->TIMx_CCER  |= (1u << 4);	//enable capture
}
void timer3PwmEnable(uint32_t dutyCycle)
{
	TIMER3_PWM_MODE_1();
	TIMER3->TIMx_CCR1 = dutyCycle;
	TIMER3_PRELOAD_ENABLE();
	TIMER3_RELOAD_ENABLE();
	TIMER3_UPDATE_GEN_ENABLE();
	TIMER3_PWM_ENABLE();
}
void timer2InterruptEnable()
{
	TIMER2_INTERRUPT_ENABLE();
	nvicInterruptEnable(IRQN_TIM2);

}
void timer3InterruptEnable()
{
	TIMER3_INTERRUPT_ENABLE();
	nvicInterruptEnable(IRQN_TIM3);

}
void timer4InterruptEnable()
{
	TIMER4_INTERRUPT_ENABLE();
	nvicInterruptEnable(IRQN_TIM4);

}
void timer5InterruptEnable()
{
	TIMER5_INTERRUPT_CC2_ENABLE();
	nvicInterruptEnable(IRQN_TIM5);

}
