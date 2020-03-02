/*
 * gl_port.cpp
 *
 *  Created on: 11 maj 2018
 *      Author: Mateusz
 */

#include "gl_port.h"
#include "drivers/SSD1306BZ/ssd1306bz.h"

void gl_port_init(void) {
	ssd1306bz_init();
}

void gl_port_draw_image(
		int16_t pos_x,
		int16_t pos_y,
		uint8_t width,
		uint8_t height,
		const uint8_t* data) {
	ssd1306bz_draw_image(
			pos_x,
			pos_y,
			width,
			height,
			data);
}

void gl_port_update() {
	ssd1306bz_update();
}

void gl_port_clear_screen(void) {
	ssd1306bz_clear_screen();
}

void gl_port_turn_on_display(void) {
	ssd1306bz_turn_on();
}

void gl_port_turn_off_display(void) {
	ssd1306bz_turn_off();
}
