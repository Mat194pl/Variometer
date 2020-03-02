/*
 * gl_battery_gauge.cpp
 *
 *  Created on: 20 maj 2018
 *      Author: Mateusz
 */

#include "gl_battery_gauge.h"
#include "../images_data/images.h"
#include "../port/gl_port.h"

void gl_battery_gauge::init(void) {

}

void gl_battery_gauge::update(void) {

}

void gl_battery_gauge::draw(void) {
	int16_t draw_pos_x = this->pos_x;
	int16_t draw_pos_y = this->pos_y;

	int16_t whole_width = this->width;

	switch (horizontal_aligment) {
	case gl_object::horizontal_aligment::LEFT:

		break;

	case gl_object::horizontal_aligment::CENTER:
		draw_pos_x -= whole_width / 2;
		break;

	case gl_object::horizontal_aligment::RIGHT:
		draw_pos_x -= whole_width;
		break;
	}

	switch (vertical_aligment) {
	case gl_object::vertical_aligment::TOP:

		break;

	case gl_object::vertical_aligment::CENTER:
		draw_pos_y -= this->height / 2;
		break;

	case gl_object::vertical_aligment::BOTTOM:
		draw_pos_y -= this->height;
		break;
	}

	// Battery gauge image
	gl_port_draw_image(
			draw_pos_x,
			draw_pos_y,
			gl_data::img_battery.width,
			gl_data::img_battery.height,
			gl_data::img_battery.data);

	// Draw battery lines
	for (uint8_t i = 0; i < this->nmb_of_lines_to_draw; i++) {
		gl_port_draw_image(
				draw_pos_x + 3,
				draw_pos_y + 38 - i,
				gl_data::img_battery_line.width,
				gl_data::img_battery_line.height,
				gl_data::img_battery_line.data);
	}
}

gl_battery_gauge::gl_battery_gauge(void) {
	this->percentage_value = 0;
	this->nmb_of_lines_to_draw = 0;
	this->width = gl_data::img_battery.width;
	this->height = gl_data::img_battery.height;
}

void gl_battery_gauge::set_battery_percentage_value(uint8_t percentage_value) {
	if (percentage_value > 100) return;
	this->percentage_value = percentage_value;
	this->nmb_of_lines_to_draw = percentage_value / 3;

	if (this->nmb_of_lines_to_draw > 33) {
		this->nmb_of_lines_to_draw = 33;
	}
}
