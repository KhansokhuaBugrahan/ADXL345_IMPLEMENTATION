#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include <stdbool.h>
#include "gpio.h"
#include "utility.h"
#include "armcortexm4.h"
#include "timer.h"
#include "spi.h"
#include "adxl345.h"

volatile uint8_t flagSingleTap = true;
volatile uint8_t flag = false;


volatile uint8_t extFlag = true;
volatile uint8_t timer2Flag = false;
volatile uint8_t timer3Flag = false;
volatile uint8_t lockoutActive = false;

void EXTI9_5_IRQHandler(void)
{

	if(EXTI->PR & (1u << 8) && extFlag)
	{
		EXTI_SET_PR_8(); // clear pending register

		if(flag == false) {
			timerxConfig(TIMER2, 16000, 300); // 1ms tick, each 300ms overflow

			TIMER2_INTERRUPT_ENABLE();
			nvicInterruptEnable(IRQN_TIM2);
			TIMER2->TIMx_CNT = 0;
			timerxPeripheralEnable(TIMER2);
			flag = true;
			TIMER2->TIMx_CR1 &= ~(1u << 1); // uif enable

			flagSingleTap = true; // Activate detection of single tap
			extFlag = false;

			timer2Flag = true;


			nvicInterruptDisable(IRQN_EXTI9_5);
		}

	}


}
void TIM2_IRQHandler(void)
{

  if(TIMER2->TIMx_SR & (1u << 0) && timer2Flag)
  {
	  uint8_t flagTap = readRegisterDataAdxl345(INT_SOURCE_BASE_ADDR); // read the register here,do not read it in timer1 to not clear the register
	  TIMER2->TIMx_SR = ~(1u << 0);

	  if((1u << 5) & flagTap) // 5. bit is the double tap
	  {
		  gpioTogglePin(GPIOD, LED_BLUE);

		  (void)readRegisterDataAdxl345(INT_SOURCE_BASE_ADDR); // clear register for retained trigger

		  flagSingleTap = false;

	  }
	  else if(((1u << 6) & flagTap) && flagSingleTap)
	  	gpioTogglePin(GPIOD, LED_ORANGE);

	  timerxConfig(TIMER3, 16000, 1000); // 1ms tick, each 300ms overflow


	  TIMER3->TIMx_CNT = 0;
	  TIMER3_INTERRUPT_ENABLE();
	  nvicInterruptEnable(IRQN_TIM3);
	  timerxPeripheralEnable(TIMER3);
	  TIMER3->TIMx_CR1 &= ~(1u << 1);

	  TIMER2->TIMx_DIER &= ~(1u << 0); // disable update event
	  TIMER2->TIMx_SR = 0;
	  TIMER2->TIMx_CR1 |= (1u << 1); // uif disable
	  nvicInterruptDisable(IRQN_TIM2);

	  TIMER2_PERIPHERAL_DISABLE();


	  timer2Flag = false;
	  timer3Flag = true;
  }

}
void TIM3_IRQHandler(void) // timer3 lockout time
{

	if(TIMER3->TIMx_SR & (1u << 0) && timer3Flag)
	  {
		  TIMER3->TIMx_SR = ~(1u << 0);

		  TIMER3->TIMx_DIER &= ~(1u << 0); // disable update event
		  TIMER3->TIMx_SR = 0;
		  nvicInterruptDisable(IRQN_TIM3);
		  TIMER3->TIMx_CR1 |= (1u << 1); // uif disable
		  TIMER3_PERIPHERAL_DISABLE();

		  EXTI_SET_PR_8(); // clear pending register
		  EXTI->IMR |= (1u << 8);   // enable mask
		  EXTI_SET_PR_8(); // clear pending register
		  nvicInterruptEnable(IRQN_EXTI9_5);


		  (void)readRegisterDataAdxl345(INT_SOURCE_BASE_ADDR); // clear register for retained trigger


		  flag = false;
		  timer3Flag = false;
		  extFlag = true;
	  }
}
int main(void)
{


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
									.pinConfig.cpol = SPI_CPOL_IDLE_1,           // for 1600 - 3200 Hz data output rates at least 2Mhz SPI speed is needed
									.pinConfig.cphase = SPI_CPHASE_SECOND_EDGE,  // refer to the datasheet for details
									.pinConfig.dataSize = SPI_DATA_SIZE_8,
									.pinConfig.firstBit = SPI_MSB_FIRST,
//									.pinConfig.nss =
								};

	/*
	* Configure one of the built-in LEDs (PD13) Orange LED
	*/

	GPIO_Handle_t LED_ORANGE_PD13 = {  	.PORTNAME = GPIOD,
									    .PINCONF.PIN = LED_ORANGE,
									    .PINCONF.MODE = GPIO_MODE_OUTPUT,
									    .PINCONF.OTYPE = GPIO_OTYPE_PP,
									    .PINCONF.OSPEED = GPIO_OSPEED_HIGH,
								         .PINCONF.PUPD = GPIO_PUPD_PD,
									    .PINCONF.AF = GPIO_AF_NO,
								};
	/*
	* Configure one of the built-in LEDs (PD15) Blue LED
	*/
	GPIO_Handle_t LED_BLUE_PD15 = {  	.PORTNAME = GPIOD,
									    .PINCONF.PIN = LED_BLUE,
									    .PINCONF.MODE = GPIO_MODE_OUTPUT,
									    .PINCONF.OTYPE = GPIO_OTYPE_PP,
									    .PINCONF.OSPEED = GPIO_OSPEED_HIGH,
								         .PINCONF.PUPD = GPIO_PUPD_PD,
									    .PINCONF.AF = GPIO_AF_NO,
								};



	/*
	 * PA8 pin is used as external trigger pin,
	 */

        GPIO_Handle_t EXTI_PA8 = {   .PORTNAME = GPIOA,
								   .PINCONF.PIN = GPIO_PIN_8,
								   .PINCONF.MODE = GPIO_MODE_INT_RISING, // trigger in rising edge
								   .PINCONF.OTYPE = GPIO_OTYPE_PP,
								   .PINCONF.OSPEED = GPIO_OSPEED_HIGH,
								   .PINCONF.PUPD = GPIO_PUPD_NO,
								   .PINCONF.AF = GPIO_AF_NO
					 	 	 	 };

    gpioInit(&LED_ORANGE_PD13); // set the LEDs
    gpioInit(&LED_BLUE_PD15);


    nvicInterruptEnable(IRQN_EXTI9_5); // before enabling the peripheral, enable the core's interrupt routine
	gpioInit(&EXTI_PA8);  // PA8 external interrupt pin is  connected to INT1 pin of the sensor

	spixInit(&SPI1_ADXL345); // get start the communication

	(void)readRegisterDataAdxl345(INT_SOURCE_BASE_ADDR); // clear interrupts at the beginning, because some of them could remain set before
	uint8_t readData2 = readRegisterDataAdxl345(DEVID_BASE_ADDR); // check device ID
	writeRegisterDataAdxl345(POWER_CTL_BASE_ADDR, MEASURE_MODE_ENABLE); // set for measure mode

	writeRegisterDataAdxl345(BW_RATE_BASE_ADDR, 0x0F); // output date rate 3200 Hz set,
													   //it provides higher capability to detect different frequencies(1600 Hz BW),
													   // since we will use tap detection mode now

	uint8_t readBwRegister = readRegisterDataAdxl345(BW_RATE_BASE_ADDR); // check the passed data

	writeRegisterDataAdxl345(DATA_FORMAT_BASE_ADDR, 0x0B); // +16g range , 13 bit(FULL) resolution set

	uint8_t readDataFormatVal = readRegisterDataAdxl345(DATA_FORMAT_BASE_ADDR); // check the passed data


	/*
	 * Configure the function single tap
	 */
	writeRegisterDataAdxl345(THRESH_TAP_BASE_ADDR, 0x20); //  set 2g tap treshold
	writeRegisterDataAdxl345(DUR_BASE_ADDR, 0x30);	//  set 30 ms duration time


	writeRegisterDataAdxl345(LATENT_BASE_ADDR, 0x50); // 100 ms latecny time
	writeRegisterDataAdxl345(Window_BASE_ADDR, 0xC8); // 200 ms window time

	/*
	 * All functions are mapped to INT1 as default
	 */
	writeRegisterDataAdxl345(TAP_AXES_BASE_ADDR, 0x01); // z axis enable tap detection.
	writeRegisterDataAdxl345(INT_MAP_BASE_ADDR, 0x40);

	writeRegisterDataAdxl345(INT_ENABLE_BASE_ADDR, 0x60); // enable double-signle tap interrupt



	while(1)
	{

	}
}
