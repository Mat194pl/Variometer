/*
 * app_logic_global.h
 *
 *  Created on: 21 maj 2018
 *      Author: Mateusz
 */

#ifndef SRC_APP_LOGIC_APP_LOGIC_GLOBAL_H_
#define SRC_APP_LOGIC_APP_LOGIC_GLOBAL_H_

#include <stdint.h>
#include <stdbool.h>

class app_logic_global {
public:
	static app_logic_global* get_instance(void);

	uint8_t battery_level; // %
	bool is_turn_off_requested;
	bool is_sleep_requested;
	bool is_velocity_buzzer_enabled;
	float current_velocity; // m/s
	uint32_t battery_voltage; // mV
};

#endif /* SRC_APP_LOGIC_APP_LOGIC_GLOBAL_H_ */
