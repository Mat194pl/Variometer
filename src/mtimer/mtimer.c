/*
 * mtimer..c
 *
 *  Created on: 22 kwi 2018
 *      Author: Mateusz
 */

#include "mtimer.h"
#include "app_timer.h"

#define APP_TIMER_PRESCALER 0

static uint32_t milliseconds_accumulator = 0;

APP_TIMER_DEF(millisecond_timer_id);

void millisecond_timer_callback(void* pcontext);

void mtimer_init(void) {
	uint32_t err_code;
	err_code = app_timer_create(&millisecond_timer_id, APP_TIMER_MODE_REPEATED, millisecond_timer_callback);
	APP_ERROR_CHECK(err_code);
	err_code = app_timer_start(millisecond_timer_id, APP_TIMER_TICKS(1, APP_TIMER_PRESCALER), NULL);

	milliseconds_accumulator = 0;
}

uint32_t mtimer_get_current_timestamp(void) {
	return milliseconds_accumulator;
}

void millisecond_timer_callback(void* pcontext) {
	milliseconds_accumulator++;
}
