/*
 * buttons.c
 *
 *  Created on: 19 maj 2018
 *      Author: Mateusz
 */

#include "buttons.h"
#include "nrf.h"
#include "custom_board.h"
#include "nrf_drv_gpiote.h"
#include "nrf_drv_ppi.h"
#include "app_error.h"

bool _is_button_left_pressed = false;
bool _is_button_right_pressed = false;

static void _button_left_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action);
static void _button_right_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action);

void buttons_init(void) {
	ret_code_t errCode;

	nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);
	//in_config.pull = NRF_GPIO_PIN_PULLDOWN;

	// Configure left button
	errCode = nrf_drv_gpiote_in_init(
			BUTTON_LEFT_PIN,
			&in_config,
			_button_left_handler);
	APP_ERROR_CHECK(errCode);
	nrf_drv_gpiote_in_event_enable(
			BUTTON_LEFT_PIN,
			true);

	// Configure right button
	errCode = nrf_drv_gpiote_in_init(
			BUTTON_RIGHT_PIN,
			&in_config,
			_button_right_handler);
	APP_ERROR_CHECK(errCode);
	nrf_drv_gpiote_in_event_enable(
			BUTTON_RIGHT_PIN,
			true);

	// Read current buttons state
	if (nrf_drv_gpiote_in_is_set(BUTTON_LEFT_PIN)) {
		_is_button_left_pressed = true;
	} else {
		_is_button_left_pressed = false;
	}

	if (nrf_drv_gpiote_in_is_set(BUTTON_RIGHT_PIN)) {
		_is_button_right_pressed = true;
	} else {
		_is_button_right_pressed = false;
	}
}

bool buttons_is_pressed(button_t button) {
	switch (button) {
	case BUTTON_LEFT:
		return _is_button_left_pressed;
		break;

	case BUTTON_RIGHT:
		return _is_button_right_pressed;
		break;
	}

	return false;
}

static void _button_left_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action) {
	if (nrf_drv_gpiote_in_is_set(BUTTON_LEFT_PIN)) {
		_is_button_left_pressed = true;
	} else {
		_is_button_left_pressed = false;
	}
}

static void _button_right_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action) {
	if (nrf_drv_gpiote_in_is_set(BUTTON_RIGHT_PIN)) {
		_is_button_right_pressed = true;
	} else {
		_is_button_right_pressed = false;
	}
}
