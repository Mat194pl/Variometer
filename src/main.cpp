/*
 * main.cpp
 *
 *  Created on: 26 mar 2018
 *      Author: Mateusz
 */

#include "drivers/MS5611/ms5611.h"
#include "drivers/SSD1306BZ/ssd1306bz.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "app_error.h"
#include "drivers/buzzer/buzzer.h"
#include "nrf_delay.h"
#include "nrf_drv_gpiote.h"
#include "graphics_lib/gl.h"
#include "app_timer.h"
#include "ble/ble_p.h"
#include "nmea/nmea.h"
#include <math.h>
#include "app_logic/app_logic.h"
#include "drivers/watchdog/watchdog.h"
#include "drivers/buzzer/pwm/pwm_lib.h"

#define DEAD_BEEF 0xDEADBEEF /**< Value used as error code on stack dump, can be used to identify stack location on stack unwind. */
#define APP_TIMER_PRESCALER 0
#define APP_TIMER_OP_QUEUE_SIZE 10

APP_TIMER_DEF(buz_update_timer_id);

/**@brief Function for assert macro callback.
 *
 * @details This function will be called in case of an assert in the SoftDevice.
 *
 * @warning This handler is an example only and does not fit a final product. You need to analyse
 *          how your product is supposed to react in case of Assert.
 * @warning On assert from the SoftDevice, the system can only recover on reset.
 *
 * @param[in] line_num    Line number of the failing ASSERT call.
 * @param[in] p_file_name File name of the failing ASSERT call.
 */
void assert_nrf_callback(uint16_t line_num, const uint8_t * p_file_name)
{
    app_error_handler(DEAD_BEEF, line_num, p_file_name);
}

void app_error_fault_handler(uint32_t id, uint32_t pc, uint32_t info)
{
    NRF_LOG_ERROR("Fatal\r\n");
    NRF_LOG_FINAL_FLUSH();
    // On assert, the system can only recover with a reset.
    NVIC_SystemReset();
}


void HardFault_Handler(void) {
	while(1) {}
}


int main(void) {
	APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
	NRF_LOG_INFO("App start\r\n");
	nrf_delay_ms(500);
	// Init GPIOTE
	ret_code_t err_code = nrf_drv_gpiote_init();
	APP_ERROR_CHECK(err_code);
	nmea_send_velocity(-2.15);
	watchdog_init();

	APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_OP_QUEUE_SIZE, NULL);
	ble_init();

	app_logic& app = app_logic::get_instance();

	for (;;) {
		app.process();
		NRF_LOG_PROCESS();
    }
}

