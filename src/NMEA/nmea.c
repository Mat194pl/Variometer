/*
 * nmea.c
 *
 *  Created on: 25 maj 2018
 *      Author: Mateusz
 */

#include "nmea.h"
#include <string.h>
#include "ble/ble_p.h"

uint8_t string_to_send_data[20];

typedef enum {
	OPEN_VARIO_TYPE_VELOCITY
} open_vario_type_t;

static uint8_t add_pov_header_to_string(uint8_t* string_data);
static uint8_t add_data_to_string(uint8_t* string_data, uint8_t write_index, open_vario_type_t type, float value);
static uint8_t convert_number_to_char_array(uint8_t* char_array, uint32_t number);

void nmea_send_velocity(float velocity) {
	memset(string_to_send_data, 0, 20);
	uint8_t widx = 0;
	widx = add_pov_header_to_string(string_to_send_data);
	widx = add_data_to_string(string_to_send_data, widx, OPEN_VARIO_TYPE_VELOCITY, velocity);
	nmea_append_checksum(string_to_send_data, widx);
	widx += 3;
	string_to_send_data[widx++] = '\n';

	ble_send_string(string_to_send_data, widx);

}

static uint8_t add_pov_header_to_string(uint8_t* string_data) {
	string_data[0] = '$';
	string_data[1] = 'P';
	string_data[2] = 'O';
	string_data[3] = 'V';
	string_data[4] = ',';

	return 5;
}


static uint8_t add_data_to_string(uint8_t* string_data, uint8_t write_index, open_vario_type_t type, float value) {
	uint8_t widx = write_index;

	switch (type) {
	case OPEN_VARIO_TYPE_VELOCITY:
		string_data[widx++] = 'E';
		break;
	}

	string_data[widx++] = ',';

	float conv_value = value;
	if (conv_value < 0) {
		conv_value *= -1;
	}

	uint32_t number_value = (uint32_t)(conv_value * 100);

	uint8_t number_integral_part_array[8];


	if (value < 0) {
		string_data[widx++] = '-';
	}

	uint8_t conv_nmb_length = convert_number_to_char_array(number_integral_part_array, (uint32_t)number_value / 100);
	memcpy(&(string_data[widx]), number_integral_part_array, conv_nmb_length);
	widx += conv_nmb_length;

	string_data[widx++] = '.';

	conv_nmb_length = convert_number_to_char_array(number_integral_part_array, (uint32_t)number_value - ((number_value / 100) * 100));

	if (conv_nmb_length != 2) {
		string_data[widx++] = '0';
	}

	memcpy(&(string_data[widx]), number_integral_part_array, conv_nmb_length);
	widx += conv_nmb_length;

	return widx;
}

static uint8_t convert_number_to_char_array(uint8_t* char_array, uint32_t number) {
	int idx = 0;

	if (0 == number) {
		char_array[idx] = 48;
		idx++;
		return idx;
	}

	while (number > 0) {
		char_array[idx] = number % 10 + 48;
		idx++;
		number /= 10;
	}

	uint8_t temp = 0;
	uint8_t end = idx - 1;

	for (uint8_t c = 0; c < idx / 2; c++) {
		temp = char_array[c];
		char_array[c]   = char_array[end];
		char_array[end] = temp;

	    end--;
	}

	return idx;
}

