/*
 * gpio.c
 *
 *  Created on: Oct 19, 2024
 *      Author: khans
 */
#include "gpio.h"
#include "stm32f4xx.h"
/*
 * 	mode ayarı output için push pull, open-drain, speed ne olsun?
 * 	input için, pull-up, pull-down mu?, input mu alternate function mı?
 *
 * 	gpioInit
 *  gpioWritePin
 *  gpioTogglePin
 *  gpioWritePort
 *  gpioReadPin
 *  gpioReadPort
 *
 */
static void gpioClockEnable(const GPIO_RegDef_t* portName)
{
	if(portName == GPIOA)
	{
		GPIOA_CLOCK_EN();
	}
	else if(portName == GPIOB)
	{
		GPIOB_CLOCK_EN();
	}
	else if(portName == GPIOC)
	{
		GPIOC_CLOCK_EN();
	}
	else if(portName == GPIOD)
	{
		GPIOD_CLOCK_EN();
	}
	else if(portName == GPIOE)
	{
		GPIOE_CLOCK_EN();
	}
	else if(portName == GPIOF)
	{
		GPIOF_CLOCK_EN();
	}
	else if(portName == GPIOG)
	{
		GPIOG_CLOCK_EN();
	}
	else if(portName == GPIOH)
	{
		GPIOH_CLOCK_EN();
	}
	else if(portName == GPIOI)
	{
		GPIOI_CLOCK_EN();
	}
}
static uint8_t getNibbleCorrepondingPort(const GPIO_RegDef_t* portName)
{
		if(portName == GPIOA) return PORTA;
		else if(portName == GPIOB) return PORTB;
		else if(portName == GPIOC) return PORTC;
		else if(portName == GPIOD) return PORTD;
		else if(portName == GPIOE) return PORTE;
		else if(portName == GPIOF) return PORTF;
		else if(portName == GPIOG) return PORTG;
		else if(portName == GPIOH) return PORTH;
							return PORTI;

}
void gpioInit(GPIO_Handle_t* portName)
{

	gpioClockEnable(portName->PORTNAME);

	if(portName->PINCONF.MODE <= GPIO_MODE_ANALOG)
		portName->PORTNAME->MODER |= (portName->PINCONF.MODE << (portName->PINCONF.PIN * 2));
	else{

		if(portName->PINCONF.MODE == GPIO_MODE_INT_RISING)
				EXTI->RTSR |= (1u << portName->PINCONF.PIN);
		else if(portName->PINCONF.MODE == GPIO_MODE_INT_FALLING)
				EXTI->FTSR |= (1u << portName->PINCONF.PIN);
		else{
			EXTI->FTSR |= (1u << portName->PINCONF.PIN);
			EXTI->RTSR |= (1u << portName->PINCONF.PIN);
		}

		SYSCFG_CLOCK_EN();

		uint8_t regIndex = portName->PINCONF.PIN / 4;
		uint8_t shiftBitCount = (portName->PINCONF.PIN % 4) * 4;
		uint8_t getPortInfo = getNibbleCorrepondingPort(portName->PORTNAME);
		SYSCFG->EXTICR[regIndex] |= ( getPortInfo << shiftBitCount) ;
		EXTI->IMR |= (1u << portName->PINCONF.PIN);


	}

		portName->PORTNAME->OTYPER |= (portName->PINCONF.OTYPE << (portName->PINCONF.PIN));
		portName->PORTNAME->OSPEEDR |= (portName->PINCONF.OSPEED << (portName->PINCONF.PIN * 2));
		portName->PORTNAME->PUPDR |= (portName->PINCONF.PUPD << (portName->PINCONF.PIN * 2));

	if(portName->PINCONF.MODE == GPIO_MODE_ALTARNATE) {

		uint8_t alternHighLow = portName->PINCONF.PIN / 8;
		uint8_t bitPosition = (portName->PINCONF.PIN % 8) * 4;
		portName->PORTNAME->AFR[alternHighLow] &=  ~(0xF << bitPosition); // altermode set etmeden önce sıfırla
		portName->PORTNAME->AFR[alternHighLow] |= (portName->PINCONF.AF << bitPosition);

	}


	//	PORT ismi
	/*	pin seçimi
	 * MODER
	 *
	 * 1-input 2-output 3- alternate func 4- analog
	 * OTYPER
	 * 1-push-pull 2-open-drain
	 * OSPEEDR
	 * 1-low speed 2-medium speed 3-high speed 4-very high speed
	 * PUPDR
	 * 1-no pu-no pd 2-pull up 3-pull down
	 *
	 *ALTERNATE
	 */

}
void gpioTogglePin(GPIO_RegDef_t* portName, GPIO_PinNo_e pinNo)
{
	portName->ODR ^= (1u << pinNo);
}
void gpioWritePin(GPIO_RegDef_t* portName, GPIO_PinNo_e pinNo, BOOL state )
{
	if(state)
	{
		portName->ODR |= (1u << pinNo);
	}
	else
	{
		portName->ODR &= ~(1u << pinNo);
	}
}
void gpioWritePin2(GPIO_RegDef_t* portName, GPIO_PinNo_e pinNo, BOOL state )
{

	if(state)
	{
	 portName->BSRR |= (1u << pinNo);
	}
	else
	{
	 portName->BSRR |= (1u << (pinNo + 16));
	}

}
void gpioWritePort(GPIO_RegDef_t* portName, BOOL state)
{
	if(state)
	{
		portName->ODR = 0xFFFF;
	}
	else
	{
		portName->ODR = 0;
	}
}
uint16_t gpioReadPort(const GPIO_RegDef_t* portName)
{
	uint16_t data = (uint16_t)portName->IDR;
	return data;

}
BOOL gpioReadPin(const GPIO_RegDef_t* portName, GPIO_PinNo_e pinNo)
{
	uint16_t data = portName->IDR & (1u << pinNo);

	return data ? 1 : 0;

}
BOOL gpioReadPin2(const GPIO_RegDef_t* portName, GPIO_PinNo_e pinNo)
{
	uint16_t data = portName->ODR;
	return data &= (1u << pinNo) ? 1 : 0;
}
void gpioSetPort(GPIO_RegDef_t* portName, MODE_SELECTION_e mode)
{
	switch(mode)
	{
		case GPIO_MODE_INPUT:  portName->MODER = 0; break;
		case GPIO_MODE_OUTPUT: GPIOD->MODER = 0;
		for(int i = 0; i <= 30; i += 2)
		{
			GPIOD->MODER |= (1u << i);
		}
	    break;
		case GPIO_MODE_ALTARNATE:  GPIOD->MODER = 0;
		for(int i = 1; i <= 31; i += 2)
		{
			GPIOD->MODER |= (1u << i);
		}
	    break;
		case GPIO_MODE_ANALOG: portName->MODER = 0xFFFFFFFF; break;
		default: break;

	}
}

