/*
 * app_logic.cpp
 *
 *  Created on: 20 maj 2018
 *      Author: Mateusz
 */

#include "app_logic.h"
#include "app_logic_global.h"
#include "app_timer.h"
#include "../drivers/buttons/buttons.h"
#include "../drivers/MS5611/ms5611.h"
#include "../drivers/power/power.h"
#include "../mtimer/mtimer.h"
#include "../drivers/watchdog/watchdog.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "app_util_platform.h"
#include "ble/ble_p.h"
#include "nmea/nmea.h"

#define APP_TIMER_PRESCALER 0
#define APP_TIMER_OP_QUEUE_SIZE 10
#define BOOTLOADER_DFU_START    0xB1    /**< Value of flag for starting bootloader */

static void buzzer_timer_callback_priv(void* context);
static void gui_timer_callback_priv(void* context);
static void data_acquisition_timer_callback_priv(void* context);
static void watchdog_timer_callback_priv(void* context);
static void enter_bootloader(void);

const double b1 = 0.0200833655642112;
const double b2 = 0.0401667311284225;
const double b3 = 0.0200833655642112;
const double a2 = -1.561018075800718;
const double a3 = 0.641351538057563;

static double filter_process(double x);

app_logic& app_logic::get_instance(void) {
	static app_logic instance;
	return instance;
}

app_logic::app_logic(void) {
	NRF_LOG_INFO("app_logic init\r\n");

	// Initialize power control functions
	power_init();
	power_turn_on();

	// Initialize app_logic value
	app_logic_global* global_settings = app_logic_global::get_instance();
	global_settings->battery_level = 50;
	global_settings->is_sleep_requested = false;
	global_settings->is_turn_off_requested = false;
	global_settings->current_velocity = 0.0;
	global_settings->battery_voltage = 3500;

	// Turn off buzzer velocity beeping
	global_settings->is_velocity_buzzer_enabled = false;

	// Clear watchdog
	watchdog_clear();

	// Initialize milliseconds timer
	mtimer_init();

	// Initialize MS5611 barometric pressure sensor
	ms5611_init();

	// Initialize buttons
	buttons_init();

	// Initialize graphics library and OLED display
	graphic_drv = gl::get_instance();

	// Initialize buzzer driver
	buzzer_drv = buzzer::get_instance();

	// Initialize battery driver
	battery_drv = battery::get_instance();

	// Create timer for buzzer processing
	app_timer_create(&(this->buzzer_timer_id), APP_TIMER_MODE_REPEATED, buzzer_timer_callback_priv);

	// Start buzzer processing timer
	app_timer_start(this->buzzer_timer_id, APP_TIMER_TICKS(20, APP_TIMER_PRESCALER), NULL);

	// Create GUI and buttons timer
	app_timer_create(&(this->gui_timer_id), APP_TIMER_MODE_REPEATED, gui_timer_callback_priv);

	// Start GUI and buttons timer
	app_timer_start(this->gui_timer_id, APP_TIMER_TICKS(100, APP_TIMER_PRESCALER), NULL);

	// Create data acquisition timer
	app_timer_create(&(this->data_acquisition_timer_id), APP_TIMER_MODE_REPEATED, data_acquisition_timer_callback_priv);

	// Start data acquisition timer
	app_timer_start(this->data_acquisition_timer_id, APP_TIMER_TICKS(100, APP_TIMER_PRESCALER), NULL);

	// Create watchdog timer
	app_timer_create(&(this->watchdog_timer_id), APP_TIMER_MODE_REPEATED, watchdog_timer_callback_priv);

	// Start watchdog timer
	app_timer_start(this->watchdog_timer_id, APP_TIMER_TICKS(500, APP_TIMER_PRESCALER), NULL);

	gui_timer_flag = false;
	process_pressure_flag = false;

	app_state = app_state_t::INIT;
}

