#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include <stdbool.h>
#include "gpio.h"
#include "armcortexm4.h"
#include "timer.h"
#include "spi.h"
#include "adxl345.h"



int main(void)
{
	sysTickInit();
	/*
	 * PA4 - PA5 - PA6 - PA7 pins must be configured in AF mode for SPI1
	 */

	GPIO_Handle_t SP1_NSS_PA4 = {	 // on ADXL345 connected to CS pin
									.PORTNAME = GPIOA,
									.PINCONF.PIN = GPIO_PIN_4,
									.PINCONF.MODE = GPIO_MODE_ALTARNATE,
									.PINCONF.OTYPE = GPIO_OTYPE_PP,
									.PINCONF.OSPEED = GPIO_OSPEED_HIGH,
									.PINCONF.PUPD = GPIO_PUPD_NO,
									.PINCONF.AF = AF5
								};
	GPIO_Handle_t SP1_SCK_PA5 = { 	 // on ADXL345 connected to SCL pin
									.PORTNAME = GPIOA,
									.PINCONF.PIN = GPIO_PIN_5,
									.PINCONF.MODE = GPIO_MODE_ALTARNATE,
									.PINCONF.OTYPE = GPIO_OTYPE_PP,
									.PINCONF.OSPEED = GPIO_OSPEED_HIGH,
									.PINCONF.PUPD = GPIO_PUPD_NO,
									.PINCONF.AF = AF5
								};
	GPIO_Handle_t SP1_MISO_PA6 = {   // on ADXL345 connected to SDO pin
									.PORTNAME = GPIOA,
									.PINCONF.PIN = GPIO_PIN_6,
									.PINCONF.MODE = GPIO_MODE_ALTARNATE,
									.PINCONF.OTYPE = GPIO_OTYPE_PP,
									.PINCONF.OSPEED = GPIO_OSPEED_HIGH,
									.PINCONF.PUPD = GPIO_PUPD_PU,
									.PINCONF.AF = AF5
								};
	GPIO_Handle_t SP1_MOSI_PA7 = {   // on ADXL345 connected to SDA pin
									.PORTNAME = GPIOA,
									.PINCONF.PIN = GPIO_PIN_7,
									.PINCONF.MODE = GPIO_MODE_ALTARNATE,
									.PINCONF.OTYPE = GPIO_OTYPE_PP,
									.PINCONF.OSPEED = GPIO_OSPEED_HIGH,
									.PINCONF.PUPD = GPIO_PUPD_NO,
									.PINCONF.AF = AF5
								};

	gpioInit(&SP1_NSS_PA4);
	gpioInit(&SP1_SCK_PA5);
	gpioInit(&SP1_MISO_PA6);
	gpioInit(&SP1_MOSI_PA7);


	/*
	 *  SPI configuration must be made according to the ADXL345 requirements
	 */

	SPI_Handle_t SPI1_ADXL345 = {   .spiSelect = SPI1,
									.pinConfig.mode = SPI_DEVICE_MASTER,
									.pinConfig.baudRate = SPI_BAUD_RATE_PRESC_8, // 2 MHz clock, since main clock 16 Mhz HSI
									.pinConfig.cpol = SPI_CPOL_IDLE_1,
									.pinConfig.cphase = SPI_CPHASE_SECOND_EDGE,
									.pinConfig.dataSize = SPI_DATA_SIZE_8,
									.pinConfig.firstBit = SPI_MSB_FIRST,
//									.pinConfig.nss =
								};

	spixInit(&SPI1_ADXL345);


	uint8_t readData2 = readRegisterDataAdxl345(DEVID_BASE_ADDR); // check device ID
	writeRegisterDataAdxl345(POWER_CTL_BASE_ADDR, MEASURE_MODE_ENABLE);



	writeRegisterDataAdxl345(DATA_FORMAT_BASE_ADDR, 0x0B); // self-test disable and +16g, 13 bit


	uint8_t readDataFormatVal = readRegisterDataAdxl345(DATA_FORMAT_BASE_ADDR); // check register value

		int16_t DataX = readAxisDataAdxl345(AXIS_X);
		int16_t DataY = readAxisDataAdxl345(AXIS_Y);
		int16_t DataZ = readAxisDataAdxl345(AXIS_Z);

		/*
		 * 
		 * I tested data outputs with different orientations, they all gave accurate results.
		 * Close to the values on figure 58 in datasheet
		 * 
		 */
	uint8_t readDataFormatVal2 = readRegisterDataAdxl345(DATA_FORMAT_BASE_ADDR); // check register value again to make sure

	uint8_t readData = readRegisterDataAdxl345(DEVID_BASE_ADDR); // check again if something went wrong



	

	while(1)
	{

	}
}
