/*
 * gl_int_nmb_label.cpp
 *
 *  Created on: 11 maj 2018
 *      Author: Mateusz
 */

#include "gl_int_nmb_label.h"
#include "../images_data/letters.h"
#include "../port/gl_port.h"
#include <math.h>

void gl_int_nmb_label::init(void) {

}

void gl_int_nmb_label::update(void) {

}

void gl_int_nmb_label::draw(void) {
	uint8_t whole_width = this->width;

	int16_t draw_pos_x = this->pos_x;
	int16_t draw_pos_y = this->pos_y;

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
		draw_pos_y -= 15 / 2;
		break;

	case gl_object::vertical_aligment::BOTTOM:
		draw_pos_y -= 15;
		break;
	}

	uint8_t draw_x_offset = 0;

	if (this->is_number_negative) {
		gl_port_draw_image(
				draw_pos_x + draw_x_offset,
				draw_pos_y,
				gl_data::img_minus.width,
				gl_data::img_minus.height,
				gl_data::img_minus.data);

		draw_x_offset += gl_data::img_minus.width;
	}

	uint32_t nmb_to_draw = abs(this->number_value);

	for (uint8_t i = nmb_of_digits_to_draw; i > 0; i--) {
		const gl_type::image_t* img_to_draw = this->get_img_from_nmb(this->get_digit(i - 1, nmb_to_draw));

		if (img_to_draw) {
			gl_port_draw_image(
					draw_pos_x + draw_x_offset,
					draw_pos_y,
					img_to_draw->width,
					img_to_draw->height,
					img_to_draw->data);

			draw_x_offset += img_to_draw->width;
		}
	}
}

void gl_int_nmb_label::set_number_value(int value) {
	this->number_value = value;

	this->nmb_of_digits_to_draw = this->get_nmb_of_digits();

	if (this->nmb_of_digits_to_draw > 7) {
		this->nmb_of_digits_to_draw = 7;
	}

	if (this->number_value < 0) {
		this->is_number_negative = true;
	} else {
		this->is_number_negative = false;
	}

	uint8_t whole_width = nmb_of_digits_to_draw * 12;
	if (this->is_number_negative) {
		whole_width += 12;
	}
	this->width = whole_width;
}

int gl_int_nmb_label::get_number_value(void) {
	return this->number_value;
}

void gl_int_nmb_label::set_is_number_negative(bool is_number_negative) {
	if (is_number_negative && !this->is_number_negative) {
		this->width += 12;
	}

	this->is_number_negative = is_number_negative;
}


gl_int_nmb_label::gl_int_nmb_label(void) {
	this->number_value = 0;
	this->horizontal_aligment = gl_object::horizontal_aligment::LEFT;
	this->vertical_aligment = gl_object::vertical_aligment::TOP;
}

uint8_t gl_int_nmb_label::get_nmb_of_digits(void) {
	uint32_t abs_value = abs(this->number_value);
	uint8_t count = 0;

	if (0 == abs_value) {
		count = 1;
		return count;
	}

	while (abs_value > 0) {
		abs_value /= 10;
		count++;
	}

	return count;
}

const gl_type::image_t* gl_int_nmb_label::get_img_from_nmb(uint8_t nmb) {
	switch(nmb) {
	case 0:
		return &gl_data::img_zero;
		break;

	case 1:
		return &gl_data::img_one;
		break;

	case 2:
		return &gl_data::img_two;
		break;

	case 3:
		return &gl_data::img_three;
		break;

	case 4:
		return &gl_data::img_four;
		break;

	case 5:
		return &gl_data::img_five;
		break;

	case 6:
		return &gl_data::img_six;
		break;

	case 7:
		return &gl_data::img_seven;
		break;

	case 8:
		return &gl_data::img_eight;
		break;

	case 9:
		return &gl_data::img_nine;
		break;

	default:
		return 0;
	}
}

uint32_t gl_int_nmb_label::get_digit(uint8_t digit_index, uint32_t number) {
	switch(digit_index) {
	case 6:
		return (number / 1000000) % 10;
		break;

	case 5:
		return (number / 100000) % 10;
		break;

	case 4:
		return (number / 10000) % 10;
		break;

	case 3:
		return (number / 1000) % 10;
		break;

	case 2:
		return (number / 100) % 10;
		break;

	case 1:
		return (number / 10) % 10;
		break;

	case 0:
		return number % 10;
		break;
	}

	return 0;
}
