/* color-bricklet
 * Copyright (C) 2014 Ishraq Ibne Ashraf <ishraq@tinkerforge.com>
 *
 * color.c: Implementation of Color Bricklet messages
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

#include "color.h"

#include "brickletlib/bricklet_entry.h"
#include "brickletlib/bricklet_simple_x4.h"
#include "bricklib/utility/util_definitions.h"
#include "bricklib/bricklet/bricklet_communication.h"
#include "config.h"

#define I2C_EEPROM_ADDRESS_HIGH 84

#define I2C_ADDRESS 41 //I2C address of the RGB sensor TCS34725
#define I2C_HALF_CLOCK_400KHZ  1250  // 2500ns per clock
#define I2C_READ  1
#define I2C_WRITE 0

#define SIMPLE_UNIT_COLOR 0

const SimpleMessageProperty smp[] = {
    // {Unit(color, analog value etc), transfer type(value, period etc), direction(get/set)},
	{SIMPLE_UNIT_COLOR, SIMPLE_TRANSFER_VALUE, SIMPLE_DIRECTION_GET}, // TYPE_GET_COLOR
	{SIMPLE_UNIT_COLOR, SIMPLE_TRANSFER_PERIOD, SIMPLE_DIRECTION_SET}, // TYPE_SET_COLOR_CALLBACK_PERIOD
	{SIMPLE_UNIT_COLOR, SIMPLE_TRANSFER_PERIOD, SIMPLE_DIRECTION_GET}, // TYPE_GET_COLOR_CALLBACK_PERIOD
	{SIMPLE_UNIT_COLOR, SIMPLE_TRANSFER_THRESHOLD, SIMPLE_DIRECTION_SET}, // TYPE_SET_COLOR_CALLBACK_THRESHOLD
	{SIMPLE_UNIT_COLOR, SIMPLE_TRANSFER_THRESHOLD, SIMPLE_DIRECTION_GET}, // TYPE_GET_COLOR_CALLBACK_THRESHOLD
	{0, SIMPLE_TRANSFER_DEBOUNCE, SIMPLE_DIRECTION_SET}, // TYPE_SET_DEBOUNCE_PERIOD
	{0, SIMPLE_TRANSFER_DEBOUNCE, SIMPLE_DIRECTION_GET} // TYPE_GET_DEBOUNCE_PERIOD
};

const SimpleUnitProperty sup[] = {
    // {signed/unsigned, FID for getter, FID for reached callback, unit}
	{SIMPLE_SIGNEDNESS_UINT, FID_COLOR, FID_COLOR_REACHED, SIMPLE_UNIT_COLOR} // color
};

const uint8_t smp_length = sizeof(smp);

void invocation(const ComType com, const uint8_t *data) {
	switch(((MessageHeader*)data)->fid) {
        case FID_LIGHT_ON: {
			light_on(com, (LightOn*)data);
			return;
		}
		case FID_LIGHT_OFF: {
			light_off(com, (LightOff*)data);
			return;
		}
		case FID_IS_LIGHT_ON: {
			is_light_on(com, (IsLightOn*)data);
			return;
		}
        case FID_SET_CONFIG: {
            set_config(com, (Config*)data);
        }
        case FID_GET_CONFIG: {
            get_config(com, (GetConfig*)data);
        }
    }

	simple_invocation(com, data);

	if(((MessageHeader*)data)->fid > FID_LAST) {
		BA->com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_NOT_SUPPORTED, com);
	}
}

void constructor(void) {
	_Static_assert(sizeof(BrickContext) <= BRICKLET_CONTEXT_MAX_SIZE, "BrickContext too big");

    //setup device
    uint8_t enable_reg_config = (1 << 4) | (1 << 1) | (1 << 0);
    write_register(REG_RW_ENABLE, enable_reg_config);//disabling wait
    write_register(REG_RW_PERS, 0x00);//enabling interrupt every RGBC cycle

    //setting the interrupt pin as input
    PIN_INT.type = PIO_INPUT;
    PIN_INT.attribute = PIO_PULLUP;
    BA->PIO_Configure(&PIN_INT, 1);
    
    //turning off the light by default
    PIN_LED.type = PIO_OUTPUT_0;
    PIN_LED.attribute = PIO_DEFAULT;
    BA->PIO_Configure(&PIN_LED, 1);

    //setting up default configuration(gain, integration time)
    BC->config_gain = 0x3;//(0b11) 60x gain
    BC->config_integration_time = 0x00;//(0b00000000) 700ms integration time
    write_register(REG_RW_CONTROL, BC->config_gain);
    write_register(REG_RW_ATIME, BC->config_integration_time);
}

void destructor(void) {
	simple_destructor();
}

void tick(const uint8_t tick_type) {   
    if(tick_type & TICK_TASK_TYPE_CALCULATION) {
        if(!(PIN_INT.pio->PIO_PDSR & PIN_INT.mask)) {
            uint16_t values[4];
            read_registers(REG_RO_CDATAL, (uint8_t*)values, 8);
            BC->value1[SIMPLE_UNIT_COLOR] = values[1];
            BC->value2[SIMPLE_UNIT_COLOR] = values[2];
            BC->value3[SIMPLE_UNIT_COLOR] = values[3];
            BC->value4[SIMPLE_UNIT_COLOR] = values[0];
            clear_interrupt();
        }
    }
	simple_tick(tick_type);
}

void light_on(const ComType com, const LightOn *data) {
    PIN_LED.pio->PIO_SODR = PIN_LED.mask;
}

void light_off(const ComType com, const LightOff *data) {
    PIN_LED.pio->PIO_CODR = PIN_LED.mask;
}

void is_light_on(const ComType com, const IsLightOn *data) {
    IsLightOnReturn ilor;
	ilor.header        = data->header;
	ilor.header.length = sizeof(IsLightOnReturn);
	ilor.light         = PIN_LED.pio->PIO_PDSR & PIN_LED.mask ? 0 : 1;
	BA->send_blocking_with_timeout(&ilor, sizeof(IsLightOnReturn), com);
}

void set_config(const ComType com, const Config *data) {
    BC->config_gain = data->gain;
    BC->config_integration_time = data->integration_time;
    write_register(REG_RW_CONTROL, BC->config_gain);
    write_register(REG_RW_ATIME, BC->config_integration_time);
	BA->com_return_setter(com, data);
}

void get_config(const ComType com, const GetConfig *data) {
    Config cfg;
	cfg.header = data->header;
	cfg.header.length = sizeof(cfg);
    cfg.gain = BC->config_gain;
    cfg.integration_time = BC->config_integration_time;
	BA->send_blocking_with_timeout(&cfg, sizeof(Config), com);
}

void read_registers(const uint8_t reg, uint8_t *data, const uint8_t length) {
	i2c_start();
	i2c_send_byte((I2C_ADDRESS << 1) | I2C_WRITE);
	i2c_send_byte(reg | COMMAND_REG_SEL);
	i2c_stop();
	i2c_start();
	i2c_send_byte((I2C_ADDRESS << 1) | I2C_READ);
	for(uint8_t i = 0; i < length; i++) {
		data[i] = i2c_recv_byte(i != (length - 1));
	}
	i2c_stop();
}

void clear_interrupt() {
	i2c_start();
	i2c_send_byte((I2C_ADDRESS << 1) | I2C_WRITE);
	i2c_send_byte(0b11100110);
	i2c_stop();
}

void write_register(const uint8_t reg, uint8_t value) {
	i2c_start();
	i2c_send_byte((I2C_ADDRESS << 1) | I2C_WRITE);
	i2c_send_byte(reg | COMMAND_REG_SEL);
	i2c_send_byte(value);
	i2c_stop();
}

bool i2c_scl_value(void) {
	return PIN_SCL.pio->PIO_PDSR & PIN_SCL.mask;
}

void i2c_scl_high(void) {
	PIN_SCL.pio->PIO_ODR = PIN_SCL.mask;
	while(!i2c_scl_value()); // allow slave to clock-stretch
}

void i2c_scl_low(void) {
	PIN_SCL.pio->PIO_OER = PIN_SCL.mask;
}

bool i2c_sda_value(void) {
	return PIN_SDA.pio->PIO_PDSR & PIN_SDA.mask;
}

void i2c_sda_high(void) {
	PIN_SDA.pio->PIO_ODR = PIN_SDA.mask;
}

void i2c_sda_low(void) {
	PIN_SDA.pio->PIO_OER = PIN_SDA.mask;
}

void i2c_sleep_halfclock(void) {
	SLEEP_NS(I2C_HALF_CLOCK_400KHZ);
}

void i2c_stop(void) {
	i2c_scl_low();
	i2c_sda_low();
	i2c_sleep_halfclock();
	i2c_scl_high();
	i2c_sleep_halfclock();
	i2c_sda_high();
	i2c_sleep_halfclock();
}

void i2c_start(void) {
	i2c_scl_high();
	i2c_sleep_halfclock();
	i2c_sda_low();
	i2c_sleep_halfclock();
}

uint8_t i2c_recv_byte(bool ack) {
	uint8_t value = 0;

	for(int8_t i = 7; i >= 0; i--) {
		i2c_scl_low();
		i2c_sda_high(); // allow slave to read
		i2c_sleep_halfclock();
		i2c_scl_high();
		if(i2c_sda_value()) {
			value |= (1 << i);
		}
		i2c_sleep_halfclock();
	}

	// ACK
	i2c_scl_low();
	if(ack) {
		i2c_sda_low();
	} else {
		i2c_sda_high();
	}
	i2c_sleep_halfclock();
	i2c_scl_high();
	i2c_sleep_halfclock();

	return value;
}

bool i2c_send_byte(const uint8_t value) {
	for(int8_t i = 7; i >= 0; i--) {
		i2c_scl_low();
		if((value >> i) & 1) {
			i2c_sda_high();
		} else {
			i2c_sda_low();
		}
		i2c_sleep_halfclock();
		i2c_scl_high();
		i2c_sleep_halfclock();
	}

	// Wait for ACK
	bool ret = false;

	i2c_scl_low();
	i2c_sleep_halfclock();
	i2c_scl_high();
	if(!i2c_sda_value()) {
		ret = true;
	}

	i2c_sleep_halfclock();
	return ret;
}

