/*
 * ms5611.h
 *
 *  Created on: 16 lis 2017
 *      Author: Mateusz
 */

#ifndef MS5611_H_
#define MS5611_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** MS5611 measurement data structure */
typedef struct
{
	float temperature;
	uint32_t pressure;
} ms5611_data_t;

void ms5611_init(void);
ms5611_data_t ms5611_get_measures(void);

#ifdef __cplusplus
}
#endif

#endif /* MS5611_H_ */
