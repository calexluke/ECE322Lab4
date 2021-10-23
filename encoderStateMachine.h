/*
 * encoderStateMachine.h
 *
 *  Created on: Oct 23, 2021
 *      Author: alex
 */

#ifndef ENCODERSTATEMACHINE_H_
#define ENCODERSTATEMACHINE_H_

enum encoderStates {detent, CCWTick, CWTick, waitForDetent} encoderState;

typedef enum {HIGH, LOW} encoderPinState;
typedef enum {true, false} bool;

encoderPinState readEncoderA();
encoderPinState readEncoderB();
bool encoderIsInDetent();
void encoderTick();
void encoderStateTransition();
void encoderStateActions();
void configureIOForEncoder();
void setLEDsForDebug();


#endif /* ENCODERSTATEMACHINE_H_ */
