/*
 * test_page.cpp
 *
 *  Created on: 11 maj 2018
 *      Author: Mateusz
 */

#include "test_page.h"
#include "../images_data/letters.h"
#include "../gl_classes/gl_int_nmb_label.h"
#include "../gl_classes/gl_velocity_gauge.h"
#include "app_logic/app_logic_global.h"

gl_object* test_page_objects[1];
gl_int_nmb_label nmb_label;
gl_velocity_gauge vel_gauge;

void gl_test_page::init(void) {
	this->test_image = gl_image(&gl_data::img_zero);

	test_page_objects[0] = &vel_gauge;
	vel_gauge.set_precision_value(1);

	vel_gauge.set_velocity_value(12.34);
	vel_gauge.horizontal_aligment = gl_object::horizontal_aligment::CENTER;
	vel_gauge.vertical_aligment = gl_object::vertical_aligment::CENTER;
	vel_gauge.set_position(32, 24);

//	nmb_label.set_position(32, 24);
//	nmb_label.horizontal_aligment = gl_object::horizontal_aligment::CENTER;
//	nmb_label.vertical_aligment = gl_object::vertical_aligment::CENTER;
//	nmb_label.set_number_value(-234);

	gl_page::init();
}


void gl_test_page::draw(void) {
	vel_gauge.draw();

}

void gl_test_page::update(void) {
	static double last_velocity = 0;

	app_logic_global* global_settings = app_logic_global::get_instance();

	if (global_settings->current_velocity != last_velocity) {
		vel_gauge.set_velocity_value(global_settings->current_velocity);
		last_velocity = global_settings->current_velocity;
	}

	gl_page::update();
}

gl_test_page::gl_test_page(void) {

}

