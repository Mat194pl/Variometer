/*
 * ssd1306bz_port.c
 *
 *  Created on: 2 mar 2018
 *      Author: Mateusz
 */


#include "app_twi.h"
#include "custom_board.h"
#include "nordic_common.h"
#include "app_util_platform.h"
#include "nrf_log.h"
#include "nrf_delay.h"
#include "nrf_drv_gpiote.h"
#include <stdbool.h>
#include <stdint.h>

#define MAX_PENDING_TRANSACTIONS    5
#define SSD1306BZ_ADDR 0b0111100

static app_twi_t m_app_twi = APP_TWI_INSTANCE(1);
static bool _is_initialized = false;

void SSD1306BZ_port_init(void) {
	if (!_is_initialized) {
		_is_initialized = true;
		uint32_t err_code;

		nrf_drv_twi_config_t const config = {
				.scl                = SSD1306BZ_SCL_PIN,
				.sda                = SSD1306BZ_SDA_PIN,
				.frequency          = NRF_TWI_FREQ_100K,
				.interrupt_priority = APP_IRQ_PRIORITY_LOWEST,
				.clear_bus_init     = false
		};

		APP_TWI_INIT(&m_app_twi, &config, MAX_PENDING_TRANSACTIONS, err_code);
		APP_ERROR_CHECK(err_code);

		nrf_drv_gpiote_out_config_t out_config = GPIOTE_CONFIG_OUT_SIMPLE(false);
		err_code = nrf_drv_gpiote_out_init(SSD1306BZ_RESET_PIN, &out_config);
		APP_ERROR_CHECK(err_code);

		err_code = nrf_drv_gpiote_out_init(SSD1306BZ_LCD_ON_PIN, &out_config);
		APP_ERROR_CHECK(err_code);
	}
}

void SSD1306BZ_port_set_reset(bool state) {
	if (state) {
		nrf_gpio_pin_set(SSD1306BZ_RESET_PIN);
	} else {
		nrf_gpio_pin_clear(SSD1306BZ_RESET_PIN);
	}
}

void SSD1306BZ_port_set_lcd_on(bool state) {
	if (state) {
		nrf_gpio_pin_clear(SSD1306BZ_LCD_ON_PIN);
	} else {
		nrf_gpio_pin_set(SSD1306BZ_LCD_ON_PIN);
	}
}

void SSD1306BZ_port_read_data(uint8_t* data, uint16_t data_length) {
	if (data)
	{
		app_twi_transfer_t read_transfer[] =
		{
				APP_TWI_READ(SSD1306BZ_ADDR, data, data_length, 0)
		};

		ret_code_t ret_code = app_twi_perform(&m_app_twi, read_transfer, 1, NULL);
		UNUSED_VARIABLE(ret_code);
		//NRF_LOG_INFO("Twi read return code: %u\r\n", ret_code);
	}
}

void SSD1306BZ_port_write_data(uint8_t* data, uint16_t data_length) {
	if (data)
	{
		app_twi_transfer_t write_transfer[] =
		{
				APP_TWI_WRITE(SSD1306BZ_ADDR, data, data_length, 0)
		};

		ret_code_t ret_code = app_twi_perform(&m_app_twi, write_transfer, 1, NULL);
		UNUSED_VARIABLE(ret_code);
		//NRF_LOG_INFO("Twi write return code: %u\r\n", ret_code);
	}
}

void SSD1306BZ_delay_ms(uint16_t milliseconds) {
	nrf_delay_ms(milliseconds);
}
