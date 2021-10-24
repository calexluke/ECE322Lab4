/*
 * encoderStateMachine.h
 *
 *  Created on: Oct 23, 2021
 *      Author: alex
 */

#ifndef ENCODERSTATEMACHINE_H_
#define ENCODERSTATEMACHINE_H_

enum encoderStates {detent, CCWTick, CWTick, waitForDetent} encoderState;

void encoderTick();
void encoderStateTransition();
void encoderStateActions();
void setLEDsForDebug();


#endif /* ENCODERSTATEMACHINE_H_ */
