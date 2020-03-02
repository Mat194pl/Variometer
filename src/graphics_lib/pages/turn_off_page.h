/*
 * turn_off_page.h
 *
 *  Created on: 21 maj 2018
 *      Author: Mateusz
 */

#ifndef SRC_GRAPHICS_LIB_PAGES_TURN_OFF_PAGE_H_
#define SRC_GRAPHICS_LIB_PAGES_TURN_OFF_PAGE_H_

#include "../gl_classes/gl_page.h"
#include "../gl_classes/gl_image.h"

class gl_turn_off_page : public gl_page {
public:
	void init(void);
	void draw(void);
	void update(void);
	gl_turn_off_page(void);
	void process_input(void);

private:
	gl_image turn_off_page_image;
};


#endif /* SRC_GRAPHICS_LIB_PAGES_TURN_OFF_PAGE_H_ */
