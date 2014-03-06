/* color-bricklet
 * Copyright (C) 2014 Ishraq Ibne Ashraf <ishraq@tinkerforge.com>
 *
 * config.h: Temperature Bricklet specific configuration
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stdbool.h>

#include "bricklib/drivers/board/sam3s/SAM3S.h"
#include "brickletlib/bricklet_entry.h"

#include "color.h"

#define BRICKLET_FIRMWARE_VERSION_MAJOR 1
#define BRICKLET_FIRMWARE_VERSION_MINOR 0
#define BRICKLET_FIRMWARE_VERSION_REVISION 0

#define BRICKLET_HARDWARE_VERSION_MAJOR 1
#define BRICKLET_HARDWARE_VERSION_MINOR 0
#define BRICKLET_HARDWARE_VERSION_REVISION 0

#define BRICKLET_DEVICE_IDENTIFIER 243

#define LOGGING_LEVEL LOGGING_DEBUG
#define DEBUG_BRICKLET 1

#define BOARD_MCK 64000000 // Frequency of brick

#define NUM_SIMPLE_VALUES 1
#define SIMPLE_VALUE_TYPE uint16_t
#define BRICKLET_HAS_SIMPLE_X4
#define INVOCATION_IN_BRICKLET_CODE

// register definitions
#define REG_RW_ENABLE   0x00
#define REG_RW_ATIME    0x01
#define REG_RW_WTIME    0x03
#define REG_RW_AILTL    0x04
#define REG_RW_AILTH    0x05
#define REG_RW_AIHTL    0x06
#define REG_RW_AIHTH    0x07
#define REG_RW_PERS     0x0C
#define REG_RW_CONFIG   0x0D
#define REG_RW_CONTROL  0x0F
#define REG_RO_ID       0x12
#define REG_RO_STATUS   0x13
#define REG_RO_CDATAL   0x14
#define REG_RO_CDATAH   0x15
#define REG_RO_RDATAL   0x16
#define REG_RO_RDATAH   0x17
#define REG_RO_GDATAL   0x18
#define REG_RO_GDATAH   0x19
#define REG_RO_BDATAL   0x1A
#define REG_RO_BDATAH   0x1B

#define PIN_INT   (BS->pin1_ad)//marked 0 on hardware
#define PIN_LED   (BS->pin2_da)//marked 1 on hardware
#define PIN_SCL   (BS->pin4_io)//marked 3 on hardware
#define PIN_SDA   (BS->pin3_pwm)//marked 2 on hardware

#define COMMAND_REG_SEL ((1 << 7) | (1 << 5)) //set bit 7 of command register

typedef struct {
    uint8_t config_gain;
    uint8_t config_integration_time;

	int32_t value1[NUM_SIMPLE_VALUES];
	int32_t value2[NUM_SIMPLE_VALUES];
	int32_t value3[NUM_SIMPLE_VALUES];
    int32_t value4[NUM_SIMPLE_VALUES];
	int32_t last_value1[NUM_SIMPLE_VALUES];
	int32_t last_value2[NUM_SIMPLE_VALUES];
    int32_t last_value3[NUM_SIMPLE_VALUES];
    int32_t last_value4[NUM_SIMPLE_VALUES];

	uint32_t signal_period[NUM_SIMPLE_VALUES];
	uint32_t signal_period_counter[NUM_SIMPLE_VALUES];

	uint32_t threshold_debounce;
	uint32_t threshold_period_current[NUM_SIMPLE_VALUES];
	int32_t  threshold_min1[NUM_SIMPLE_VALUES];
	int32_t  threshold_max1[NUM_SIMPLE_VALUES];
	int32_t  threshold_min2[NUM_SIMPLE_VALUES];
	int32_t  threshold_max2[NUM_SIMPLE_VALUES];
	int32_t  threshold_min3[NUM_SIMPLE_VALUES];
	int32_t  threshold_max3[NUM_SIMPLE_VALUES];
    int32_t  threshold_min4[NUM_SIMPLE_VALUES];
	int32_t  threshold_max4[NUM_SIMPLE_VALUES];
	char     threshold_option[NUM_SIMPLE_VALUES];

	int32_t  threshold_min_save1[NUM_SIMPLE_VALUES];
	int32_t  threshold_max_save1[NUM_SIMPLE_VALUES];
	int32_t  threshold_min_save2[NUM_SIMPLE_VALUES];
	int32_t  threshold_max_save2[NUM_SIMPLE_VALUES];
	int32_t  threshold_min_save3[NUM_SIMPLE_VALUES];
	int32_t  threshold_max_save3[NUM_SIMPLE_VALUES];
    int32_t  threshold_min_save4[NUM_SIMPLE_VALUES];
	int32_t  threshold_max_save4[NUM_SIMPLE_VALUES];
	char     threshold_option_save[NUM_SIMPLE_VALUES];

	uint32_t tick;
} BrickContext;

#endif
