/*
 * spi.c
 *
 *  Created on: Feb 19, 2025
 *      Author: khans
 */


#include "spi.h"

void spixInit(const SPI_Handle_t* handler)
{
	SPI_RegDef_t* spi = handler->spiSelect;

	if(spi == SPI1)
		SPI1_CLOCK_ENABLE();
	else if(spi == SPI2)
		SPI2_CLOCK_ENABLE();
	else if(spi == SPI3)
		SPI3_CLOCK_ENABLE();

	spi->SPI_CR1 = 0;
	spi->SPI_CR1 |= ( handler->pinConfig.cphase << 0);
	spi->SPI_CR1 |= ( handler->pinConfig.cpol << 1);
	spi->SPI_CR1 |= ( handler->pinConfig.mode << 2);
	spi->SPI_CR1 |= ( handler->pinConfig.baudRate << 3);
	spi->SPI_CR1 |= ( handler->pinConfig.firstBit << 7);
	spi->SPI_CR1 |= ( handler->pinConfig.dataSize << 11);
	/*
	 * Default full-duplex two wire
	 * Default NSS  in HW mode, since we will use single slave mostly
	 */
	if(!(spi->SPI_CR1 & (1u << 9))) // if HW NSS enabled
		spi->SPI_CR2 |= (1u << 2);	// set slave select	 automatically

	spi->SPI_CR1 |= ( 1u << 13); // CRC enable
	spi->SPI_CR1 |= ( 1u << 6); // peripheral enable
}
void spixSendDataByte(SPI_RegDef_t* spi, const uint8_t* buffer, size_t size)
{

	while(size--)
	{
		while(!(spi->SPI_SR & (1u << 1)))
		; // wait until TX buffer empty
		spi->SPI_DR = *buffer++;
	}

	while(spi->SPI_SR & (1u << 7))
			;  // wait until busy flag reset

}
void spixSendDataHalfWord(SPI_RegDef_t* spi, const uint16_t* buffer, size_t size)
{

	while(size--)
	{
		while(!(spi->SPI_SR & (1u << 1)))
		; // wait until TX buffer empty
		spi->SPI_DR = *buffer++;

	}

	while(spi->SPI_SR & (1u << 7))
			;  // wait until busy flag reset

}
void spixReceiveDataByte(SPI_RegDef_t* spi, uint8_t* buffer, size_t size)
{

	while(size--)
	{
		while(!(spi->SPI_SR & (1u << 0)))
		; // wait until RX buffer is not empty
		*buffer++ = spi->SPI_DR;
	}

	while(spi->SPI_SR & (1u << 7))
			;  // wait until busy flag reset
}

void spixReceiveDataHalfWord(SPI_RegDef_t* spi, uint16_t* buffer, size_t size)
{

	while(size--)
	{
		while(!(spi->SPI_SR & (1u << 0)))
		; // wait until RX buffer is not empty
		*buffer++ = spi->SPI_DR;

	}

	while(spi->SPI_SR & (1u << 7))
			;  // wait until busy flag reset

}

/*
 * little endian       (uint8_t*)++; right to left ( type cast and increment in the same priority but right to left)
 */

/*
 *
 * 				*****ADXL345*****
 * 				   First bit W/R -->      		0 - Write, 	  1 - Read
 * 			Second bit multibyte -->			0 - inactive, 1 - active
 * 							2-6  --> 			Register Address info
 * 							7-14 --> 			Data
 */
