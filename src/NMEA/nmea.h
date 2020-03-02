/*
 * nmea.h
 *
 *  Created on: 25 maj 2018
 *      Author: Mateusz
 */

#ifndef SRC_NMEA_NMEA_H_
#define SRC_NMEA_NMEA_H_

#include "nmea_checksum.h"

#ifdef __cplusplus
extern "C" {
#endif

void nmea_send_velocity(float velocity);

#ifdef __cplusplus
}
#endif

#endif /* SRC_NMEA_NMEA_H_ */
