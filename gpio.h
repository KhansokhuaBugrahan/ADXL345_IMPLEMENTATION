/*
 * gpio.h
 *
 *  Created on: Oct 19, 2024
 *      Author: khans
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f4xx.h"

#define		BUILTin_LED_COUNT			4
#define		PORT_PIN_COUNT				16
#define		BYTE_SIZE					8


#define 	GPIO_PIN_RESET 		0
#define 	GPIO_PIN_SET	  	1



#define		GPIO_OTYPE_PP		0
#define		GPIO_OTYPE_OD		1

#define		GPIO_OSPEED_LOW		0
#define		GPIO_OSPEED_MED		1
#define		GPIO_OSPEED_HIGH	2
#define		GPIO_OSPEED_VHIGH	3

#define		GPIO_PUPD_NO 		0
#define		GPIO_PUPD_PU		1
#define		GPIO_PUPD_PD		2

#define		GPIO_AF_NO			(-1)


#define 	GPIOA_CLOCK_EN()	(RCC->AHB1ENR |= (1u << 0))
#define 	GPIOB_CLOCK_EN()	(RCC->AHB1ENR |= (1u << 1))
#define 	GPIOC_CLOCK_EN()	(RCC->AHB1ENR |= (1u << 2))
#define 	GPIOD_CLOCK_EN()	(RCC->AHB1ENR |= (1u << 3))
#define 	GPIOE_CLOCK_EN()	(RCC->AHB1ENR |= (1u << 4))
#define 	GPIOF_CLOCK_EN()	(RCC->AHB1ENR |= (1u << 5))
#define 	GPIOG_CLOCK_EN()	(RCC->AHB1ENR |= (1u << 6))
#define 	GPIOH_CLOCK_EN()	(RCC->AHB1ENR |= (1u << 7))
#define 	GPIOI_CLOCK_EN()	(RCC->AHB1ENR |= (1u << 8))

#define 	SYSCFG_CLOCK_EN()   (RCC->APB2ENR |= (1u << 14))
#define 	EXTI_SET_PR_0()		(EXTI->PR |= (1u << 0))
#define 	EXTI_SET_PR_1()		(EXTI->PR |= (1u << 1))
#define 	EXTI_SET_PR_2()		(EXTI->PR |= (1u << 2))
#define 	EXTI_SET_PR_3()		(EXTI->PR |= (1u << 3))
#define 	EXTI_SET_PR_4()		(EXTI->PR |= (1u << 4))
#define 	EXTI_SET_PR_5()		(EXTI->PR |= (1u << 5))
#define 	EXTI_SET_PR_6()		(EXTI->PR |= (1u << 6))
#define 	EXTI_SET_PR_7()		(EXTI->PR |= (1u << 7))
#define 	EXTI_SET_PR_8()		(EXTI->PR |= (1u << 8))
#define		BYTE_SIZE			8

typedef enum{
	LED_GREEN = 12,
	LED_ORANGE,
	LED_RED,
	LED_BLUE
}BUILTin_LEDs_e;

typedef enum{

	GPIO_MODE_INPUT,
	GPIO_MODE_OUTPUT,
	GPIO_MODE_ALTARNATE,
	GPIO_MODE_ANALOG,
	GPIO_MODE_INT_RISING,
	GPIO_MODE_INT_FALLING,
	GPIO_MODE_INT_BOTH_RF

}MODE_SELECTION_e;

typedef enum{
	AFNO = -1, AF0, AF1, AF2, AF3, AF4, AF5, AF6, AF7, AF8, AF9, AF10, AF11, AF12, AF13, AF14, AF15
}GPIO_ALTERNATE_MODE_SELECTION_e;

typedef enum {

	GPIO_PIN_0,	GPIO_PIN_1,	GPIO_PIN_2,	GPIO_PIN_3,	GPIO_PIN_4,	GPIO_PIN_5,	GPIO_PIN_6,GPIO_PIN_7,
	GPIO_PIN_8,GPIO_PIN_9,GPIO_PIN_10,GPIO_PIN_11,GPIO_PIN_12,GPIO_PIN_13,GPIO_PIN_14,GPIO_PIN_15

}GPIO_PinNo_e;

typedef enum {

	PORTA, PORTB, PORTC, PORTD, PORTE, PORTF, PORTG, PORTH, PORTI

}SYSCFG_PORT_NIBBLE_VALs_e;


void gpioTogglePin(GPIO_RegDef_t* portName, GPIO_PinNo_e pinNo);
void gpioWritePin(GPIO_RegDef_t* portName, GPIO_PinNo_e pinNo, BOOL state );
void gpioWritePin2(GPIO_RegDef_t* portName, GPIO_PinNo_e pinNo, BOOL state );
void gpioWritePort(GPIO_RegDef_t* portName, BOOL state);
BOOL gpioReadPin(const GPIO_RegDef_t* portName, GPIO_PinNo_e pinNo);
uint16_t gpioReadPort(const GPIO_RegDef_t* portName);
void gpioSetPort(GPIO_RegDef_t* portName, MODE_SELECTION_e mode);
void gpioInit(GPIO_Handle_t* portName);
void gpioWritePortLowByte(GPIO_RegDef_t* portName, const uint8_t byteData);
void gpioWritePortLowByte2(GPIO_RegDef_t* portName, const uint8_t byteData);
void gpioWritePortHighByte(GPIO_RegDef_t* portName, const uint8_t byteData);

#endif /* GPIO_H_ */
