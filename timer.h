/*
 * timer.h
 *
 *  Created on: Feb 2, 2025
 *      Author: khans
 */

#ifndef TIMER_H_
#define TIMER_H_
#include <stm32f4xx.h>
#include "armcortexm4.h"

#define			DUTY_CYCLE_0			0
#define			DUTY_CYCLE_10			10
#define			DUTY_CYCLE_20			20
#define			DUTY_CYCLE_30			30
#define			DUTY_CYCLE_40			40
#define			DUTY_CYCLE_50			50
#define			DUTY_CYCLE_60			60
#define			DUTY_CYCLE_70			70
#define			DUTY_CYCLE_80			80
#define			DUTY_CYCLE_90			90
#define			DUTY_CYCLE_100			100


typedef enum {

	CCx_OUTPUT_COMPARE, CCx_CAPTURE_TI2, CCx_CAPTURE_TI1, CCx_CAPTURE_TRC

}CC_Mode_e;

typedef enum {

	CC1_CH1, CC2_CH2, CC3_CH3, CC4_CH4

}CC_Channel_e;

typedef enum {

	CCx_RISING = 0b000, CCx_FALLING = 0b001,  CCx_BOTH_EDGES = 0b101

}CC_Edge_Selection_e;

typedef struct {

	volatile uint32_t  TIMx_CR1;
	volatile uint32_t  TIMx_CR2;
	volatile uint32_t  TIMx_SMCR;
	volatile uint32_t  TIMx_DIER;
	volatile uint32_t  TIMx_SR;
	volatile uint32_t  TIMx_EGR;
	volatile uint32_t  TIMx_CCMR1;
	volatile uint32_t  TIMx_CCMR2;
	volatile uint32_t  TIMx_CCER;
	volatile uint32_t  TIMx_CNT;
	volatile uint32_t  TIMx_PSC;
	volatile uint32_t  TIMx_ARR;
	volatile uint32_t  TIMx_RCR;
	volatile uint32_t  TIMx_CCR1;
	volatile uint32_t  TIMx_CCR2;
	volatile uint32_t  TIMx_CCR3;
	volatile uint32_t  TIMx_CCR4;
	volatile uint32_t  TIMx_BDTR;
	volatile uint32_t  TIMx_DCR;
	volatile uint32_t  TIMx_DMAR;
	volatile uint32_t  TIMx_OR;

}Timer_RegDef_t;

#define 	TIMER1			((Timer_RegDef_t*)(TIM1_BASE_ADDR))
#define 	TIMER2			((Timer_RegDef_t*)(TIM2_BASE_ADDR))
#define 	TIMER3			((Timer_RegDef_t*)(TIM3_BASE_ADDR))
#define 	TIMER4			((Timer_RegDef_t*)(TIM4_BASE_ADDR))
#define 	TIMER5			((Timer_RegDef_t*)(TIM5_BASE_ADDR))
#define 	TIMER6			((Timer_RegDef_t*)(TIM6_BASE_ADDR))
#define 	TIMER7			((Timer_RegDef_t*)(TIM7_BASE_ADDR))
#define 	TIMER8			((Timer_RegDef_t*)(TIM8_BASE_ADDR))
#define 	TIMER9			((Timer_RegDef_t*)(TIM9_BASE_ADDR))
#define 	TIMER10			((Timer_RegDef_t*)(TIM10_BASE_ADDR))
#define 	TIMER11			((Timer_RegDef_t*)(TIM11_BASE_ADDR))
#define 	TIMER12			((Timer_RegDef_t*)(TIM12_BASE_ADDR))
#define 	TIMER13			((Timer_RegDef_t*)(TIM13_BASE_ADDR))
#define 	TIMER14			((Timer_RegDef_t*)(TIM14_BASE_ADDR))



#define		TIMER1_CLOCK_ENABLE()		(RCC->APB2ENR |= (1u << 0))
#define		TIMER2_CLOCK_ENABLE()		(RCC->APB1ENR |= (1u << 0))
#define		TIMER3_CLOCK_ENABLE()		(RCC->APB1ENR |= (1u << 1))
#define		TIMER4_CLOCK_ENABLE()		(RCC->APB1ENR |= (1u << 2))
#define		TIMER5_CLOCK_ENABLE()		(RCC->APB1ENR |= (1u << 3))
#define		TIMER6_CLOCK_ENABLE()		(RCC->APB1ENR |= (1u << 4))
#define		TIMER7_CLOCK_ENABLE()		(RCC->APB1ENR |= (1u << 5))
#define		TIMER8_CLOCK_ENABLE()		(RCC->APB2ENR |= (1u << 1))
#define		TIMER9_CLOCK_ENABLE()		(RCC->APB2ENR |= (1u << 16))
#define		TIMER10_CLOCK_ENABLE()		(RCC->APB2ENR |= (1u << 17))
#define		TIMER11_CLOCK_ENABLE()		(RCC->APB2ENR |= (1u << 18))
#define		TIMER12_CLOCK_ENABLE()		(RCC->APB1ENR |= (1u << 6))
#define		TIMER13_CLOCK_ENABLE()		(RCC->APB1ENR |= (1u << 7))
#define		TIMER14_CLOCK_ENABLE()		(RCC->APB1ENR |= (1u << 8))

