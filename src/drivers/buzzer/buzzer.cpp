/*
 * buzzer.cpp
 *
 *  Created on: 16 kwi 2018
 *      Author: Mateusz
 */

#include "buzzer.h"
#include "custom_board.h"
#include "nordic_common.h"
#include "app_util_platform.h"
#include "pwm/pwm_lib.h"
#include "mtimer/mtimer.h"

buzzer* buzzer::get_instance(void) {
	static buzzer instance(-2.0, 2.0, 0.5);
	return &instance;
}

buzzer::buzzer(
		double sinking_threshold,
		double climbing_threshold,
		double near_climbing_sensivity) {

	pwm_init();

	beep_start_time = 0;
	beep_type = BEEP_TYPE_SILENT;
	beep_state = {0};

	beep_sinking_threshold = sinking_threshold;
	beep_gliding_threshold = climbing_threshold - near_climbing_sensivity;
	beep_climbing_threshold = climbing_threshold;
}

void buzzer::set_frequency(uint32_t frequency) {
	pwm_set_frequency(frequency);
}

void buzzer::set_velocity(double velocity) {
	beep_type_need_change = false;
	switch(beep_type) {
	case BEEP_TYPE_SINKING :
		if( velocity >  beep_sinking_threshold + BEEPER_VELOCITY_SENSITIVITY )
			beep_type_need_change = true;
		break;

	case BEEP_TYPE_SILENT :
		if( velocity < beep_sinking_threshold || velocity > beep_gliding_threshold )
			beep_type_need_change = true;
		break;

	case BEEP_TYPE_GLIDING :
		if( velocity < beep_gliding_threshold - BEEPER_VELOCITY_SENSITIVITY || velocity > beep_climbing_threshold )
			beep_type_need_change = true;
		break;

	case BEEP_TYPE_CLIMBING :
		if( velocity < beep_climbing_threshold - BEEPER_VELOCITY_SENSITIVITY )
			beep_type_need_change = true;
		break;
	}

	bool alarm_start = false;

	// Check if climbing or sinking alarm is needed to start
	if (beep_state.gliding_alarm_enabled && beep_type_need_change && !beep_state.climbing_alarm && !beep_state.sinking_alarm) {
	    if (BEEP_TYPE_SINKING == beep_type || BEEP_TYPE_SILENT == beep_type) {
	    	if (velocity > beep_gliding_threshold && velocity < beep_climbing_threshold ) {
	    		alarm_start = true;
	    		beep_state.climbing_alarm = true;
	    	}
	    } else {
	    	if( velocity > beep_sinking_threshold && velocity < beep_gliding_threshold ) {
	    		alarm_start = true;
	    		beep_state.sinking_alarm = true;
	    	}
	    }
	}

	// Check if climbing or sinking alarm is needed to stop
	if ((beep_type_need_change) &&
		(beep_state.climbing_alarm || beep_state.sinking_alarm) &&
		(velocity > beep_climbing_threshold || velocity < beep_sinking_threshold)) {
		beep_state.climbing_alarm = false;
		beep_state.sinking_alarm = false;
	}

	if ((beep_type_need_change &&
		!beep_state.climbing_alarm &&
		!beep_state.sinking_alarm) || alarm_start) {
		beep_start_time = mtimer_get_current_timestamp();
		beep_pattern_base_position = 0.0;
		beep_pattern_position = 0.0;
		beep_state.beep_new_freq = true;
	}

	if (beep_type_need_change) {
		if (velocity < beep_sinking_threshold) {
			beep_type = BEEP_TYPE_SINKING;
		} else if (velocity < beep_gliding_threshold) {
			beep_type = BEEP_TYPE_SILENT;
		} else if (velocity < beep_climbing_threshold) {
			beep_type = BEEP_TYPE_GLIDING;
		} else {
			beep_type = BEEP_TYPE_CLIMBING;
		}
	}

	if (alarm_start || beep_type_need_change ||
		velocity > beep_velocity + BEEPER_VELOCITY_SENSITIVITY ||
		velocity < beep_velocity - BEEPER_VELOCITY_SENSITIVITY) {
		set_beep_parameters(velocity);
	}
}

void buzzer::update(void) {
	set_beep_pattern_position(beep_velocity);
	set_tone();
}

void buzzer::set_beep_parameters(double velocity) {
	beep_velocity = velocity;

	switch(beep_type) {
	case BEEP_TYPE_SINKING:
		beep_freq = SINKING_BEEP_BASE_FREQ;
		break;

	case BEEP_TYPE_SILENT:
		beep_freq = 0.0;
		break;

	case BEEP_TYPE_GLIDING:
	case BEEP_TYPE_CLIMBING:
		beep_freq = CLIMBING_BEEP_FREQ_COEFF * velocity + CLIMBING_BEEP_BASE_FREQ;
		break;

	}
}