void gpioWritePortLowByte(GPIO_RegDef_t* portName, const uint8_t byteData)
{
		 portName->ODR = portName->ODR & (0xFF00);
		 portName->ODR |= byteData;
}
void gpioWritePortLowByte2(GPIO_RegDef_t* portName, const uint8_t byteData)
{
		for(int pinNumber = 0; pinNumber < BYTE_SIZE; pinNumber++)
		{
			if((byteData) & (1u << pinNumber) ? 1 : 0)
				gpioWritePin(portName, pinNumber, GPIO_PIN_SET);
			else
				gpioWritePin(portName, pinNumber, GPIO_PIN_RESET);
		}
}
void gpioWritePortHighByte(GPIO_RegDef_t* portName, const uint8_t byteData)
{
		 uint16_t mask = (byteData << 8);
		 portName->ODR = portName->ODR & (0x00FF);
		 portName->ODR |= mask;
}

// getRngNumber	PLL clock source  AHB2 bus en fazla 48MHz olmalı

/*
GPIO_Handle_t LEDs_D0_TO_D7[8] = {  {.PORTNAME = GPIOD,
												    .PINCONF.PIN = GPIO_PIN_0,
												    .PINCONF.MODE = GPIO_MODE_OUTPUT,
												    .PINCONF.OTYPE = GPIO_OTYPE_PP,
												    .PINCONF.OSPEED = GPIO_OSPEED_HIGH,
											        .PINCONF.PUPD = GPIO_PUPD_PD,
													.PINCONF.AF = GPIO_AF_NO},

							     	 	 };


			 for (int pin = 0;  pin < BYTE_SIZE; ++pin) {
				 LEDs_D0_TO_D7[pin] = LEDs_D0_TO_D7[0];
				 LEDs_D0_TO_D7[pin].PINCONF.PIN = pin;
				 gpioInit(&LEDs_D0_TO_D7[pin]);
			}

*/
