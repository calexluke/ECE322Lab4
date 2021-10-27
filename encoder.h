#include "global.h"

/*
 * encoder.h
 *
 *  Created on: Oct 23, 2021
 *      Author: alex
 */

#ifndef ENCODER_H_
#define ENCODER_H_

typedef enum {LOW, HIGH} encoderPinState;

#define ENCODER_TIMER_PERIOD_HZ 1000  // 1ms or 1000Hz
#define ENCODER_TIMER_PERIOD (SMCLOCK_HZ / ENCODER_TIMER_PERIOD_HZ)

encoderPinState readEncoderA();
encoderPinState readEncoderB();
void configureIOForEncoder();
void configureTimerForEncoder();

#endif /* ENCODER_H_ */