void buzzer::set_beep_pattern_position(double velocity) {
	bool is_alarm = false;
	if (beep_state.climbing_alarm || beep_state.sinking_alarm) {
		is_alarm = true;
	}

	if (!is_alarm && (BEEP_TYPE_SINKING == beep_type || BEEP_TYPE_SILENT == beep_type)) {
		return;
	}

	uint32_t current_time = 0;
	current_time = mtimer_get_current_timestamp();
	double current_length = (double)(current_time - beep_start_time) / 1000.0;

	if (!is_alarm || BEEP_TYPE_CLIMBING == beep_type) {
		current_length *= (beep_velocity * CLIMBING_BEEP_VELOCITY_FILTER_COEFF + CLIMBING_BEEP_VELOCITY_FILTER_BASE);

		/* avoid going backward */
		if( current_length + beep_pattern_base_position > beep_pattern_position ) {
			beep_pattern_position = current_length + beep_pattern_base_position;
		}
	} else {
		beep_pattern_position = current_length;
	}

	/* check if the pattern end is reached */
	// alarm case
	if (is_alarm) {
		// climbing alarm
		if (beep_state.climbing_alarm) {
			// if alarm done, reset
			if (beep_pattern_position > CLIMBING_ALARM_LENGTH) {
				beep_state.climbing_alarm = false;
				beep_start_time = current_time;
				beep_pattern_base_position = 0.0;
				beep_pattern_position = 0.0;
				set_beep_pattern_position(velocity);
				beep_state.beep_new_freq = true;
				return;
			}
		} else {
			// Sinking alarm
			// if alarm done, reset
			if (beep_pattern_position > SINKING_ALARM_LENGTH) {
				beep_state.sinking_alarm = false;
				beep_start_time = current_time;
				beep_pattern_base_position = 0.0;
				beep_pattern_position = 0.0;
				set_beep_pattern_position(velocity);
				beep_state.beep_new_freq = true;
			}
		}
	} else {
		// looping pattern case
		double looping_pattern_length;
		if (BEEP_TYPE_GLIDING) {
			looping_pattern_length = GLIDING_BEEP_LENGTH;
		} else {
			looping_pattern_length = CLIMBING_BEEP_LENGTH;
		}

		while (beep_pattern_position > looping_pattern_length) {
			beep_pattern_position -= looping_pattern_length;
			beep_start_time = mtimer_get_current_timestamp();
			beep_pattern_base_position = beep_pattern_position;
		}
	}
}

void buzzer::set_tone(void) {
	// alarm case
	if (beep_state.climbing_alarm || beep_state.sinking_alarm) {
		// Climbing alarm
		if (beep_state.climbing_alarm) {
			// Get half position
			double half_pattern_position = beep_pattern_position;
			if (half_pattern_position > (CLIMBING_ALARM_LENGTH / 2.0)) {
				half_pattern_position -= (CLIMBING_ALARM_LENGTH / 2.0);
			}

			// Set tone
			if (half_pattern_position < CLIMBING_ALARM_HIGH_LENGTH) {
				if (!beep_state.beep_high) {
					// TODO toneAC(CLIMBING_ALARM_FREQ, volume);
					pwm_set_frequency(CLIMBING_ALARM_FREQ);
					beep_state.beep_high = true;
				} else {
					// TODO toneAC(CLIMBING_ALARM_FREQ, volume);
					pwm_set_frequency(CLIMBING_ALARM_FREQ);
				}
			} else {
				// TODO toneAC(0.0);
				pwm_set_frequency(0);
				beep_state.beep_high = false;
			}
		} else {
			// Sinking alarm
			if (!beep_state.beep_high || beep_state.beep_new_freq) {
				// TODO toneAC(SINKING_ALARM_FREQ, volume);
				pwm_set_frequency(SINKING_ALARM_FREQ);
				beep_state.beep_high = true;
			}
		}
	} else {
		// Sinking beep
		if (BEEP_TYPE_SINKING == beep_type) {
			if (!beep_state.beep_high || beep_state.beep_new_freq) {
				// TODO toneAC(beepFreq, volume);
				pwm_set_frequency((uint32_t)beep_freq);
				beep_state.beep_high = true;
			}
		} else if (BEEP_TYPE_SILENT == beep_type) {
			// TODO toneAC(0.0);
			pwm_set_frequency(0);
			beep_state.beep_high = false;
		} else if (BEEP_TYPE_GLIDING == beep_type) {
			if (beep_state.gliding_beep_enabled) {
				if (beep_pattern_position < GLIDING_BEEP_HIGH_LENGTH) {
					if (!beep_state.beep_high) {
						// TODO toneAC(beepFreq, volume);
						pwm_set_frequency((uint32_t)beep_freq);
						beep_state.beep_high = true;
					} else if (beep_state.beep_new_freq) {
						// TODO toneAC(beef_freq, volume);
						pwm_set_frequency((uint32_t)beep_freq);
					}
				} else {
					// TODO toneAC(0.0);
					pwm_set_frequency(0);
					beep_state.beep_high = false;
				}
			} else {
				// TODO toneAC(0.0);
				pwm_set_frequency(0);
				beep_state.beep_high = false;
			}
		} else { // Climbing
			if (beep_pattern_position < CLIMBING_BEEP_HIGH_LENGTH) {
				if (!beep_state.beep_high) {
					// TODO toneAC(beep_freq, volume);
					pwm_set_frequency((uint32_t)beep_freq);
					beep_state.beep_high = true;
				} else if (beep_state.beep_new_freq) {
					// TODO toneAC(beep_freq, volume);
					pwm_set_frequency((uint32_t)beep_freq);
				}
			} else {
				// TODO toneAC(0.0);
				pwm_set_frequency(0);
				beep_state.beep_high = false;
			}
		}
	}

	// Tone is set
	beep_state.beep_new_freq = false;
}
