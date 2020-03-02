/**
 * @file ble.h
 *
 *  Created on: 24 lut 2018
 *      Author: Mateusz
 */

#ifndef BLE_BLE_H_
#define BLE_BLE_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup BLE Bluetooth Low Energy Module
 * @{
 */

/**
 * @addtogroup BLE_Public_Functions Public Functions
 * @{
 */

/**
 * @brief Initialize BLE modules
 */
void ble_init(void);

void ble_send_string(uint8_t * p_string, uint16_t length);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* BLE_BLE_H_ */
