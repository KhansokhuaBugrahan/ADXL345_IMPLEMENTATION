/*
 * spi.h
 *
 *  Created on: Feb 19, 2025
 *      Author: khans
 */

#ifndef SPI_H_
#define SPI_H_
#include "stm32f4xx.h"

	/*
	 * 1- BaudRate     // (SPI_CR1) frequeny is directly diveded by prescaler which defines com speed
	 * 2- polarity and phase
	 * 3- data frame format
	 * 4- master or slave
	 * 5- frequency
	 * 6- NSS SW or HW
	 * 7- Data Alignment first MSB or LSB
	 *
	 *
	 */
typedef struct {

	uint8_t baudRate;
	uint8_t cpol;
	uint8_t cphase;
	uint8_t dataSize;
	uint8_t firstBit;
	uint8_t mode;
	uint8_t nss;

}SPI_ConFig_t;



typedef struct {

	volatile uint32_t SPI_CR1;
	volatile uint32_t SPI_CR2;
	volatile uint32_t SPI_SR;
	volatile uint32_t SPI_DR;
	volatile uint32_t SPI_CRCPR;
	volatile uint32_t SPI_RXCRCR;
	volatile uint32_t SPI_TXCRCR;
	volatile uint32_t SPI_I2SCFGR;
	volatile uint32_t SPI_I2SPR;

}SPI_RegDef_t;

typedef struct {

	SPI_RegDef_t* spiSelect;
	SPI_ConFig_t  pinConfig;
}SPI_Handle_t;

#define 		SPI1						((SPI_RegDef_t*)(SPI1_BASE_ADDR))
#define 		SPI2						((SPI_RegDef_t*)(SPI2_I2S2_BASE_ADDR))
#define 		SPI3						((SPI_RegDef_t*)(SPI3_I2S3_BASE_ADDR))


#define 		SPI1_CLOCK_ENABLE()				(RCC->APB2ENR |= (1u << 12))
#define 		SPI1_CLOCK_DISABLE()			(RCC->APB2ENR &= ~(1u << 12))

#define			SPI1_PERIPHERAL_ENABLE()  		(SPI1->SPI_CR1 |= ( 1u << 6))
#define			SPI1_PERIPHERAL_DISABLE()		(SPI1->SPI_CR1 &= ~( 1u << 6))

#define 		SPI2_CLOCK_ENABLE()				(RCC->APB1ENR |= (1u << 14))
#define 		SPI2_CLOCK_DISABLE()			(RCC->APB1ENR &= ~(1u << 14))

#define 		SPI3_CLOCK_ENABLE()				(RCC->APB1ENR |= (1u << 15))
#define 		SPI3_CLOCK_DISABLE()			(RCC->APB1ENR &= ~(1u << 15))

#define			SPI_CPOL_IDLE_0					0
#define			SPI_CPOL_IDLE_1					1

#define			SPI_CPHASE_FIRST_EDGE			0
#define			SPI_CPHASE_SECOND_EDGE			1

#define			SPI_DATA_SIZE_8			0
#define			SPI_DATA_SIZE_16		1

#define			SPI_MSB_FIRST			0
#define			SPI_LSB_FIRST			1

#define			SPI_DEVICE_SLAVE		0
#define			SPI_DEVICE_MASTER		1

typedef enum {
	SPI_BAUD_RATE_PRESC_2, SPI_BAUD_RATE_PRESC_4, SPI_BAUD_RATE_PRESC_8, SPI_BAUD_RATE_PRESC_16,
	SPI_BAUD_RATE_PRESC_32, SPI_BAUD_RATE_PRESC_64, SPI_BAUD_RATE_PRESC_128, SPI_BAUD_RATE_PRESC_256
}SPI_BaudRate_e;

void spixInit(const SPI_Handle_t* handler);
void spixSendDataByte(SPI_RegDef_t* spi, const uint8_t* buffer, size_t size);
void spixSendDataHalfWord(SPI_RegDef_t* spi, const uint16_t* buffer, size_t size);
void spixReceiveDataByte(SPI_RegDef_t* spi, uint8_t* buffer, size_t size);
void spixReceiveDataHalfWord(SPI_RegDef_t* spi, uint16_t* buffer, size_t size);
#endif /* SPI_H_ */
