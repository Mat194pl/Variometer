/*
 * battery.cpp
 *
 *  Created on: 3 maj 2018
 *      Author: Mateusz
 */

#include "battery.h"
#include "nrf.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "nrf_drv_adc.h"
#include "nordic_common.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "app_error.h"
#include "app_logic/app_logic_global.h"

#define ADC_BUFFER_SIZE 1                                /**< Size of buffer for ADC samples.  */
static nrf_adc_value_t       adc_buffer[ADC_BUFFER_SIZE]; /**< ADC buffer. */
static nrf_drv_adc_channel_t m_channel_config;  /**< Channel instance. Default configuration used. */

#define BATTERY_0_LEVEL_VOLTAGE_VALUE	3000
#define BATTERY_100_LEVEL_VOLTAGE_VALUE	4000

/**
 * @brief ADC interrupt handler.
 */
static void _adc_event_handler(nrf_drv_adc_evt_t const * p_event);

/**
 * @brief Start ADC sampling
 */
static void _adc_sample(void);

static uint8_t _percentage_value;

battery* battery::get_instance(void) {
	static battery instance;
	return &instance;
}

battery::battery() {
	// Config ADC
    ret_code_t ret_code;
    nrf_drv_adc_config_t config = NRF_DRV_ADC_DEFAULT_CONFIG;

    ret_code = nrf_drv_adc_init(&config, _adc_event_handler);
    APP_ERROR_CHECK(ret_code);

    m_channel_config.config.config.resolution = NRF_ADC_CONFIG_RES_10BIT;
    m_channel_config.config.config.input = NRF_ADC_CONFIG_SCALING_INPUT_ONE_THIRD;
	m_channel_config.config.config.reference = ADC_CONFIG_REFSEL_VBG;
	m_channel_config.config.config.ain = NRF_ADC_CONFIG_INPUT_2;

    nrf_drv_adc_channel_enable(&m_channel_config);

    _percentage_value = 100;
}

void battery::start_sampling(void) {
	_adc_sample();
}

uint8_t battery::get_percentage_value(void) {
	return _percentage_value;
}

static void _adc_sample(void) {
	ret_code_t ret_code;

    ret_code = nrf_drv_adc_buffer_convert(adc_buffer, ADC_BUFFER_SIZE);        // Allocate buffer for ADC
    APP_ERROR_CHECK(ret_code);

    while((NRF_ADC->BUSY & ADC_BUSY_BUSY_Msk) == ADC_BUSY_BUSY_Busy) {}    //Wait until the ADC is finished sampling
    nrf_drv_adc_sample();
//
//    for (uint32_t i = 0; i < ADC_BUFFER_SIZE; i++)
//    {
//        while((NRF_ADC->BUSY & ADC_BUSY_BUSY_Msk) == ADC_BUSY_BUSY_Busy) {}    //Wait until the ADC is finished sampling
//        printf("Start sampling ... \r\n");
//        nrf_drv_adc_sample();
//    }
}

static void _adc_event_handler(nrf_drv_adc_evt_t const * p_event) {
    if (p_event->type == NRF_DRV_ADC_EVT_DONE) {
    	uint32_t i;
    	app_logic_global* global_settings = app_logic_global::get_instance();

        for (i = 0; i < p_event->data.done.size; i++) {
            // Convert ADC value to voltage value
            uint32_t voltage = ((1000 * (p_event->data.done.p_buffer[i])) / 133) - 98;
            //NRF_LOG_INFO("Current voltage: %u\r\n", voltage);
            global_settings->battery_voltage = voltage;

            // Convert voltage value to percentage
            if (voltage < 3000) {
            	voltage = 3000;
            }

            if (voltage > 4000) {
            	voltage = 4000;
            }

            voltage -= 3000;
            uint32_t full_scale = BATTERY_100_LEVEL_VOLTAGE_VALUE - BATTERY_0_LEVEL_VOLTAGE_VALUE;
            uint32_t percentage = (voltage * 100) / full_scale;

            if (percentage > 100) {
            	percentage = 100;
            }

            global_settings->battery_level = (uint8_t)percentage;
        }
    }
}
