/*
 * armcortexm4.h
 *
 *  Created on: Nov 30, 2024
 *      Author: khans
 */

#ifndef ARMCORTEXM4_H_
#define ARMCORTEXM4_H_
#include <stdint.h>

typedef enum {

	IRQN_WWDG, IRQN_PVD, IRQN_TAMP_STAMP, IRQN_RTC_WKUP, IRQN_FLASH, IRQN_RCC, IRQN_EXTI0, IRQN_EXTI1, IRQN_EXTI2, IRQN_EXTI3, IRQN_EXTI4,
	IRQN_DMA1_Stream0, IRQN_DMA1_Stream1, IRQN_DMA1_Stream2,IRQN_DMA1_Stream3, IRQN_DMA1_Stream4, IRQN_DMA1_Stream5, IRQN_DMA1_Stream6,
	IRQN_ADC, IRQN_CAN1_TX, IRQN_CAN1_RX0, IRQN_CAN1_RX1, IRQN_CAN1_SCE, IRQN_EXTI9_5, IRQN_TIM1_BRK_TIM9, IRQN_TIM1_UP_TIM10, IRQN_TIM1_TRG_COM_TIM11,
	IRQN_TIM1_CC, IRQN_TIM2, IRQN_TIM3, IRQN_TIM4, IRQN_TIM5 = 50,
	// devamı eklenmeli


}IRQ_NUMBER_e;



#define 		ICTR_BASEADDR				0xE000E004
#define 		NVIC_ISER_BASEADDR			0xE000E100
#define 		NVIC_ICER_BASEADDR			0xE000E180
#define 		NVIC_ISPR_BASEADDR			0xE000E200
#define 		NVIC_ICPR_BASEADDR			0xE000E280
#define 		NVIC_IABR_BASEADDR			0xE000E300
#define 		NVIC_IPR0_BASEADDR			0xE000E400

#define 		SYST_CSR_BASEADDR			0xE000E010

#define			FPU_BASEADDR				0xE000EF34

typedef struct {

	volatile  uint32_t FPCCR;
	volatile  uint32_t FPCAR;
	volatile  uint32_t FPDSCR;
	volatile  uint32_t MVFR0;
	volatile  uint32_t MVFR1;


}FPU_RegDef_t;

#define 		FPU						((FPU_RegDef_t*)(FPU_BASEADDR))

#define			ASPEN_ENABLE()			(FPU->FPCCR |= (1u << 31))
#define			LSPEN_ENABLE()			(FPU->FPCCR |= (1u << 30))

#define			FP_ROUNDING_MODE()		(FPU->MVFR0 |= (1u << 28))
#define			FP_SQUARE_ROOT()		(FPU->MVFR0 |= (1u << 20))
#define			FP_DIVIDE()				(FPU->MVFR0 |= (1u << 16))
#define			FP_SINGLE_PRECISION()	(FPU->MVFR0 |= (2u << 4))
#define			FP_SIMD()				(FPU->MVFR0 |= (1u << 0))

#define			CPACR()					((*((uint32_t*)0xE000ED88)) |=  (15u << 20))



typedef struct {

	volatile uint32_t NVIC_ISER0;
	volatile uint32_t NVIC_ISER1;
	volatile uint32_t NVIC_ISER2;
	volatile uint32_t NVIC_ISER3;
	volatile uint32_t NVIC_ISER4;
	volatile uint32_t NVIC_ISER5;
	volatile uint32_t NVIC_ISER6;
	volatile uint32_t NVIC_ISER7;

}NVIC_ISER_RegDef_t;



#define		NVIC_ISER		((NVIC_ISER_RegDef_t*)(NVIC_ISER_BASEADDR))

typedef struct  {

	volatile uint32_t NVIC_ICER0;
	volatile uint32_t NVIC_ICER1;
	volatile uint32_t NVIC_ICER2;
	volatile uint32_t NVIC_ICER3;
	volatile uint32_t NVIC_ICER4;
	volatile uint32_t NVIC_ICER5;
	volatile uint32_t NVIC_ICER6;
	volatile uint32_t NVIC_ICER7;

}NVIC_ICER_RegDef_t;

#define		NVIC_ICER		((NVIC_ICER_RegDef_t*)(NVIC_ICER_BASEADDR))

typedef struct{

	volatile uint32_t SYST_CSR;
	volatile uint32_t SYST_RVR;
	volatile uint32_t SYST_CVR;
	volatile uint32_t SYST_CALIB;

}SYSTICK_RegDef_t;

extern  volatile  uint32_t TickCounter;
#define 	  SYSTICK							((SYSTICK_RegDef_t*)(SYST_CSR_BASEADDR))
#define 	  SYSTICK_ENABLE()					(SYSTICK->SYST_CSR |= (1u << 0))
#define 	  SYSTICK_EXCEPTION_ENABLE()		(SYSTICK->SYST_CSR |= (1u << 1))
#define 	  SYSTICK_CLOCK_INTERNAL()			(SYSTICK->SYST_CSR |= (1u << 2))
#define		  SYSTICK_SET_EACH_1MS_INTERRUPT()	(SYSTICK->SYST_RVR = 16000  - 1)
#define 	  SYSTICK_RESET_CURR_VALUE()		(SYSTICK->SYST_CVR = 0)


void fpuInit(void);
void sysTickInit(void);
uint32_t getTick(void);
void delay_ms(uint32_t delay);

void nvicInterruptEnable(IRQ_NUMBER_e position);
void nvicInterruptDisable(IRQ_NUMBER_e position);
#endif /* ARMCORTEXM4_H_ */
