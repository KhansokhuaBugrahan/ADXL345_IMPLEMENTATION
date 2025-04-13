/*
 * adxl345.c
 *
 *  Created on: Feb 23, 2025
 *      Author: khans
 */
#include "adxl345.h"
#include "armcortexm4.h"

uint8_t readRegisterDataAdxl345(uint8_t registerAddress )
{
		SPI1_PERIPHERAL_ENABLE();

		uint8_t readBuffer = 0;
		uint8_t dummyByte = 0xFF; // I can send the registerAddress twice instead of creating a new variable for this
								  // But to avoid confusion, it is clearer
		registerAddress |= 0x80; // set for read operation
		//readBuffer = SPI1->SPI_DR;
		spixSendDataByte(SPI1, &registerAddress , 1);
		readBuffer = SPI1->SPI_DR;  // clear buffer(garbage data) by reading it, otherwise it remains stuck

		spixSendDataByte(SPI1,&dummyByte , 1);
		spixReceiveDataByte(SPI1, &readBuffer, 1);

		SPI1_PERIPHERAL_DISABLE();

		return readBuffer;
}


void writeRegisterDataAdxl345(uint8_t registerAddress, uint8_t data )
{
	SPI1_PERIPHERAL_ENABLE();
	spixSendDataByte(SPI1, &registerAddress , 1); // since we do not modify 7.bit for R/W operation it is default 0(write)
	spixSendDataByte(SPI1, &data , 1);
	SPI1_PERIPHERAL_DISABLE();
}

//int16_t readAxisDataAdxl345(uint8_t baseRegister)
//{
//    uint8_t dataBuffer[2] = {0};
//
//    baseRegister |= 0xC0; // Read mode + Multi-byte mode
//
//    spixSendDataByte(SPI1, &baseRegister, 1); // Send register address
//    (void)SPI1->SPI_DR; // Clear garbage data
//
//    uint8_t dummyByte = 0xFF;
//    spixSendDataByte(SPI1, &dummyByte, 1); // Send dummy byte to generate clock
//    spixReceiveDataByte(SPI1, &dataBuffer[0], 1); // Read LSB (low byte)
//
//    spixSendDataByte(SPI1, &dummyByte, 1); // Send another dummy byte
//    spixReceiveDataByte(SPI1, &dataBuffer[1], 1); // Read MSB (high byte)
//
//    int16_t returnValue = dataBuffer[0];
//    returnValue |= (dataBuffer[1] << 8);
//
//    return returnValue; // Combine LSB + MSB
//}
int16_t readAxisDataAdxl345(ADXL345_AxisData_e axisBaseAddress)
{
	SPI1_PERIPHERAL_ENABLE();

    uint8_t dataBuffer[2] = {0};

    axisBaseAddress |= 0xC0; // Set Read mode and Multi-byte mode
    uint8_t dummyByte = 0xFF;
    // Send register address
    spixSendDataByte(SPI1, &axisBaseAddress, 1);

    (void)SPI1->SPI_DR; // clear buffer

    // Send first dummy byte to get LSB
    spixSendDataByte(SPI1, &dummyByte, 1);
    spixReceiveDataByte(SPI1, &dataBuffer[0], 1); // Read LSB (low byte)

    // Send second dummy byte to get MSB
    spixSendDataByte(SPI1, &dummyByte, 1);
    spixReceiveDataByte(SPI1, &dataBuffer[1], 1); // Read MSB (high byte)

    SPI1_PERIPHERAL_DISABLE();

    // Combine the two bytes: MSB should be shifted left
        int16_t returnValue = dataBuffer[0];
	    returnValue |= (dataBuffer[1] << 8);

    return returnValue; // Return combined result
}

//void writeRegisterDataAdxl345_2(uint8_t registerAddress, const uint8_t* dataBuffer )
//{
//	//registerAddress &= ~0xC0; // 1100 0000        0011 1111
//	spixSendDataByte(SPI1, &registerAddress , 1);
//	spixSendDataByte(SPI1, dataBuffer , 1);
//
//}
