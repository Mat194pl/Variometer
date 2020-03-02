/*
 * gl_int_nmb_label.h
 *
 *  Created on: 11 maj 2018
 *      Author: Mateusz
 */

#ifndef SRC_GRAPHICS_LIB_GL_CLASSES_GL_INT_NMB_LABEL_H_
#define SRC_GRAPHICS_LIB_GL_CLASSES_GL_INT_NMB_LABEL_H_

#include "gl_object.h"
#include "../gl_types.h"

class gl_int_nmb_label : public gl_object {
public:
	void init(void);
	void update(void);
	void draw(void);

	gl_int_nmb_label(void);

	void set_number_value(int value);
	int get_number_value(void);
	void set_is_number_negative(bool is_number_negative);
private:
	uint8_t get_nmb_of_digits(void);
	const gl_type::image_t* get_img_from_nmb(uint8_t nmb);
	uint32_t get_digit(uint8_t digit_index, uint32_t number);

	int number_value;
	uint8_t nmb_of_digits_to_draw;
	bool is_number_negative;
};

#endif /* SRC_GRAPHICS_LIB_GL_CLASSES_GL_INT_NMB_LABEL_H_ */
