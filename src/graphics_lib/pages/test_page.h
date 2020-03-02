/*
 * test_page.h
 *
 *  Created on: 11 maj 2018
 *      Author: Mateusz
 */

#ifndef SRC_GRAPHICS_LIB_PAGES_TEST_PAGE_H_
#define SRC_GRAPHICS_LIB_PAGES_TEST_PAGE_H_

#include "../gl_classes/gl_page.h"
#include "../gl_classes/gl_image.h"

class gl_test_page : public gl_page {
public:
	void init(void);
	void draw(void);
	void update(void);
	gl_test_page(void);
private:
	gl_image test_image;
	float velocity;
};

#endif /* SRC_GRAPHICS_LIB_PAGES_TEST_PAGE_H_ */
