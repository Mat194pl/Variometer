/*
 * mtimer.h
 *
 *  Created on: 22 kwi 2018
 *      Author: Mateusz
 */

#ifndef SRC_MTIMER_MTIMER_H_
#define SRC_MTIMER_MTIMER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize milliseconds timer
 */
void mtimer_init(void);

/**
 * @brief Get current milliseconds timestamp
 */
uint32_t mtimer_get_current_timestamp(void);

#ifdef __cplusplus
}
#endif

#endif /* SRC_MTIMER_MTIMER_H_ */
