/*
 * pwm_lib.h
 *
 *  Created on: 16 kwi 2018
 *      Author: Mateusz
 */

#ifndef SRC_DRIVERS_BUZZER_PWM_PWM_LIB_H_
#define SRC_DRIVERS_BUZZER_PWM_PWM_LIB_H_

#ifdef __cplusplus
extern "C" {
#endif

void pwm_init(void);
void pwm_set_frequency(uint32_t frequency);

#ifdef __cplusplus
}
#endif

#endif /* SRC_DRIVERS_BUZZER_PWM_PWM_LIB_H_ */
