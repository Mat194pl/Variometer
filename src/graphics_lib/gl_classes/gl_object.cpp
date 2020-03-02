/*
 * gl_object.cpp
 *
 *  Created on: 8 maj 2018
 *      Author: Mateusz
 */

#include "gl_object.h"

void gl_object::init() {

}

void gl_object::draw() {

}

void gl_object::update() {

}

void gl_object::set_position(uint32_t pos_x, uint32_t pos_y) {
	this->pos_x = pos_x;
	this->pos_y = pos_y;
}

uint32_t gl_object::get_width(void) {
	return this->width;
}

uint32_t gl_object::get_height(void) {
	return this->height;
}
