/* color-bricklet
 * Copyright (C) 2014 Ishraq Ibne Ashraf <ishraq@tinkerforge.com>
 * Copyright (C) 2014 Olaf Lüke <olaf@tinkerforge.com>
 *
 * color.h: Implementation of Color Bricklet messages
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

#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

#include "bricklib/com/com_common.h"

// function IDs
#define FID_GET_COLOR 1
#define FID_SET_COLOR_CALLBACK_PERIOD 2
#define FID_GET_COLOR_CALLBACK_PERIOD 3
#define FID_SET_COLOR_CALLBACK_THRESHOLD 4
#define FID_GET_COLOR_CALLBACK_THRESHOLD 5
#define FID_SET_DEBOUNCE_PERIOD 6
#define FID_GET_DEBOUNCE_PERIOD 7
#define FID_COLOR 8
#define FID_COLOR_REACHED 9
#define FID_LIGHT_ON 10
#define FID_LIGHT_OFF 11
#define FID_IS_LIGHT_ON 12
#define FID_SET_CONFIG 13
#define FID_GET_CONFIG 14
#define FID_GET_ILLUMINANCE 15
#define FID_GET_COLOR_TEMPERATURE 16

#define FID_LAST 16

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) LightOn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) LightOff;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) IsLightOn;

typedef struct {
	MessageHeader header;
    uint8_t light;
} __attribute__((__packed__)) IsLightOnReturn;

typedef struct {
	MessageHeader header;
    uint8_t gain;
    uint8_t integration_time;
} __attribute__((__packed__)) SetConfig;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetConfig;

typedef struct {
	MessageHeader header;
    uint8_t gain;
    uint8_t integration_time;
} __attribute__((__packed__)) GetConfigReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetIlluminance;

typedef struct {
	MessageHeader header;
    uint32_t illuminance;
} __attribute__((__packed__)) GetIlluminanceReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetColorTemperature;

typedef struct {
	MessageHeader header;
    uint32_t color_temperature;
} __attribute__((__packed__)) GetColorTemperatureReturn;

void light_on(const ComType com, const LightOn *data);
void light_off(const ComType com, const LightOff *data);
void is_light_on(const ComType com, const IsLightOn *data);
void set_config(const ComType com, const SetConfig *data);
void get_config(const ComType com, const GetConfig *data);
void get_illuminance(const ComType com, const GetIlluminance *data);
void get_color_temperature(const ComType com, const GetColorTemperature *data);

void invocation(const ComType com, const uint8_t *data);
void constructor(void);
void destructor(void);
void tick(const uint8_t tick_type);

inline int32_t div_round_closest(int32_t n, int32_t d);
inline uint32_t div_round_closest_unsigned(uint32_t n, uint32_t d);
int32_t calculate_illuminance();
uint16_t calculate_color_temperature();

void read_registers(const uint8_t reg, uint8_t *data, const uint8_t length);
void clear_interrupt();
void write_register(const uint8_t reg, uint8_t value);
bool i2c_scl_value(void);
void i2c_scl_high(void);
void i2c_scl_low(void);
bool i2c_sda_value(void);
void i2c_sda_high(void);
void i2c_sda_low(void);
void i2c_sleep_halfclock(void);
void i2c_stop(void);
void i2c_start(void);
uint8_t i2c_recv_byte(bool ack);
bool i2c_send_byte(const uint8_t value);

#endif
