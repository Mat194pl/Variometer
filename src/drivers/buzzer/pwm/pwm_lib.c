/*
 * pwm_lib.c
 *
 *  Created on: 16 kwi 2018
 *      Author: Mateusz
 */

#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "app_pwm.h"
#include "custom_board.h"
#include "pwm_lib.h"
#include "nrf_drv_gpiote.h"
#include "nrf_log.h"

APP_PWM_INSTANCE(PWM1,1);                   // Create the instance "PWM1" using TIMER1.

static volatile bool ready_flag;            // A flag indicating PWM status.

// PWM callback function
static void pwm_ready_callback(uint32_t pwm_id) {
    ready_flag = true;
}

void pwm_init(void) {
//	 ret_code_t err_code;

//	 nrf_drv_gpiote_out_config_t out_config = GPIOTE_CONFIG_OUT_SIMPLE(false);
//	 err_code = nrf_drv_gpiote_out_init(BUZZER_GND_PIN, &out_config);
//	 APP_ERROR_CHECK(err_code);

	 /* 2-channel PWM, 200Hz */
//	 app_pwm_config_t pwm1_cfg = APP_PWM_DEFAULT_CONFIG_2CH(5000L, BUZZER_VCC_PIN, BUZZER_GND_PIN);
//
//	 /* Switch the polarity of the second channel. */
//	 pwm1_cfg.pin_polarity[1] = APP_PWM_POLARITY_ACTIVE_HIGH;
//
//	 /* Initialize and enable PWM. */
//	 err_code = app_pwm_init(&PWM1, &pwm1_cfg, pwm_ready_callback);
//	 APP_ERROR_CHECK(err_code);
//
//	 app_pwm_enable(&PWM1);
//
//	 while (app_pwm_channel_duty_set(&PWM1, 0, 50) == NRF_ERROR_BUSY);
}

void pwm_set_frequency(uint32_t frequency) {
	static uint32_t last_frequency = 0;

	if (last_frequency == frequency) {
		return;
	}

	last_frequency = frequency;

	ret_code_t err_code;
	uint32_t value = 5000 * 200;

	NRF_LOG_INFO("Buzzer set frequency %u\r\n", frequency);

	if (0 == frequency) {
		app_pwm_disable(&PWM1);
		return;
	}

	value /= frequency;

	/* 2-channel PWM, 200Hz */
	app_pwm_config_t pwm1_cfg = APP_PWM_DEFAULT_CONFIG_2CH(value, BUZZER_VCC_PIN, BUZZER_GND_PIN);

	/* Switch the polarity of the second channel. */
	pwm1_cfg.pin_polarity[1] = APP_PWM_POLARITY_ACTIVE_HIGH;

	app_pwm_uninit(&PWM1);
	err_code = app_pwm_init(&PWM1, &pwm1_cfg, pwm_ready_callback);
	app_pwm_enable(&PWM1);

	UNUSED_VARIABLE(err_code);

	//APP_ERROR_CHECK(err_code);
	while (app_pwm_channel_duty_set(&PWM1, 0, 50) == NRF_ERROR_BUSY);
}

