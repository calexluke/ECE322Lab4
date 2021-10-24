/*
 * encoder.h
 *
 *  Created on: Oct 23, 2021
 *      Author: alex
 */

#ifndef ENCODER_H_
#define ENCODER_H_

typedef enum {HIGH, LOW} encoderPinState;

encoderPinState readEncoderA();
encoderPinState readEncoderB();
void configureIOForEncoder();

#endif /* ENCODER_H_ */
