/*
 * gl_port.h
 *
 *  Created on: 11 maj 2018
 *      Author: Mateusz
 */

#ifndef SRC_GRAPHICS_LIB_PORT_GL_PORT_H_
#define SRC_GRAPHICS_LIB_PORT_GL_PORT_H_

#include <stdint.h>

/**
 * @brief Initialize graphics library low level port functions
 */
void gl_port_init(void);
void gl_port_draw_image(
		int16_t pos_x,
		int16_t pos_y,
		uint8_t width,
		uint8_t height,
		const uint8_t* data);
void gl_port_update();
void gl_port_clear_screen(void);
void gl_port_turn_on_display(void);
void gl_port_turn_off_display(void);

#endif /* SRC_GRAPHICS_LIB_PORT_GL_PORT_H_ */
