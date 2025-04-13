/*
 * stm32f4xx.h
 *
 *  Created on: Oct 18, 2024
 *      Author: khans
 */

#ifndef STM32F4XX_H_
#define STM32F4XX_H_
#include <stdint.h>
#include <stddef.h>
typedef uint8_t BOOL;

#define 	APB1_BASE_ADDR 			0x40000000
#define 	APB2_BASE_ADDR 			0x40010000
#define 	AHB1_BASE_ADDR 			0x40020000
#define 	AHB2_BASE_ADDR 			0x50000000
#define 	AHB3_BASE_ADDR 			0xA0000000


// APB1 BUSLARI
#define 	TIM2_BASE_ADDR			APB1_BASE_ADDR
#define 	TIM3_BASE_ADDR			(APB1_BASE_ADDR + 0x400)
#define 	TIM4_BASE_ADDR			(APB1_BASE_ADDR + 0x800)
#define 	TIM5_BASE_ADDR			(APB1_BASE_ADDR + 0xC00)
#define 	TIM6_BASE_ADDR			(APB1_BASE_ADDR + 0x1000)
#define 	TIM7_BASE_ADDR			(APB1_BASE_ADDR + 0x1400)
#define 	TIM12_BASE_ADDR			(APB1_BASE_ADDR + 0x1800)
#define 	TIM13_BASE_ADDR			(APB1_BASE_ADDR + 0x1C00)
#define 	TIM14_BASE_ADDR			(APB1_BASE_ADDR + 0x2000)
#define 	RTC_BKP_BASE_ADDR		(APB1_BASE_ADDR + 0x2800)
#define 	WWDG_BASE_ADDR			(APB1_BASE_ADDR + 0x2C00)
#define 	IWDG_BASE_ADDR			(APB1_BASE_ADDR + 0x3000)
#define 	I2S2EXT_BASE_ADDR		(APB1_BASE_ADDR + 0x3400)
#define 	SPI2_I2S2_BASE_ADDR		(APB1_BASE_ADDR + 0x3800)
#define 	SPI3_I2S3_BASE_ADDR		(APB1_BASE_ADDR + 0x3C00)
#define 	I2S3EXT_BASE_ADDR		(APB1_BASE_ADDR + 0x4000)
#define 	USART2_BASE_ADDR		(APB1_BASE_ADDR + 0x4400)
#define 	USART3_BASE_ADDR		(APB1_BASE_ADDR + 0x4800)
#define 	UART4_BASE_ADDR			(APB1_BASE_ADDR + 0x4C00)
#define 	UART5_BASE_ADDR			(APB1_BASE_ADDR + 0x5000)
#define 	I2C1_BASE_ADDR			(APB1_BASE_ADDR + 0x5400)
#define 	I2C2_BASE_ADDR			(APB1_BASE_ADDR + 0x5800)
#define 	I2C3_BASE_ADDR			(APB1_BASE_ADDR + 0x5C00)
#define 	CAN1_BASE_ADDR			(APB1_BASE_ADDR + 0x6400)
#define 	CAN2_BASE_ADDR			(APB1_BASE_ADDR + 0x6800)
#define 	PWR_BASE_ADDR			(APB1_BASE_ADDR + 0x7000)
#define 	DAC_BASE_ADDR			(APB1_BASE_ADDR + 0x7400)
#define 	UART7_BASE_ADDR			(APB1_BASE_ADDR + 0x7800)
#define 	UART8_BASE_ADDR			(APB1_BASE_ADDR + 0x7C00)

// APB2 BUSLARI
#define 	TIM1_BASE_ADDR				APB2_BASE_ADDR
#define 	TIM8_BASE_ADDR				(APB2_BASE_ADDR + 0x400)
#define 	USART1_BASE_ADDR			(APB2_BASE_ADDR + 0x1000)
#define 	USART6_BASE_ADDR			(APB2_BASE_ADDR + 0x1400)
#define 	ADC1_BASE_ADDR				(APB2_BASE_ADDR + 0x2000)
#define 	ADC2_BASE_ADDR				(APB2_BASE_ADDR + 0x2100)
#define 	ADC3_BASE_ADDR				(APB2_BASE_ADDR + 0x2200)

