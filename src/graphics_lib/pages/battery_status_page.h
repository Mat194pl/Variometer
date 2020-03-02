/*
 * battery_status_page.h
 *
 *  Created on: 20 maj 2018
 *      Author: Mateusz
 */

#ifndef SRC_GRAPHICS_LIB_PAGES_BATTERY_STATUS_PAGE_H_
#define SRC_GRAPHICS_LIB_PAGES_BATTERY_STATUS_PAGE_H_

#include "../gl_classes/gl_page.h"
#include "../gl_classes/gl_image.h"
#include "../gl_classes/gl_battery_gauge.h"
#include "../gl_classes/gl_int_nmb_label.h"

class gl_battery_status_page : public gl_page {
public:
	void init(void);
	void draw(void);
	void update(void);
	gl_battery_status_page(void);
private:
	uint8_t battery_percentage_value;
	gl_battery_gauge battery_gauge;
	gl_int_nmb_label battery_value_label;
	gl_image percentage_image;
};


#endif /* SRC_GRAPHICS_LIB_PAGES_BATTERY_STATUS_PAGE_H_ */
