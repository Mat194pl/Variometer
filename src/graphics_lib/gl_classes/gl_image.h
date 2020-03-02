/*
 * gl_image.h
 *
 *  Created on: 8 maj 2018
 *      Author: Mateusz
 */

#ifndef SRC_GRAPHICS_LIB_GL_CLASSES_GL_IMAGE_H_
#define SRC_GRAPHICS_LIB_GL_CLASSES_GL_IMAGE_H_

#include "gl_object.h"
#include "../gl_types.h"

class gl_image : public gl_object {
public:
	void init(void);
	void update(void);
	void draw(void);

	gl_image(const gl_type::image_t* image);
	gl_image(void);

	void set_image(const gl_type::image_t* image);
private:
	const gl_type::image_t* image;
};

#endif /* SRC_GRAPHICS_LIB_GL_CLASSES_GL_IMAGE_H_ */
