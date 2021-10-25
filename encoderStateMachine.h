#include "encoder.h"

/*
 * encoderStateMachine.h
 *
 *  Created on: Oct 23, 2021
 *      Author: alex
 */

#ifndef ENCODERSTATEMACHINE_H_
#define ENCODERSTATEMACHINE_H_

enum encoderStates {detent, CCWTick, CWTick, waitForDetent} encoderState;

void encoderTick(encoderPinState encoderA, encoderPinState encoderB);
void encoderStateTransition(encoderPinState encoderA, encoderPinState encoderB);
void encoderStateActions();
void setLEDsForDebug(encoderPinState encoderA, encoderPinState encoderB);


#endif /* ENCODERSTATEMACHINE_H_ */
