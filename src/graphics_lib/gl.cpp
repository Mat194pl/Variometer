/*
 * gl.c
 *
 *  Created on: 4 kwi 2018
 *      Author: Mateusz
 */

#include "gl.h"
#include "gl_classes/gl_page.h"
#include "gl_types.h"
#include "pages/test_page.h"
#include "pages/battery_status_page.h"
#include "pages/turn_off_page.h"
#include "port/gl_port.h"
#include "app_logic/app_logic_global.h"

gl_test_page test_page;
gl_battery_status_page battery_page;
gl_turn_off_page turn_off_page;

gl* gl::get_instance(void) {
	static gl instance;
	return &instance;
}

gl::gl(void) {
	gl_port_init();

	test_page.init();
	battery_page.init();
	turn_off_page.init();
	current_page = &test_page;

	is_display_on = false;
}

void gl::process(void) {
	if (is_display_on) {
		// Clear screen
		gl_port_clear_screen();

		if (current_page) {
			current_page->update();
			current_page->draw();
		}

		gl_port_update();
	}
}

void gl::turn_display_on(void) {
	gl_port_turn_on_display();
	current_page = &test_page;
	is_display_on = true;
}

void gl::turn_display_off(void) {
	is_display_on = false;
	gl_port_clear_screen();
	gl_port_update();
	// FIXME: Check why this function doesn't work
	gl_port_turn_off_display();
}

void gl::show_next_page(void) {
	if (current_page == &test_page) {
		current_page = &battery_page;
	} else if (current_page == &battery_page) {
		current_page = &turn_off_page;
	} else if (current_page == &turn_off_page) {
		current_page = 0;
		app_logic_global* global_settings = app_logic_global::get_instance();
		global_settings->is_sleep_requested = true;
	}
}

void gl::change_value_in_page(void) {
	if (current_page) {
		current_page->process_input();
	}
}

const gl_type::image_t img_test = {
	.width = 2,
	.height = 2,
	.data = {
		0xFF, 0xFF, 0xFF, 0xFF,
	}
};

