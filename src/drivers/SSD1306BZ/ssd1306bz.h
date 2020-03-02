/*
 * ssd1306bz.h
 *
 *  Created on: 2 mar 2018
 *      Author: Mateusz
 */

#ifndef SRC_DRIVERS_SSD1306BZ_SSD1306BZ_H_
#define SRC_DRIVERS_SSD1306BZ_SSD1306BZ_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialiaze SSD1306BZ display
 */
void ssd1306bz_init(void);

/**
 * @brief Send frame buffer to display
 */
void ssd1306bz_update(void);

/**
 * @brief Draw an image on screen
 * @param[in] pos_x Horizontal position
 * @param[in] pox_y Vertical position
 * @param[in] width Image width
 * @param[in] height Image height
 * @param[in] data Pointer to image data array
 */
void ssd1306bz_draw_image(
		int16_t pos_x,
		int16_t pos_y,
		uint8_t width,
		uint8_t height,
		const uint8_t* data);

/**
 * @brief Clear display screen
 */
void ssd1306bz_clear_screen(void);

/**
 * @brief Turn off display
 */
void ssd1306bz_turn_off(void);

/**
 * @brief Turn on display
 */
void ssd1306bz_turn_on(void);

#ifdef __cplusplus
}
#endif

#endif /* SRC_DRIVERS_SSD1306BZ_SSD1306BZ_H_ */
