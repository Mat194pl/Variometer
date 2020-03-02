/*
 * gl.h
 *
 *  Created on: 4 kwi 2018
 *      Author: Mateusz
 */

#ifndef SRC_GRAPHICS_LIB_GL_H_
#define SRC_GRAPHICS_LIB_GL_H_

#include "gl_classes/gl_page.h"

class gl {
public:
	static gl* get_instance(void);
	void process(void);
	void turn_display_on(void);
	void turn_display_off(void);
	void show_next_page(void);
	void change_value_in_page(void);

private:
	void operator=(gl const&);
	gl(void);
	gl(gl const&);

	gl_page* current_page;
	bool is_display_on;
};

#endif /* SRC_GRAPHICS_LIB_GL_H_ */
