/*
 * ms5611.c
 *
 *  Created on: 16 lis 2017
 *      Author: Mateusz
 */
#include "ms5611.h"
#include "nrf_log.h"

#ifndef UNUSED
#define UNUSED(x) (void)(x)
#endif

static const uint8_t COMMAND_RESET = 0x1E;
static const uint8_t COMMAND_D1_OSR_4096 = 0x48;
__unused static const uint8_t COMMAND_D2_OSR_2048 = 0x56;
static const uint8_t COMMAND_D2_OSR_4096 = 0x58;
static const uint8_t COMMAND_READ_ADC = 0;

extern void MS5611_port_init(void);
extern void MS5611_port_read_data(uint8_t* data, uint16_t data_length);
extern void MS5611_port_write_data(uint8_t* data, uint16_t data_length);
extern void MS5611_delay_ms(uint16_t milliseconds);

static void reset(void);
static uint16_t read_prom(uint8_t prom_address);
static uint32_t read_adc(void);

/**
 * @brief Calibration data structure
 */
static struct calibration_data {
		uint16_t pressure_sensivity;	/**< Pressure sensivity */
		uint16_t pressure_offset;		/**< Pressure offset */
		uint16_t tcs;	/**< Temperature coefficient of pressure sensitivity */
		uint16_t tco;	/**< Temperature coefficient of pressure offset */
		uint16_t reference_temperature; /**< Reference temperature */
		uint16_t tct; /**< Temperature coefficient of the temperature */
} calibration_data;

void ms5611_init(void)
{
	MS5611_port_init();

	reset();

	// Get calibration data
	calibration_data.pressure_sensivity = read_prom(0);
	calibration_data.pressure_offset = read_prom(2);
	calibration_data.tcs = read_prom(4);
	calibration_data.tco = read_prom(6);
	calibration_data.reference_temperature = read_prom(8);
	calibration_data.tct = read_prom(10);
}

ms5611_data_t ms5611_get_measures(void) {
	ms5611_data_t result;

	MS5611_port_write_data((uint8_t[]){ COMMAND_D1_OSR_4096 }, 1);

	MS5611_delay_ms(10);

	uint32_t d1 = read_adc();

	MS5611_port_write_data((uint8_t[]){ COMMAND_D2_OSR_4096 }, 1);

	MS5611_delay_ms(10);

	uint32_t d2 = read_adc();

	int32_t dT = (d2 - ((uint32_t)calibration_data.reference_temperature * 256));

	int32_t temp =  2000 + ((int64_t)dT * calibration_data.tct) / 8388608;

	// compensate temperature
	if (temp < 2000)
	{
		temp = temp - (dT * dT) / (2 << 30);
	}

	// compute pressure

	int64_t off = (int64_t)calibration_data.pressure_offset * 65536 + (int64_t)calibration_data.tco * dT / 128;
	int64_t sens = (int64_t)calibration_data.pressure_sensivity * 32768 + (int64_t)calibration_data.tcs * dT / 256;

	// compensate pressure

	int64_t off2 = 0;
	int64_t sens2 = 0;

	if (temp < 2000)
	{
		off2 = 5 * ((temp - 2000) * (temp - 2000)) / 2;
		sens2 = 5 * ((temp - 2000) * (temp - 2000)) / 4;
	}

	if (temp < -1500)
	{
		off2 = off2 + 7 * ((temp + 1500) * (temp + 1500));
		sens2 = sens2 + 11 * ((temp + 1500) * (temp + 1500)) / 2;
	}

	off = off - off2;
	sens = sens - sens2;

	uint32_t pressure = (d1 * sens / 2097152 - off) / 32768;

	result.temperature = ((float)(temp));
	result.pressure = ((pressure));

	return result;
}

static void reset(void)
{
	MS5611_port_write_data((uint8_t[]){ COMMAND_RESET }, 1);
	MS5611_delay_ms(5);
}

static uint16_t read_prom(uint8_t prom_address) {
	uint8_t received_data[2];

	MS5611_port_write_data((uint8_t[]){0xA2 + prom_address}, 1);
	MS5611_port_read_data((uint8_t*)(&received_data), 2);

	return (uint16_t)(received_data[0] << 8) + (uint16_t)received_data[1];
}

static uint32_t read_adc(void) {
	uint8_t received_data[3];

	MS5611_port_write_data((uint8_t[]){COMMAND_READ_ADC}, 1);
	MS5611_port_read_data((uint8_t*)(&received_data), 3);

	return ((uint32_t)received_data[0] << 16) + ((uint32_t)received_data[1] << 8) + ((uint32_t)received_data[2] << 0);
}

