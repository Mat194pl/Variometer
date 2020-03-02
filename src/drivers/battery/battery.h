/*
 * battery.h
 *
 *  Created on: 3 maj 2018
 *      Author: Mateusz
 */

#ifndef SRC_DRIVERS_BATTERY_BATTERY_H_
#define SRC_DRIVERS_BATTERY_BATTERY_H_

#include <stdint.h>

class battery {
public:
	static battery* get_instance(void);
	void start_sampling(void);
	uint8_t get_percentage_value(void);

private:
	battery(void);
	battery(battery const&);
	void operator=(battery const&);
};

#endif /* SRC_DRIVERS_BATTERY_BATTERY_H_ */
