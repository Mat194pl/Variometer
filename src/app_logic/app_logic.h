/*
 * app_logic.h
 *
 *  Created on: 20 maj 2018
 *      Author: Mateusz
 */

#ifndef SRC_APP_LOGIC_APP_LOGIC_H_
#define SRC_APP_LOGIC_APP_LOGIC_H_

#include "graphics_lib/gl.h"
#include "drivers/buzzer/buzzer.h"
#include "drivers/battery/battery.h"
#include "app_timer.h"

class app_logic {
public:
	static app_logic& get_instance(void);
	void process(void);
	void buzzer_timer_callback(void);
	void gui_timer_callback(void);
	void data_acquisition_timer_callback(void);

private:
	app_logic(void);
	app_logic(app_logic const&);
	void operator=(app_logic const&);

	typedef enum {
		INIT,
		GUI_MENU,
		GUI_SLEEP
	} app_state_t;

	app_state_t app_state;

	gl* graphic_drv;
	buzzer* buzzer_drv;
	battery* battery_drv;

	app_timer_t buzzer_timer_id_data = { {0} };
	const app_timer_id_t buzzer_timer_id = &buzzer_timer_id_data;

	app_timer_t gui_timer_id_data = { {0} };
	const app_timer_id_t gui_timer_id = &gui_timer_id_data;

	app_timer_t data_acquisition_timer_id_data = { {0} };
	const app_timer_id_t data_acquisition_timer_id = &data_acquisition_timer_id_data;

	app_timer_t watchdog_timer_id_data = { {0} };
	const app_timer_id_t watchdog_timer_id = &watchdog_timer_id_data;

	bool gui_timer_flag;
	bool process_pressure_flag;
};

#endif /* SRC_APP_LOGIC_APP_LOGIC_H_ */
