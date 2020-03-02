/*
 * turn_off_page.cpp
 *
 *  Created on: 21 maj 2018
 *      Author: Mateusz
 */

#include "turn_off_page.h"
#include "../images_data/images.h"
#include "app_logic/app_logic_global.h"
#include "nrf_log.h"

void gl_turn_off_page::init(void) {
	this->turn_off_page_image.set_image(&gl_data::img_turn_off);
	this->turn_off_page_image.set_position(0,0);
	gl_page::init();
}

void gl_turn_off_page::draw(void) {
	this->turn_off_page_image.draw();
}

void gl_turn_off_page::update(void) {

	gl_page::update();
}

gl_turn_off_page::gl_turn_off_page(void) {
}

void gl_turn_off_page::process_input(void) {
	NRF_LOG_INFO("Turn off page input\r\n");
	// Initialize app_logic value
	app_logic_global* global_settings = app_logic_global::get_instance();
	global_settings->is_turn_off_requested = true;
}





