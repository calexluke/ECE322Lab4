/*
 * longPressStateMachine.h
 *
 *  Created on: Oct 23, 2021
 *      Author: alex
 */

#ifndef LONGPRESSSTATEMACHINE_H_
#define LONGPRESSSTATEMACHINE_H_

enum longPressStates {buttonsOff, bothButtonsHeld, button1Held, button2Held, servoCenter, servoCCW, servoCW} longPressState;
void longPressTick(BUTTON_STATE button1, BUTTON_STATE button2);
void longPressStateTransition(BUTTON_STATE button1, BUTTON_STATE button2);
void longPressStateActions();

#endif /* LONGPRESSSTATEMACHINE_H_ */
