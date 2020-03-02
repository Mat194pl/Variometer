/*
 * gl_object.h
 *
 *  Created on: 8 maj 2018
 *      Author: Mateusz
 */

#ifndef SRC_GRAPHICS_LIB_GL_CLASSES_GL_OBJECT_H_
#define SRC_GRAPHICS_LIB_GL_CLASSES_GL_OBJECT_H_

#include <stdint.h>

class gl_object {
public:
	virtual void init(void);
	virtual void update(void);
	virtual void draw(void);
	virtual uint32_t get_width(void);
	virtual uint32_t get_height(void);
	virtual void set_position(uint32_t pos_x, uint32_t pos_y);

	enum class object_type {
			PAGE,
			IMAGE
	};

	object_type object_type;

	enum class horizontal_aligment {
		LEFT,
		CENTER,
		RIGHT
	};

	horizontal_aligment horizontal_aligment;

	enum class vertical_aligment {
		TOP,
		CENTER,
		BOTTOM
	};

	vertical_aligment vertical_aligment;

protected:
	uint32_t pos_x;
	uint32_t pos_y;
	uint32_t width;
	uint32_t height;
};

#endif /* SRC_GRAPHICS_LIB_GL_CLASSES_GL_OBJECT_H_ */
