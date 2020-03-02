/*
 * gl_battery_gauge.h
 *
 *  Created on: 20 maj 2018
 *      Author: Mateusz
 */

#ifndef SRC_GRAPHICS_LIB_GL_CLASSES_GL_BATTERY_GAUGE_H_
#define SRC_GRAPHICS_LIB_GL_CLASSES_GL_BATTERY_GAUGE_H_

#include <stdint.h>
#include "gl_object.h"
#include "../gl_types.h"

class gl_battery_gauge : public gl_object {
public:
	void init(void);
	void update(void);
	void draw(void);
	gl_battery_gauge(void);
	void set_battery_percentage_value(uint8_t percentage_value);

private:
	uint8_t percentage_value;
	uint8_t nmb_of_lines_to_draw;
};

#endif /* SRC_GRAPHICS_LIB_GL_CLASSES_GL_BATTERY_GAUGE_H_ */
