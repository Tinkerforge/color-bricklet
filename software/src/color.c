/* color-bricklet
 * Copyright (C) 2014 Ishraq Ibne Ashraf <ishraq@tinkerforge.com>
 * Copyright (C) 2014 Olaf Lüke <olaf@tinkerforge.com>
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
            set_config(com, (SetConfig*)data);
            return;
        }

        case FID_GET_CONFIG: {
            get_config(com, (GetConfig*)data);
            return;
        }

        case FID_GET_ILLUMINANCE: {
            get_illuminance(com, (GetIlluminance*)data);
            return;
        }

        case FID_GET_COLOR_TEMPERATURE: {
            get_color_temperature(com, (GetColorTemperature*)data);
            return;
        }

        case FID_SET_ILLUMINANCE_CALLBACK_PERIOD: {
            set_illuminance_callback_period(com, (SetIlluminanceCallbackPeriod*)data);
            return;
        }

        case FID_GET_ILLUMINANCE_CALLBACK_PERIOD: {
            get_illuminance_callback_period(com, (GetIlluminanceCallbackPeriod*)data);
            return;
        }

        case FID_SET_COLOR_TEMPERATURE_CALLBACK_PERIOD: {
            set_color_temperature_callback_period(com, (SetColorTemperatureCallbackPeriod*)data);
            return;
        }

        case FID_GET_COLOR_TEMPERATURE_CALLBACK_PERIOD: {
            get_color_temperature_callback_period(com, (GetColorTemperatureCallbackPeriod*)data);
            return;
        }
    }

	simple_invocation(com, data);

	if(((MessageHeader*)data)->fid > FID_LAST) {
		BA->com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_NOT_SUPPORTED, com);
	}
}

void constructor(void) {
	_Static_assert(sizeof(BrickContext) <= BRICKLET_CONTEXT_MAX_SIZE, "BrickContext too big");

    // Setup device
    write_register(REG_RW_ENABLE, REG_ENABLE_AIEN | REG_ENABLE_AEN | REG_ENABLE_PON);
    write_register(REG_RW_PERS, 0x00); // Enabling interrupt every RGBC cycle

    // Setting the interrupt pin as input
    PIN_INT.pio->PIO_PUER = PIN_INT.mask;
    PIN_INT.pio->PIO_ODR  = PIN_INT.mask;
    PIN_INT.pio->PIO_PER  = PIN_INT.mask;

    // Turning off the light by default
    PIN_LED.pio->PIO_CODR = PIN_LED.mask;
    PIN_LED.pio->PIO_OER  = PIN_LED.mask;
    PIN_LED.pio->PIO_PER  = PIN_LED.mask;

    // Setting up default configuration(gain, integration time)
    BC->config_gain = REG_CONTROL_60X_GAIN;
    BC->config_integration_time = 3;  // 3 == REG_ATIME_154MS for user configuration
    write_register(REG_RW_CONTROL, REG_CONTROL_60X_GAIN);
    write_register(REG_RW_ATIME, REG_ATIME_154MS);

    simple_constructor();
}

void tick(const uint8_t tick_type) {
	
	BrickContext *BC_local = BC;
	BrickletAPI *BA_local = BA;
	const uint32_t uid = BS->uid;

    if(tick_type & TICK_TASK_TYPE_CALCULATION) {
        if(!(PIN_INT.pio->PIO_PDSR & PIN_INT.mask)) {
            uint16_t values[4];
            read_registers(REG_RO_CDATAL, (uint8_t*)values, 8);
            BC_local->value1[SIMPLE_UNIT_COLOR] = values[1];
            BC_local->value2[SIMPLE_UNIT_COLOR] = values[2];
            BC_local->value3[SIMPLE_UNIT_COLOR] = values[3];
            BC_local->value4[SIMPLE_UNIT_COLOR] = values[0];

            clear_interrupt();
        }

		if(BC_local->signal_period_counter_illuminance < UINT32_MAX) {
			BC_local->signal_period_counter_illuminance++;
		}
		if(BC_local->signal_period_counter_color_temperature < UINT32_MAX) {
			BC_local->signal_period_counter_color_temperature++;
		}
    }

    if(tick_type & TICK_TASK_TYPE_MESSAGE) {
		if(BC_local->signal_period_illuminance != 0 &&
		   BC_local->signal_period_illuminance <= BC_local->signal_period_counter_illuminance) {
			calculate_color_temperature_and_illuminance();
			if(BC_local->illuminance_current_value != BC_local->illuminance_last_callback_value) {
				BC_local->illuminance_last_callback_value = BC_local->illuminance_current_value;
				Illuminance ill;
				BA_local->com_make_default_header(&ill, uid, sizeof(Illuminance), FID_ILLUMINANCE);
				ill.illuminance = BC_local->illuminance_current_value;

				BA_local->send_blocking_with_timeout(&ill,
											         sizeof(Illuminance),
											         *BA_local->com_current);

				BC_local->signal_period_counter_illuminance = 0;
			}
		}

		if(BC_local->signal_period_color_temperature != 0 &&
		   BC_local->signal_period_color_temperature <= BC_local->signal_period_counter_color_temperature) {
			calculate_color_temperature_and_illuminance();
			if(BC_local->color_temperature_current_value != BC_local->color_temperature_last_callback_value) {
				BC_local->color_temperature_last_callback_value = BC_local->color_temperature_current_value;
				ColorTemperature ct;
				BA_local->com_make_default_header(&ct, uid, sizeof(ColorTemperature), FID_COLOR_TEMPERATURE);
				ct.color_temperature = BC_local->color_temperature_current_value;

				BA_local->send_blocking_with_timeout(&ct,
											         sizeof(ColorTemperature),
											         *BA_local->com_current);

				BC_local->signal_period_counter_color_temperature = 0;
			}
		}
    }

	simple_tick(tick_type);
	
}

void light_on(const ComType com, const LightOn *data) {
    PIN_LED.pio->PIO_SODR = PIN_LED.mask;

    BA->com_return_setter(com, data);
}

void light_off(const ComType com, const LightOff *data) {
    PIN_LED.pio->PIO_CODR = PIN_LED.mask;

    BA->com_return_setter(com, data);
}

void is_light_on(const ComType com, const IsLightOn *data) {
    IsLightOnReturn ilor;
	ilor.header        = data->header;
	ilor.header.length = sizeof(IsLightOnReturn);
	ilor.light         = PIN_LED.pio->PIO_PDSR & PIN_LED.mask ? 0 : 1;

	BA->send_blocking_with_timeout(&ilor, sizeof(IsLightOnReturn), com);
}

void set_config(const ComType com, const SetConfig *data) {
	BrickContext *BC_local = BC;
	if(data->gain > 3 || data->integration_time > 4) {
		BA->com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
		return;
	}

	BC_local->config_gain = data->gain;
	BC_local->config_integration_time = data->integration_time;

	uint8_t write_integration_time;

	switch(data->integration_time) {
		case 0: write_integration_time = REG_ATIME_2MS; break;
		case 1: write_integration_time = REG_ATIME_24MS; break;
		case 2: write_integration_time = REG_ATIME_101MS; break;
		case 3: write_integration_time = REG_ATIME_154MS; break;
		case 4: write_integration_time = REG_ATIME_700MS; break;
		default: write_integration_time = REG_ATIME_154MS; break;
	}

    write_register(REG_RW_CONTROL, BC_local->config_gain);
    write_register(REG_RW_ATIME, write_integration_time);

	BA->com_return_setter(com, data);
}

void get_config(const ComType com, const GetConfig *data) {
    GetConfigReturn gcr;
    gcr.header = data->header;
    gcr.header.length = sizeof(GetConfigReturn);

    gcr.gain = BC->config_gain;
    gcr.integration_time = BC->config_integration_time;

	BA->send_blocking_with_timeout(&gcr, sizeof(GetConfigReturn), com);
}

void get_illuminance(const ComType com, const GetIlluminance *data) {
	GetIlluminanceReturn gir;
	gir.header = data->header;
	gir.header.length = sizeof(GetIlluminanceReturn);
	calculate_color_temperature_and_illuminance();
	gir.illuminance = BC->illuminance_current_value;

	BA->send_blocking_with_timeout(&gir, sizeof(GetIlluminanceReturn), com);
}

void get_color_temperature(const ComType com, const GetColorTemperature *data) {
	GetColorTemperatureReturn gctr;
	gctr.header = data->header;
	gctr.header.length = sizeof(GetColorTemperatureReturn);
	calculate_color_temperature_and_illuminance();
	gctr.color_temperature = BC->color_temperature_current_value;

	BA->send_blocking_with_timeout(&gctr, sizeof(GetColorTemperatureReturn), com);
}

void set_illuminance_callback_period(const ComType com, const SetIlluminanceCallbackPeriod *data) {
	BC->signal_period_illuminance = data->period;
	BA->com_return_setter(com, data);
}

void get_illuminance_callback_period(const ComType com, const GetIlluminanceCallbackPeriod *data) {
	GetIlluminanceCallbackPeriodReturn gicpr;
	gicpr.header = data->header;
	gicpr.header.length = sizeof(GetIlluminanceCallbackPeriodReturn);
	gicpr.period = BC->signal_period_illuminance;

	BA->send_blocking_with_timeout(&gicpr, sizeof(GetIlluminanceCallbackPeriodReturn), com);
}

void set_color_temperature_callback_period(const ComType com, const SetColorTemperatureCallbackPeriod *data) {
	BC->signal_period_color_temperature = data->period;
	BA->com_return_setter(com, data);
}

void get_color_temperature_callback_period(const ComType com, const GetColorTemperatureCallbackPeriod *data) {
	GetColorTemperatureCallbackPeriodReturn gctcpr;
	gctcpr.header = data->header;
	gctcpr.header.length = sizeof(GetColorTemperatureCallbackPeriodReturn);
	gctcpr.period = BC->signal_period_color_temperature;

	BA->send_blocking_with_timeout(&gctcpr, sizeof(GetColorTemperatureCallbackPeriodReturn), com);
}

inline uint32_t div_round_closest_unsigned(uint32_t n, uint32_t d) {
    return ((n + d/2)/d);
}

inline int32_t div_round_closest(int32_t n, int32_t d) {
    if((n < 0) ^ (d < 0)) {
        return ((n - d/2)/d);
    }

    return ((n + d/2)/d);
}

void calculate_color_temperature_and_illuminance() {
	BrickContext *BC_local = BC;

	BC_local->illuminance_last_value = BC_local->illuminance_current_value;
	BC_local->color_temperature_last_value = BC_local->color_temperature_current_value;

	const uint16_t value_r = BC_local->last_value1[SIMPLE_UNIT_COLOR];
	const uint16_t value_g = BC_local->last_value2[SIMPLE_UNIT_COLOR];
	const uint16_t value_b = BC_local->last_value3[SIMPLE_UNIT_COLOR];

	if(BC_local->color_temperature_last_value_r == value_r &&
	   BC_local->color_temperature_last_value_g == value_g &&
	   BC_local->color_temperature_last_value_b == value_b) {
		return;
	}

	BC_local->color_temperature_current_value = 0;

	BC_local->color_temperature_last_value_r = value_r;
	BC_local->color_temperature_last_value_g = value_g;
	BC_local->color_temperature_last_value_b = value_b;

    int32_t X = div_round_closest_unsigned(COLOR_TEMPERATURE_MULT_X_G * value_g, COLOR_TEMPERATURE_DIV_X_G) -
                div_round_closest_unsigned(COLOR_TEMPERATURE_MULT_X_R * value_r, COLOR_TEMPERATURE_DIV_X_R) -
                div_round_closest_unsigned(COLOR_TEMPERATURE_MULT_X_B * value_b, COLOR_TEMPERATURE_DIV_X_B);

    int32_t Y = div_round_closest_unsigned(COLOR_TEMPERATURE_MULT_Y_G * value_g, COLOR_TEMPERATURE_DIV_Y_G) -
 	            div_round_closest_unsigned(COLOR_TEMPERATURE_MULT_Y_R * value_r, COLOR_TEMPERATURE_DIV_Y_R) -
                div_round_closest_unsigned(COLOR_TEMPERATURE_MULT_Y_B * value_b, COLOR_TEMPERATURE_DIV_Y_B);

    int32_t Z = div_round_closest_unsigned(COLOR_TEMPERATURE_MULT_Z_G * value_g, COLOR_TEMPERATURE_DIV_Z_G) -
    			div_round_closest_unsigned(COLOR_TEMPERATURE_MULT_Z_R * value_r, COLOR_TEMPERATURE_DIV_Z_R) +
                div_round_closest_unsigned(COLOR_TEMPERATURE_MULT_Z_B * value_b, COLOR_TEMPERATURE_DIV_Z_B);

    BC_local->illuminance_current_value = MAX(0, Y);

    if(X+Y+Z == 0) {
    	return;
    }

    int32_t xc = div_round_closest(X * COLOR_TEMPERATURE_MUL_XC, X + Y + Z);
    int32_t yc = div_round_closest(Y * COLOR_TEMPERATURE_MUL_YC, X + Y + Z);

    if(COLOR_TEMPERATURE_SUB_YC - yc == 0) {
    	return;
    }

    int32_t n_signed = div_round_closest((xc - COLOR_TEMPERATURE_SUB_XC)*COLOR_TEMPERATURE_MUL_N, COLOR_TEMPERATURE_SUB_YC - yc);

    int32_t sign = n_signed < 0 ? -1 : 1;
    uint32_t n = ABS(n_signed);

    uint32_t poly3 = div_round_closest_unsigned(div_round_closest_unsigned(div_round_closest_unsigned(449*n, COLOR_TEMPERATURE_MUL_N)*n, COLOR_TEMPERATURE_MUL_N)*n, COLOR_TEMPERATURE_MUL_N);
    uint32_t poly2 = div_round_closest_unsigned(div_round_closest_unsigned(3525*n, COLOR_TEMPERATURE_MUL_N)*n, COLOR_TEMPERATURE_MUL_N);
    uint32_t poly1 = div_round_closest_unsigned(6823*n, COLOR_TEMPERATURE_MUL_N);

    int32_t result = poly2 + sign*poly3 + sign*poly1 + 5520;
    if(result < 0) {
    	return;
    } else if(result > 0xFFFF) {
    	result = 0xFFFF;
    }

    BC_local->color_temperature_current_value = result;
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