void app_logic::process(void) {
	uint32_t current_timestamp = mtimer_get_current_timestamp();
	static bool last_button_left_state = false;
	static bool first_diff_skip = true;
	bool button_left_state = false;
	static bool last_button_right_state = false;
	bool button_right_state = false;
	static uint32_t last_pressure = 0;

	app_logic_global* global_settings = app_logic_global::get_instance();

	if (app_state != app_state_t::INIT && process_pressure_flag) {
		ms5611_data_t data = ms5611_get_measures();

		battery_drv->start_sampling();

		if (first_diff_skip) {
			first_diff_skip = false;
		} else {
			int diff = ((int)last_pressure - (int)data.pressure);
			double diff_f = (double)diff;
			// Convert Pa to meters
			diff_f *= 0.08849557522123893805309734513274;
			diff_f *= 10.0;

			diff_f = filter_process(diff_f);
			global_settings->current_velocity = (float)diff_f;
			buzzer_drv->set_velocity(diff_f);
			int velocity_int = (int)(diff_f * 10.0);
			static uint8_t tt = 0;

			nmea_send_velocity((float)diff_f);

			//NRF_LOG_INFO("VEL: %d\r\n", velocity_int);
		}
		last_pressure = data.pressure;
		process_pressure_flag = false;
	}

	switch (app_state) {
	case app_state_t::INIT:
		if (current_timestamp > 1000) {
			buzzer_drv->set_frequency(0);
			app_state = app_state_t::GUI_MENU;
			last_button_left_state = true;
			graphic_drv->turn_display_on();
			NRF_LOG_INFO("Change state to GUI_MENU\r\n");
			global_settings->is_velocity_buzzer_enabled = true;
		} else if (current_timestamp > 900) {
			buzzer_drv->set_frequency(440);
		} else if (current_timestamp > 800) {
			buzzer_drv->set_frequency(0);
		} else if (current_timestamp > 700) {
			buzzer_drv->set_frequency(440);
		} else {
//			if (!(buttons_is_pressed(BUTTON_LEFT) && buttons_is_pressed(BUTTON_RIGHT))) {
//				NRF_LOG_INFO("Power OFF\r\n");
//				power_turn_off();
//				while(1) {
//					NRF_LOG_PROCESS();
//				}
//			}
		}

		break;

	case app_state_t::GUI_MENU:
		if (gui_timer_flag) {
			button_left_state = buttons_is_pressed(BUTTON_LEFT);
			button_right_state = buttons_is_pressed(BUTTON_RIGHT);

			if (button_left_state && (!last_button_left_state)) {
				graphic_drv->show_next_page();
			}

			if (button_right_state && (!last_button_right_state)) {
				//enter_bootloader();
				graphic_drv->change_value_in_page();
				NRF_LOG_INFO("Change value in page\r\n");
			}

			if (global_settings->is_sleep_requested) {
				global_settings->is_sleep_requested = false;
				NRF_LOG_INFO("Change state to GUI_SLEEP\r\n");
				graphic_drv->turn_display_off();
				app_state = app_state_t::GUI_SLEEP;
				last_button_left_state = true;
				last_button_right_state = true;
				return;
			}

			if (global_settings->is_turn_off_requested) {
				global_settings->is_turn_off_requested = false;
				NRF_LOG_INFO("Power OFF request\r\n");
				power_turn_off();
			}

			graphic_drv->process();

			gui_timer_flag = false;
			last_button_left_state = button_left_state;
			last_button_right_state = button_right_state;
		}
		break;

	case app_state_t::GUI_SLEEP:
		if (gui_timer_flag) {
			button_left_state = buttons_is_pressed(BUTTON_LEFT);
			button_right_state = buttons_is_pressed(BUTTON_RIGHT);

			if ((button_left_state && (!last_button_left_state)) ||
				(button_right_state && (!last_button_right_state))) {
				app_state = app_state_t::GUI_MENU;
				NRF_LOG_INFO("Change state to GUI_MENU\r\n");
				last_button_left_state = true;
				graphic_drv->turn_display_on();
			}

			last_button_left_state = button_left_state;
			last_button_right_state = button_right_state;

			gui_timer_flag = false;
		}
		break;
	}
}

void app_logic::buzzer_timer_callback(void) {
	buzzer_drv->update();
}

void app_logic::gui_timer_callback(void) {
	gui_timer_flag = true;
}

void app_logic::data_acquisition_timer_callback(void) {
	process_pressure_flag = true;
}

static void buzzer_timer_callback_priv(void* context) {
	app_logic_global* app_global = app_logic_global::get_instance();
	if (app_global->is_velocity_buzzer_enabled) {
		app_logic& app = app_logic::get_instance();
		app.buzzer_timer_callback();
	}
}

static void gui_timer_callback_priv(void* context) {
	app_logic& app = app_logic::get_instance();
	app.gui_timer_callback();
}

static void data_acquisition_timer_callback_priv(void* context) {
	app_logic& app = app_logic::get_instance();
	app.data_acquisition_timer_callback();
}

static void watchdog_timer_callback_priv(void* context) {
	watchdog_clear();
}

static double filter_process(double x) {
	static double fx[3] = { 0.0, 0.0, 0.0 };
	static double fy[3] = { 0.0, 0.0, 0.0 };

	for (uint8_t i = 2; i > 0; i--) {
		fx[i] = fx[i - 1];
		fy[i] = fy[i - 1];
	}

	fx[0] = x;

	fy[0] = b1 * fx[0] + b2 * fx[1] + b3 * fx[2]
					   - a2 * fy[1] - a3 * fy[2];

	return fy[0];
}

static void enter_bootloader(void) {
	uint32_t errCode;
	uint32_t d;

	do {
		errCode = sd_power_gpregret_clr(0xFF);
		if (errCode != NRF_SUCCESS) {
			ASSERT(false);
		}

		errCode = sd_power_gpregret_set(BOOTLOADER_DFU_START);
		if (errCode != NRF_SUCCESS) {
			ASSERT(false);
		}
		sd_power_gpregret_get(&d);
	} while (d != BOOTLOADER_DFU_START);

	sd_nvic_SystemReset();

}

