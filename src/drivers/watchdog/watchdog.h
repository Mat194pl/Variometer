/*
 * watchdog.h
 *
 *  Created on: 23 maj 2018
 *      Author: Mateusz
 */

#ifndef SRC_DRIVERS_WATCHDOG_WATCHDOG_H_
#define SRC_DRIVERS_WATCHDOG_WATCHDOG_H_

#ifdef __cplusplus
extern "C" {
#endif

void watchdog_init(void);
void watchdog_clear(void);

#ifdef __cplusplus
}
#endif

#endif /* SRC_DRIVERS_WATCHDOG_WATCHDOG_H_ */
