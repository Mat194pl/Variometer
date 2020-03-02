/*
 * buttons.h
 *
 *  Created on: 19 maj 2018
 *      Author: Mateusz
 */

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	BUTTON_LEFT,	/*< Button SW1 */
	BUTTON_RIGHT	/*< Button SW2 */
} button_t;

/**
 * @brief Initialize buttons GPIO
 */
void buttons_init(void);

/**
 * @brief Check if button is pressed
 * @param button Button to be checked
 * @return bool True if button is pressed
 */
bool buttons_is_pressed(button_t button);

#ifdef __cplusplus
}
#endif
