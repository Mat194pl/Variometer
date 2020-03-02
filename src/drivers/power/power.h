/*
 * power.h
 *
 *  Created on: 16 maj 2018
 *      Author: Mateusz
 */

#ifndef SRC_DRIVERS_POWER_POWER_H_
#define SRC_DRIVERS_POWER_POWER_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize power ON / OFF functions
 */
void power_init(void);

/**
 * @brief Turn power ON
 */
void power_turn_on(void);

/**
 * @brief Turn power OFF
 */
void power_turn_off(void);

#ifdef __cplusplus
}
#endif

#endif /* SRC_DRIVERS_POWER_POWER_H_ */
