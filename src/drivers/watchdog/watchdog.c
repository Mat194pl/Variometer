/*
 * watchdog.c
 *
 *  Created on: 23 maj 2018
 *      Author: Mateusz
 */

#include "watchdog.h"
#include "nrf.h"

void watchdog_init(void) {
	NRF_WDT->CONFIG = (WDT_CONFIG_HALT_Pause << WDT_CONFIG_HALT_Run) | ( WDT_CONFIG_SLEEP_Run << WDT_CONFIG_SLEEP_Pos);   //Configure Watchdog. a) Pause watchdog while the CPU is halted by the debugger.  b) Keep the watchdog running while the CPU is sleeping.
	NRF_WDT->CRV = 32768;             //ca 1 sek. timout
	NRF_WDT->RREN |= WDT_RREN_RR0_Msk;  //Enable reload register 0
	NRF_WDT->TASKS_START = 1;           //Start the Watchdog timer
}

void watchdog_clear(void) {
	NRF_WDT->RR[0] = WDT_RR_RR_Reload;  //Reload watchdog register 0
}


