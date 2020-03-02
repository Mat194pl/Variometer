/*
 * gl_image.cpp
 *
 *  Created on: 8 maj 2018
 *      Author: Mateusz
 */

#include "gl_image.h"
#include "../port/gl_port.h"

void gl_image::init(void) {

}

void gl_image::update(void) {

}

void gl_image::draw(void) {
	if (image) {
		int16_t draw_pos_x = this->pos_x;
		int16_t draw_pos_y = this->pos_y;

		switch (horizontal_aligment) {
		case gl_object::horizontal_aligment::LEFT:

			break;

		case gl_object::horizontal_aligment::CENTER:
			draw_pos_x -= image->width / 2;
			break;

		case gl_object::horizontal_aligment::RIGHT:
			draw_pos_x -= image->width;
			break;
		}

		switch (vertical_aligment) {
		case gl_object::vertical_aligment::TOP:

			break;

		case gl_object::vertical_aligment::CENTER:
			draw_pos_y -= image->height / 2;
			break;

		case gl_object::vertical_aligment::BOTTOM:
			draw_pos_y -= image->height;
			break;
		}

		gl_port_draw_image(
				draw_pos_x,
				draw_pos_y,
				image->width,
				image->height,
				image->data);
	}
}

gl_image::gl_image(const gl_type::image_t* image) {
	this->image = image;
	this->pos_x = 0;
	this->pos_y = 0;
	horizontal_aligment = gl_object::horizontal_aligment::LEFT;
	object_type = gl_object::object_type::IMAGE;
}

gl_image::gl_image(void) {
	this->image = 0;
	this->pos_x = 0;
	this->pos_y = 0;
	horizontal_aligment = gl_object::horizontal_aligment::LEFT;
	object_type = gl_object::object_type::IMAGE;
}

void gl_image::set_image(const gl_type::image_t* image) {
	this->image = image;
	this->width = image->width;
	this->height = image->height;
}

