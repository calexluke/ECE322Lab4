/*
 * servoControl.h
 *
 *  Created on: Oct 23, 2021
 *      Author: alex
 */

#ifndef SERVOCONTROL_H_
#define SERVOCONTROL_H_

/*
 * define these integers as long int:    1234L
 *                            \--------------^
 * or they will not be computed correctly!
 */

#define SMCLOCK_HZ 1000000L  // Hz
#define SERVO_PERIOD_HZ 50  // 20ms or 50Hz

#define SERVO_MIN_PULSE_US 500L
#define SERVO_MID_PULSE_US 1500L
#define SERVO_MAX_PULSE_US 2500L

// convert to timer clock cycles
#define SERVO_PERIOD (SMCLOCK_HZ / SERVO_PERIOD_HZ)
#define SERVO_MIN_PULSE (SERVO_MIN_PULSE_US * (SMCLOCK_HZ / 1000000L))
#define SERVO_MID_PULSE (SERVO_MID_PULSE_US * (SMCLOCK_HZ / 1000000L))
#define SERVO_MAX_PULSE (SERVO_MAX_PULSE_US * (SMCLOCK_HZ / 1000000L))

#define WIDTH_RANGE (SERVO_MAX_PULSE_US - SERVO_MIN_PULSE_US)
// step size is 7.5 degrees. Full range is 180 degrees
#define STEP_SIZE (WIDTH_RANGE * (7.5 / 180));

typedef enum {CW_MAX, CCW_MAX, CENTER} SERVO_POSITION;

void configureTimersForServo();
void configureIOForServo();
void stepServoClockwise();
void stepServoCounterClockwise();
void setServo(SERVO_POSITION position);

#endif /* SERVOCONTROL_H_ */