#define 	SDIO_BASE_ADDR				(APB2_BASE_ADDR + 0x2C00)
#define 	SPI1_BASE_ADDR				(APB2_BASE_ADDR + 0x3000)
#define 	SPI4_BASE_ADDR				(APB2_BASE_ADDR + 0x3400)
#define 	SYSCFG_BASE_ADDR			(APB2_BASE_ADDR + 0x3800)
#define 	EXTI_BASE_ADDR				(APB2_BASE_ADDR + 0x3C00)
#define 	TIM9_BASE_ADDR				(APB2_BASE_ADDR + 0x4000)
#define 	TIM10_BASE_ADDR				(APB2_BASE_ADDR + 0x4400)
#define 	TIM11_BASE_ADDR				(APB2_BASE_ADDR + 0x4800)
#define 	SPI5_BASE_ADDR				(APB2_BASE_ADDR + 0x5000)
#define 	SPI6_BASE_ADDR				(APB2_BASE_ADDR + 0x5400)
#define 	SAI1_BASE_ADDR				(APB2_BASE_ADDR + 0x5800)
#define 	LCD_TFT_BASE_ADDR			(APB2_BASE_ADDR + 0x6800)

 // AHB1 BUSLARI
#define 	GPIOA_BASE_ADDR				AHB1_BASE_ADDR
#define 	GPIOB_BASE_ADDR				(AHB1_BASE_ADDR + 0x400)
#define 	GPIOC_BASE_ADDR				(AHB1_BASE_ADDR + 0x800)
#define 	GPIOD_BASE_ADDR				(AHB1_BASE_ADDR + 0xC00)
#define 	GPIOE_BASE_ADDR				(AHB1_BASE_ADDR + 0x1000)
#define 	GPIOF_BASE_ADDR				(AHB1_BASE_ADDR + 0x1400)
#define 	GPIOG_BASE_ADDR				(AHB1_BASE_ADDR + 0x1800)
#define 	GPIOH_BASE_ADDR				(AHB1_BASE_ADDR + 0x1C00)
#define 	GPIOI_BASE_ADDR				(AHB1_BASE_ADDR + 0x2000)
#define 	GPIOJ_BASE_ADDR				(AHB1_BASE_ADDR + 0x2400)
#define 	GPIOK_BASE_ADDR				(AHB1_BASE_ADDR + 0x2800)
#define 	CRC_BASE_ADDR				(AHB1_BASE_ADDR + 0x3000)
#define 	RCC_BASE_ADDR				(AHB1_BASE_ADDR + 0x3800)
#define 	FLASH_INTERFACE_BASE_ADDR	(AHB1_BASE_ADDR + 0x3C00)
#define 	BKPSRAM_BASE_ADDR			(AHB1_BASE_ADDR + 0x4000)
#define 	DMA1_BASE_ADDR				(AHB1_BASE_ADDR + 0x6000)
#define 	DMA2_BASE_ADDR				(AHB1_BASE_ADDR + 0x6400)
#define		ETHERNET_MAC_ADDR			(AHB1_BASE_ADDR + 0x8000)
#define 	DMA2D_BASE_ADDR				(AHB1_BASE_ADDR + 0xB000)
#define 	USB_OTG_HS_BASE_ADDR 		(AHB1_BASE_ADDR + 0x20000)

// AHB2 BUSLARI
#define 	USB_OTG_FS_BASE_ADDR 		 AHB2_BASE_ADDR
#define 	DCMI_BASE_ADDR 		 		(AHB2_BASE_ADDR + 0x50000)
#define 	CRYP_BASE_ADDR 		 		(AHB2_BASE_ADDR + 0x60000)
#define 	HASH_BASE_ADDR 		 		(AHB2_BASE_ADDR + 0x60400)
#define 	RNG_BASE_ADDR 		 		(AHB2_BASE_ADDR + 0x60800)


