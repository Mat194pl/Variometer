/*
 * ms5611_port.c
 *
 *  Created on: 24 lut 2018
 *      Author: Mateusz
 */


#include "app_twi.h"
#include "custom_board.h"
#include "nordic_common.h"
#include "app_util_platform.h"
#include "nrf_log.h"
#include "nrf_delay.h"

#define MAX_PENDING_TRANSACTIONS    5

static app_twi_t m_app_twi = APP_TWI_INSTANCE(0);

#define MS5611_ADDR 0b1110111

void MS5611_port_init(void) {
	uint32_t err_code;

	nrf_drv_twi_config_t const config = {
			.scl                = MS5611_SCL_PIN,
			.sda                = MS5611_SDA_PIN,
			.frequency          = NRF_TWI_FREQ_100K,
			.interrupt_priority = APP_IRQ_PRIORITY_LOW,
			.clear_bus_init     = false
	};

	APP_TWI_INIT(&m_app_twi, &config, MAX_PENDING_TRANSACTIONS, err_code);
	APP_ERROR_CHECK(err_code);
}

void MS5611_port_read_data(uint8_t* data, uint16_t data_length) {
	if (data)
	{
		app_twi_transfer_t read_transfer[] =
		{
				APP_TWI_READ(MS5611_ADDR, data, data_length, 0)
		};

		ret_code_t ret_code = app_twi_perform(&m_app_twi, read_transfer, 1, NULL);
		UNUSED_VARIABLE(ret_code);
		//NRF_LOG_INFO("Twi read return code: %u\r\n", ret_code);
	}
}

void MS5611_port_write_data(uint8_t* data, uint16_t data_length) {
	if (data)
	{
		app_twi_transfer_t write_transfer[] =
		{
				APP_TWI_WRITE(MS5611_ADDR, data, data_length, 0)
		};

		ret_code_t ret_code = app_twi_perform(&m_app_twi, write_transfer, 1, NULL);
		UNUSED_VARIABLE(ret_code);
		//NRF_LOG_INFO("Twi write return code: %u\r\n", ret_code);
	}
}

void MS5611_delay_ms(uint16_t milliseconds) {
	nrf_delay_ms(milliseconds);
}
