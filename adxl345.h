/*
 * adxl345.h
 *
 *  Created on: Feb 23, 2025
 *      Author: Khanshokhuo
 *
 */

#ifndef ADXL345_H_
#define ADXL345_H_

#include <stdint.h>
#include <spi.h>
// Register MAP

#define			DEVID_BASE_ADDR		 (0x00) //  Device ID
#define			THRESH_TAP_BASE_ADDR	 (0x1D) //  Tap threshold
#define			OFSX_BASE_ADDR		 (0x1E) //  X-axis offset
#define			OFSY_BASE_ADDR		 (0x1F) //  Y-axis offset
#define			OFSZ_BASE_ADDR		 (0x20) //  Z-axis offset
#define			DUR_BASE_ADDR		 (0x21) //  Tap duration
#define			LATENT_BASE_ADDR	 (0x22) //  Tap latency
#define			Window_BASE_ADDR	 (0x23) //  Tap window
#define			THRESH_ACT_BASE_ADDR	 (0x24)	//  Activity threshold
#define			THRESH_INACT_BASE_ADDR	 (0x25) //  Inactivity threshold
#define			TIME_INACT_BASE_ADDR	 (0x26) //  Inactivity time
#define			ACT_INACT_CTL_BASE_ADDR	 (0x27) //  Axis enable control for activity and inactivity detection
#define			THRESH_FF_BASE_ADDR	 (0x28)	//  Free-fall threshold
#define			TIME_FF_BASE_ADDR	 (0x29)	//  Free-fall time
#define			TAP_AXES_BASE_ADDR	 (0x2A)	//  Axis control for single tap/double tap
#define			ACT_TAP_STATUS_BASE_ADDR (0x2B)	//  Source of single tap/double tap
#define			BW_RATE_BASE_ADDR	 (0x2C) //  Data rate and power mode control
#define			POWER_CTL_BASE_ADDR	 (0x2D) //  Power-saving features control
#define			INT_ENABLE_BASE_ADDR	 (0x2E)	//  Interrupt enable control
#define			INT_MAP_BASE_ADDR	 (0x2F)	//  Interrupt mapping control
#define			INT_SOURCE_BASE_ADDR	 (0x30)	//  Source of interrupts
#define			DATA_FORMAT_BASE_ADDR	 (0x31) //  Data format control
#define			DATAX0_BASE_ADDR	 (0x32) //  X-Axis Data 0
#define			DATAX1_BASE_ADDR	 (0x33)	//  X-Axis Data 1
#define			DATAY0_BASE_ADDR	 (0x34) //  Y-Axis Data 0
#define			DATAY1_BASE_ADDR	 (0x35) //  Y-Axis Data 1
#define			DATAZ0_BASE_ADDR	 (0x36) //  Z-Axis Data 0
#define			DATAZ1_BASE_ADDR	 (0x37)	//  Z-Axis Data 1
#define			FIFO_CTL_BASE_ADDR	 (0x38) //  FIFO control
#define			FIFO_STATUS_BASE_ADDR	 (0x39) //  FIFO status

/*
 *  To create the register MAP in the above, using enum might be better option in aspect of clarity
 *
 *		Take into account!
 *  1 Digital output data is formatted as 16-bit twos complement.
 *  2 Each bit increment decrement equals
 *
 *  						***Capabilities***
 *  3 Activity and inactivity sensing detect the presence or lack of motion by comparing
	  the acceleration on any axis with user-set thresholds.
	4 Tap sensing  detects single and double taps in any direction.
	5 Free-fall sensing  detects if the device is falling
-----------------------------------------------------------------------------------------------
	6 Those abilities can be implemented by using two interrupt pins

	REFERS TO DATASHEET for more info
 */

/*
 *
 */

typedef enum {
	AXIS_X = DATAX0_BASE_ADDR,
	AXIS_Y = DATAY0_BASE_ADDR,
	AXIS_Z = DATAZ0_BASE_ADDR
}ADXL345_AxisData_e;

#define			SELF_TEST_ENABLE		(1u << 7)
#define			MEASURE_MODE_ENABLE		(1u << 3)



uint8_t readRegisterDataAdxl345(uint8_t address );
void writeRegisterDataAdxl345(uint8_t registerAddress, uint8_t data );
int16_t readAxisDataAdxl345(ADXL345_AxisData_e axisBaseAddress);
#endif /* ADXL345_H_ */
