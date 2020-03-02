/*
 * gl_struct.h
 *
 *  Created on: 8 maj 2018
 *      Author: Mateusz
 */

#ifndef SRC_GRAPHICS_LIB_GL_TYPES_H_
#define SRC_GRAPHICS_LIB_GL_TYPES_H_

#include <stdint.h>

namespace gl_type {
	typedef struct {
		uint8_t width;
		uint8_t height;
		uint8_t data[];
	} image_t;
};

#endif /* SRC_GRAPHICS_LIB_GL_TYPES_H_ */
