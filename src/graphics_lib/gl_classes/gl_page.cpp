/*
 * page.cpp
 *
 *  Created on: 8 maj 2018
 *      Author: Mateusz
 */

#include "gl_page.h"
#include "nrf_log.h"

void gl_page::init(void) {
	object_type = gl_object::object_type::PAGE;
}

void gl_page::draw(void) {
	for (uint32_t i = 0; i < objects_table_size; i++) {
		objects_table[i]->draw();
	}
}

void gl_page::update(void) {
	for (uint32_t i = 0; i < objects_table_size; i++) {
		objects_table[i]->update();
	}
}

void gl_page::set_objects_table(gl_object** objects_table, uint32_t objects_table_size) {
	this->objects_table = objects_table;
	this->objects_table_size = objects_table_size;

	for (uint32_t i = 0; i < objects_table_size; i++) {
		objects_table[i]->init();
	}
}

void gl_page::process_input(void) {
}