#define		TIMER1_PERIPHERAL_ENABLE()		(TIMER1->TIMx_CR1 |= (1u << 0))
#define		TIMER2_PERIPHERAL_ENABLE()		(TIMER2->TIMx_CR1 |= (1u << 0))
#define		TIMER3_PERIPHERAL_ENABLE()		(TIMER3->TIMx_CR1 |= (1u << 0))
#define		TIMER4_PERIPHERAL_ENABLE()		(TIMER4->TIMx_CR1 |= (1u << 0))
#define		TIMER5_PERIPHERAL_ENABLE()		(TIMER5->TIMx_CR1 |= (1u << 0))
#define		TIMER6_PERIPHERAL_ENABLE()		(TIMER6->TIMx_CR1 |= (1u << 0))
#define		TIMER7_PERIPHERAL_ENABLE()		(TIMER7->TIMx_CR1 |= (1u << 0))
#define		TIMER8_PERIPHERAL_ENABLE()		(TIMER8->TIMx_CR1 |= (1u << 0))
#define		TIMER9_PERIPHERAL_ENABLE()		(TIMER9->TIMx_CR1 |= (1u << 0))
#define		TIMER10_PERIPHERAL_ENABLE()		(TIMER10->TIMx_CR1|= (1u << 0))
#define		TIMER11_PERIPHERAL_ENABLE()		(TIMER11->TIMx_CR1|= (1u << 0))
#define		TIMER12_PERIPHERAL_ENABLE()		(TIMER12->TIMx_CR1|= (1u << 0))
#define		TIMER13_PERIPHERAL_ENABLE()		(TIMER13->TIMx_CR1|= (1u << 0))
#define		TIMER14_PERIPHERAL_ENABLE()		(TIMER14->TIMx_CR1|= (1u << 0))

#define		TIMER2_PERIPHERAL_DISABLE()		(TIMER2->TIMx_CR1 &= ~(1u << 0))
#define		TIMER3_PERIPHERAL_DISABLE()		(TIMER3->TIMx_CR1 &= ~(1u << 0))


#define 	TIMER2_INTERRUPT_ENABLE()		(TIMER2->TIMx_DIER|= (1u << 0))
#define 	TIMER3_INTERRUPT_ENABLE()		(TIMER3->TIMx_DIER|= (1u << 0))
#define 	TIMER4_INTERRUPT_ENABLE()		(TIMER4->TIMx_DIER|= (1u << 0))
#define 	TIMER5_INTERRUPT_CC2_ENABLE()	(TIMER5->TIMx_DIER|= (1u << 2))

#define		TIMER3_PWM_MODE_1()				(TIMER3->TIMx_CCMR1 |= (0b110 << 4))
#define		TIMER3_PRELOAD_ENABLE() 		(TIMER3->TIMx_CCMR1 |= (1u << 3))
#define		TIMER3_RELOAD_ENABLE()			(TIMER3->TIMx_CR1 |= (1u << 7))
#define		TIMER3_UPDATE_GEN_ENABLE()		(TIMER3->TIMx_EGR |= (1u << 0))
#define		TIMER3_PWM_ENABLE()				(TIMER3->TIMx_CCER |= (1u << 0))

void timerxConfig(Timer_RegDef_t* selectTimer,uint16_t prescaler, uint32_t autoReload );
void timerxPeripheralEnable(Timer_RegDef_t* selectTimer);
void timer2InterruptEnable();
void timer3InterruptEnable();
void timer4InterruptEnable();
void timer5InterruptEnable();
void timer3PwmEnable(uint32_t dutyCycle);
void timerxCaptureEnable(Timer_RegDef_t* selectTimer, CC_Channel_e channel, CC_Mode_e mode, CC_Edge_Selection_e edge);
#endif /* TIMER_H_ */
