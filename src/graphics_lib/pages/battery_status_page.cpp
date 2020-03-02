/*
 * battery_status_page.cpp
 *
 *  Created on: 20 maj 2018
 *      Author: Mateusz
 */

#include "battery_status_page.h"
#include "mtimer/mtimer.h"
#include "../images_data/letters.h"
#include "app_logic/app_logic_global.h"

void gl_battery_status_page::init(void) {
	this->battery_value_label.init();
	this->battery_value_label.set_position(45,5);
	this->battery_value_label.horizontal_aligment = gl_object::horizontal_aligment::CENTER;
	this->percentage_image.set_image(&gl_data::img_percentage);
	this->percentage_image.set_position(45,25);
	this->percentage_image.horizontal_aligment = gl_object::horizontal_aligment::CENTER;
	gl_page::init();
}

void gl_battery_status_page::draw(void) {
	this->battery_value_label.draw();
	this->battery_gauge.draw();
	this->percentage_image.draw();
}

void gl_battery_status_page::update(void) {
	app_logic_global* global_settings = app_logic_global::get_instance();

	this->battery_value_label.set_number_value(global_settings->battery_level);
	this->battery_gauge.set_battery_percentage_value(global_settings->battery_level);

	gl_page::update();
}

gl_battery_status_page::gl_battery_status_page(void) {
	battery_percentage_value = 0;
}