// AHB3 BUSLARI
#define		FSMC_FMC_BASE_ADDR			 AHB3_BASE_ADDR


typedef struct{

	volatile uint32_t CR;
	volatile uint32_t SR;
	volatile uint32_t DR;

}RNG_t;


#define		 RNG			((RNG_t*)RNG_BASE_ADDR)

typedef struct {

	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t AHB3RSTR;
	volatile uint32_t RESERVED_1;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t RESERVED_2;
	volatile uint32_t RESERVED_3;
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t AHB3ENR;
	volatile uint32_t RESERVED_4;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t RESERVED_5;
	volatile uint32_t RESERVED_6;
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t AHB3LPENR;
	volatile uint32_t RESERVED_7;
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	volatile uint32_t RESERVED_8;
	volatile uint32_t RESERVED_9;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t RESERVED_10;
	volatile uint32_t RESERVED_11;
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;


}GPIO_RCC_t;
#define 	RCC 					((GPIO_RCC_t*)RCC_BASE_ADDR)
#define 	RCC_PLL_ON()			(RCC->CR |= (1u << 24))



typedef struct {

	// MODER, OTYPER, OSPEEDR, PUPDR, IDR, ODR, BSRR, LCKR, AFRL[2](low, high)
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2];

}GPIO_RegDef_t;		//_t ==> typedef



typedef struct{

	uint8_t MODE;
	uint8_t PIN;
	uint8_t OTYPE;
	uint8_t OSPEED;
	uint8_t PUPD;
	uint8_t AF;

}GPIO_PinConfig_t;
typedef struct{
		//	PORT ismi
		/*	pin seçimi
		 * MODER
		 * 1-input 2-output 3- alternate func 4- analog
		 * OTYPER
		 * 1-push-pull 2-open-drain
		 * OSPEEDR
		 * 1-low speed 2-medium speed 3-high speed 4-very high speed
		 * PUPDR
		 * 1-no pu-no pd 2-pull up 3-pull down
		 *
		 */
	GPIO_RegDef_t* PORTNAME; //	PORT ismi
	GPIO_PinConfig_t PINCONF;


}GPIO_Handle_t;


/*GPIOx makroları ile doğrudan portları manipüle edebiliriz.
 *ÖRNEK GPIOA->MODER = 0x01;
 **/
#define 	GPIOA		((GPIO_RegDef_t*)(GPIOA_BASE_ADDR))
#define 	GPIOB		((GPIO_RegDef_t*)(GPIOB_BASE_ADDR))
#define 	GPIOC		((GPIO_RegDef_t*)(GPIOC_BASE_ADDR))
#define 	GPIOD		((GPIO_RegDef_t*)(GPIOD_BASE_ADDR))
#define 	GPIOE		((GPIO_RegDef_t*)(GPIOE_BASE_ADDR))
#define 	GPIOF		((GPIO_RegDef_t*)(GPIOF_BASE_ADDR))
#define 	GPIOG		((GPIO_RegDef_t*)(GPIOG_BASE_ADDR))
#define 	GPIOH		((GPIO_RegDef_t*)(GPIOH_BASE_ADDR))
#define 	GPIOI		((GPIO_RegDef_t*)(GPIOI_BASE_ADDR))
#define 	GPIOJ		((GPIO_RegDef_t*)(GPIOJ_BASE_ADDR))
#define 	GPIOK		((GPIO_RegDef_t*)(GPIOK_BASE_ADDR))



typedef struct {
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_RegDef_t;

#define 		EXTI		((EXTI_RegDef_t*)(EXTI_BASE_ADDR))

typedef struct {

	volatile uint32_t MEMRMP;
	volatile uint32_t PMC;
	volatile uint32_t EXTICR[4];
	volatile uint32_t BLANK[2];
	volatile uint32_t CMPCR;

}SYSCFG_RegDef_t;

//uint8_t data[8] = {0x30, 0x50,0x30, 0x30, 0x50,0x30, 0, 0};
#define 		SYSCFG		((SYSCFG_RegDef_t*)(SYSCFG_BASE_ADDR))

#endif /* STM32F4XX_H_ */
