/*
 * page.h
 *
 *  Created on: 8 maj 2018
 *      Author: Mateusz
 */

#ifndef SRC_GRAPHICS_LIB_GL_CLASSES_GL_PAGE_H_
#define SRC_GRAPHICS_LIB_GL_CLASSES_GL_PAGE_H_

#include "gl_object.h"
#include <stdint.h>

class gl_page : public gl_object {
public:
	virtual void init(void);
	virtual void update(void);
	virtual void draw(void);
	void set_objects_table(gl_object** objects_table, uint32_t objects_table_size);
	virtual void process_input(void);

private:
	gl_object** objects_table;
	uint32_t objects_table_size;
};

#endif /* SRC_GRAPHICS_LIB_GL_CLASSES_GL_PAGE_H_ */
