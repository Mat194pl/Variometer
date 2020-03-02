/*
 * gl_velocity_gauge.cpp
 *
 *  Created on: 12 maj 2018
 *      Author: Mateusz
 */

#include "gl_velocity_gauge.h"
#include "../images_data/letters.h"
#include "../port/gl_port.h"
#include <math.h>

void gl_velocity_gauge::init(void) {

}

void gl_velocity_gauge::update(void) {

}

void gl_velocity_gauge::draw(void) {
	int16_t draw_pos_x = this->pos_x;
	int16_t draw_pos_y = this->pos_y;
	int16_t vel_off_x = 0;
	int16_t vel_off_y = 16;
	int16_t digits_offset_x = 0;

	int16_t whole_width = 53;

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
		draw_pos_y -= 31 / 2;
		break;

	case gl_object::vertical_aligment::BOTTOM:
		draw_pos_y -= 31;
		break;
	}

	vel_off_x = whole_width - gl_data::img_velocity.width;
	vel_off_x /= 2;

	digits_offset_x = whole_width - this->length_of_velocity_digits;
	digits_offset_x /= 2;

	// Draw m/s
	gl_port_draw_image(
			draw_pos_x + vel_off_x,
			draw_pos_y + vel_off_y,
			gl_data::img_velocity.width,
			gl_data::img_velocity.height,
			gl_data::img_velocity.data);

	// Draw integral part
	uint8_t offset = digits_offset_x;
	integral_nmb.set_position(draw_pos_x + offset, draw_pos_y);
	integral_nmb.draw();

	offset += integral_nmb.get_width();

	// Draw comma
	gl_port_draw_image(
			draw_pos_x + offset,
			draw_pos_y,
			gl_data::img_comma.width,
			gl_data::img_comma.height,
			gl_data::img_comma.data);

	offset += gl_data::img_comma.width;

	// Draw decimal part
	decimal_nmb.set_position(draw_pos_x + offset, draw_pos_y);
	decimal_nmb.draw();
}

gl_velocity_gauge::gl_velocity_gauge(void) {
	this->integral_nmb.set_number_value(0);
	this->decimal_nmb.set_number_value(0);
	this->precision = 2;
	this->velocity_value = 0.0;
	this->length_of_velocity_digits = 0;
}

void gl_velocity_gauge::set_velocity_value(float velocity_value) {
	this->velocity_value = velocity_value;

	// Extract decimal and integer part
	int integral_part = (int)velocity_value;
	int decimal_part = 0;

	if (this->precision > 0) {
		float decimal_value = velocity_value - integral_part;
		float multipler = pow(10.0, (int)(this->precision));
		decimal_value *= multipler;
		decimal_part = (int)abs(decimal_value);
	}

	this->integral_nmb.set_number_value(integral_part);
	if (velocity_value < 0) {
		this->integral_nmb.set_is_number_negative(true);
	}
	this->decimal_nmb.set_number_value(decimal_part);

	// Compute length of velocity digits
	this->length_of_velocity_digits = 0;
	this->length_of_velocity_digits += integral_nmb.get_width();
	this->length_of_velocity_digits += decimal_nmb.get_width();
	this->length_of_velocity_digits += gl_data::img_comma.width;
}

void gl_velocity_gauge::set_precision_value(uint8_t precision_value) {
	this->precision = precision_value;
}
