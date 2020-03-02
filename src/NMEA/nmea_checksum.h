/*
 * nmea_checksum.h
 *
 *  Created on: 24 lut 2018
 *      Author: Mateusz
 */

#ifndef NMEA_NMEA_CHECKSUM_H_
#define NMEA_NMEA_CHECKSUM_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Verify NMEA string checksum
 * @param p String which will be checked
 * @return bool Returns true if verification was successful
 */
bool nmea_verify_checksum(const char*p);

/**
 * @brief Append checksum to NMEA string
 * Function adds checksum to delivered string, checksum has a form: "*XX", where X is hexadecimal number
 * @param[in] p String to which the checksum will be added
 */
void nmea_append_checksum(char* p, uint8_t write_idx);

/**
 * @brief Compute and return checksum of string
 * @param[in] p String
 * @param[in] p String length
 * @return uint8_t Compted checksum
 */
uint8_t nmea_compute_checksum(const char *p, unsigned length);

#ifdef __cplusplus
}
#endif

#endif /* NMEA_NMEA_CHECKSUM_H_ */
