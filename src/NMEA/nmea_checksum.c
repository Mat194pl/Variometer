/*
 * nmea_checksum.c
 *
 *  Created on: 24 lut 2018
 *      Author: Mateusz
 */

#include "nmea_checksum.h"

#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

static void _convert_uint8_t_to_hex_string(uint8_t number, uint8_t* string);

bool nmea_verify_checksum(const char*p) {
	assert(p);

	const char* asterisk = strchr(p, '*');

	if (0 == asterisk)
	    return false;

	const char *checksum_string = asterisk + 1;
	char *endptr;

	unsigned long read_checksum_2 = strtoul(checksum_string, &endptr, 16);

	if (endptr == checksum_string || *endptr != 0 || read_checksum_2 >= 0x100)
		return false;

	uint8_t read_checksum = (unsigned char)read_checksum_2;
	uint8_t calc_checksum = nmea_compute_checksum(p, asterisk - p);

	return calc_checksum == read_checksum;
}

void nmea_append_checksum(char* p, uint8_t write_idx) {
	assert(p);

	uint8_t nmea_checksum = nmea_compute_checksum(p, write_idx);

	p[write_idx++] = '*';

	_convert_uint8_t_to_hex_string(nmea_checksum, &p[write_idx]);

	//sprintf(p + strlen(p), "*%02X", nmea_compute_checksum(p, strlen(p)));
}

uint8_t nmea_compute_checksum(const char *p, unsigned length) {
	assert(p);
	assert(length > 0);

	uint8_t checksum = 0;

	unsigned i = 0;

	/* skip the dollar sign at the beginning (the exclamation mark is
	     used by CAI302 */
	if (length > 0 && (*p == '$' || *p == '!')) {
		++i;
		++p;
	}

	for (; i < length; ++i)
		checksum ^= *p++;

	return checksum;
}

static void _convert_uint8_t_to_hex_string(uint8_t number, uint8_t* string) {
	uint8_t digit = number % 16;
	if (digit < 10) {
		string[1] = digit + 48;
	} else {
		string[1] = digit + 55;
	}

	number /= 16;

	digit = number % 16;
	if (digit < 10) {
		string[0] = digit + 48;
	} else {
		string[0] = digit + 55;
	}
}
