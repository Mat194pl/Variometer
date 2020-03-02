/*
 * buzzer.h
 *
 *  Created on: 16 kwi 2018
 *      Author: Mateusz
 */

#ifndef SRC_DRIVERS_BUZZER_BUZZER_H_
#define SRC_DRIVERS_BUZZER_BUZZER_H_

#include <stdint.h>
#include <stdbool.h>

/** Default thresholds values */
#define BEEPER_VELOCITY_DEFAULT_SINKING_THRESHOLD (-1.0)
#define BEEPER_VELOCITY_DEFAULT_CLIMBING_THRESHOLD 1.0
#define BEEPER_VELOCITY_DEFAULT_NEAR_CLIMBING_SENSITIVITY 0.1

#define BEEPER_VELOCITY_SENSITIVITY 0.1

/** THE SINKING BEEP */
#define SINKING_BEEP_BASE_FREQ 100.0

/** climbing beep sound freq computation : BEEP_FREQ_COEFF * velocity + BEEP_BASE_FREQ */
#define CLIMBING_BEEP_BASE_FREQ		386.0
#define CLIMBING_BEEP_FREQ_COEFF	141.0

/** climbing beep velocity filter */
/** filteredVelocity = beepVelocity * BEEP_VELOCITY_FILTER_COEFF + BEEP_VELOCITY_FILTER_BASE */
#define CLIMBING_BEEP_VELOCITY_FILTER_BASE 1.62
#define CLIMBING_BEEP_VELOCITY_FILTER_COEFF 0.51

/** THE CLIMBING ALARM */
#define CLIMBING_ALARM_HIGH_LENGTH 0.10
#define CLIMBING_ALARM_LOW_LENGTH 0.30
#define CLIMBING_ALARM_LENGTH (CLIMBING_ALARM_HIGH_LENGTH + CLIMBING_ALARM_LOW_LENGTH)
#define CLIMBING_ALARM_FREQ 1000.0

/** length of beep in vertical meters */
#define CLIMBING_BEEP_HIGH_LENGTH 0.5
#define CLIMBING_BEEP_LOW_LENGTH 0.5
#define CLIMBING_BEEP_LENGTH (CLIMBING_BEEP_HIGH_LENGTH + CLIMBING_BEEP_LOW_LENGTH)

/** THE SINKING ALARM */
#define SINKING_ALARM_LENGTH 0.7
#define SINKING_ALARM_FREQ 100.0

/** THE GLIDING BEEP */
#define GLIDING_BEEP_HIGH_LENGTH 0.10
#define GLIDING_BEEP_LOW_LENGTH 1.40
#define GLIDING_BEEP_LENGTH (GLIDING_BEEP_HIGH_LENGTH + GLIDING_BEEP_LOW_LENGTH)

class buzzer {
public:
	static buzzer* get_instance(void);
	void set_frequency(uint32_t frequency);
	void set_velocity(double velocity);
	void update(void);

private:
	buzzer(void);
	buzzer(	double sinking_threshold,
			double climbing_threshold,
			double near_climbing_sensivity);
	buzzer(buzzer const&);
	void operator=(buzzer const&);

	void set_beep_parameters(double velocity);
	void set_beep_pattern_position(double velocity);
	void set_tone(void);

	enum beep_type_e {
		BEEP_TYPE_SILENT = 0,
		BEEP_TYPE_SINKING,
		BEEP_TYPE_GLIDING,
		BEEP_TYPE_CLIMBING
	};

	enum beep_type_e beep_type;

	typedef struct {
		bool beep_high : 1;
		bool gliding_beep_enabled : 1;
		bool gliding_alarm_enabled : 1;
		bool climbing_alarm : 1;
		bool sinking_alarm : 1;
		bool beep_new_freq : 1;
	} beep_state_t;

	beep_state_t beep_state;
	bool beep_type_need_change;
	double beep_sinking_threshold;
	double beep_gliding_threshold;
	double beep_climbing_threshold;
	double beep_velocity;
	double beep_freq;
	double beep_pattern_base_position;
	double beep_pattern_position;
	uint32_t beep_start_time;
};

#endif /* SRC_DRIVERS_BUZZER_BUZZER_H_ */
