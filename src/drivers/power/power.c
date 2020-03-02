/*
 * power.c
 *
 *  Created on: 16 maj 2018
 *      Author: Mateusz
 */

#include "power.h"
#include "nrf.h"
#include "nrf_drv_gpiote.h"
#include "custom_board.h"

void power_init(void) {
	ret_code_t err_code;

	nrf_drv_gpiote_out_config_t out_config = GPIOTE_CONFIG_OUT_SIMPLE(true);
	err_code = nrf_drv_gpiote_out_init(POWER_ON_OFF_PIN, &out_config);
	APP_ERROR_CHECK(err_code);
}

void power_turn_on(void) {
	nrf_drv_gpiote_out_set(POWER_ON_OFF_PIN);
}

void power_turn_off(void) {
	nrf_drv_gpiote_out_clear(POWER_ON_OFF_PIN);
}
