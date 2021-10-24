
#include "msp430BuiltInIO.h"
#include "encoder.h"

/*
 * global.h
 *
 *  Created on: Oct 23, 2021
 *      Author: alex
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

BUTTON_STATE button1;
BUTTON_STATE button2;
BUTTON_STATE button1Previous;
BUTTON_STATE button2Previous;

encoderPinState encoderA;
encoderPinState encoderB;

int timerFlag;

typedef enum {true, false} bool;

#endif /* GLOBAL_H_ */
