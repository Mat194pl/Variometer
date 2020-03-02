/*
 * app_logic_global.cpp
 *
 *  Created on: 22 maj 2018
 *      Author: Mateusz
 */

#include "app_logic_global.h"

app_logic_global* app_logic_global::get_instance(void) {
	static app_logic_global instance;
	return &instance;
}


