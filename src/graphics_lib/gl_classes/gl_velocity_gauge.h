/*
 * gl_velocity_gauge.h
 *
 *  Created on: 12 maj 2018
 *      Author: Mateusz
 */

#ifndef SRC_GRAPHICS_LIB_GL_CLASSES_GL_VELOCITY_GAUGE_H_
#define SRC_GRAPHICS_LIB_GL_CLASSES_GL_VELOCITY_GAUGE_H_

#include <stdint.h>
#include "gl_object.h"
#include "../gl_types.h"
#include "gl_int_nmb_label.h"

class gl_velocity_gauge : public gl_object {
public:
	void init(void);
	void update(void);
	void draw(void);
	gl_velocity_gauge(void);
	void set_velocity_value(float velocity_value);
	void set_precision_value(uint8_t precision_value);

private:
	float velocity_value;
	gl_int_nmb_label integral_nmb;
	gl_int_nmb_label decimal_nmb;
	uint8_t precision;
	uint8_t length_of_velocity_digits;
};

#endif /* SRC_GRAPHICS_LIB_GL_CLASSES_GL_VELOCITY_GAUGE_H_ */
