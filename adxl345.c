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
/*
	///////////////////DUMMY BYTE USAGE\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Now, I will tell what I understood from all of these process. Once I send a register 
address, as soon as data received by slave, it responses back quickly. However, at this point clock pulse stopped 
because after sending the address, master stops pulsing. So first received value will be invalid. 
To handle this issue, we need to give slave a chance to express itself, so we need to generate clock pulse for it.
 Then in the second sequence, when I send dummy byte, it sends  back to  proper data as response to previous
 transmisson. Then after sending the dummy byte, we only do this to generate 
adequate pulses for slave to communicate with master.Then we read the real data.




The device supports 13 bit and 10 bit resolution, 13 bit(full resoluiton) is auto-scaled but 10-bit needs to be multiplied by 4
Gravity downward is accepted as positive output, When we obtain avarage 256 LSB and multiply it with 3.9 mg/LSB, full resolution 16g mode.
Which is approximately 1g, it will indicate the acceleration acting on downward.
Since we use HW NSS mode, multibyte read is a bit problematic.Because it cannot deassert CS properly.
*/
void writeRegisterDataAdxl345(uint8_t registerAddress, uint8_t data )
{
	SPI1_PERIPHERAL_ENABLE();
	spixSendDataByte(SPI1, &registerAddress , 1); // since we do not modify 7.bit for R/W operation it is default 0(write)
	spixSendDataByte(SPI1, &data , 1);
	SPI1_PERIPHERAL_DISABLE();
}

 
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

 
