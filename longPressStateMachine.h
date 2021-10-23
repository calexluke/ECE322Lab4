/*
 * longPressStateMachine.h
 *
 *  Created on: Oct 23, 2021
 *      Author: alex
 */

#ifndef LONGPRESSSTATEMACHINE_H_
#define LONGPRESSSTATEMACHINE_H_

enum longPressStates {buttonsOff, buttonsHeld, button1Held, button2Held, servoCenter, servoCCW, servoCW} longPressState;
void longPressTick();
void longPressStateTransition();
void longPressStateActions();

#endif /* LONGPRESSSTATEMACHINE_H_ */
