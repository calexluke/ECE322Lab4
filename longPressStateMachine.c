#include <msp430.h>
#include "msp430BuiltInIO.h"
#include "servoControl.h"
#include "longPressStateMachine.h"
#include "global.h"

/*
 * longPressStateMachine.c
 *
 *  Created on: Oct 23, 2021
 *      Author: alex
 */

// will count up every 20ms period
// 25 * 20 = 500ms
const int LONG_PRESS_VALUE = 25;
int longPressCounter = 0;

void longPressTick() {

    longPressStateTransition();
    longPressStateActions();
}

void longPressStateTransition() {

    switch (longPressState) {

        case buttonsOff:
            if (button1 == PRESSED && button2 == NOT_PRESSED) {
                longPressState = button1Held;
            } else if (button1 == NOT_PRESSED && button2 == PRESSED) {
                longPressState = button2Held;
            } else if (button1 == PRESSED && button2 == PRESSED) {
                longPressState = buttonsHeld;
            } else {
                longPressState = buttonsOff;
            }
            break;

        case buttonsHeld:
            if (button1 == NOT_PRESSED || button2 == NOT_PRESSED) {
                // user let go of any button
                longPressState = buttonsOff;
            } else if (longPressCounter >= LONG_PRESS_VALUE) {
                longPressState = servoCenter;
            } else {
                longPressState = buttonsHeld;
            }
            break;

        case button1Held:
            if (button1 == NOT_PRESSED) {
                // user let go of button
                longPressState = buttonsOff;
            } else if (button1 == PRESSED && button2 == PRESSED) {
                // user holds other button as well
                longPressState = buttonsHeld;
            } else if (longPressCounter >= LONG_PRESS_VALUE) {
                longPressState = servoCCW;
            } else {
                longPressState = button1Held;
            }
            break;

        case button2Held:
            if (button2 == NOT_PRESSED) {
                // user let go of button
                longPressState = buttonsOff;
            } else if (button1 == PRESSED && button2 == PRESSED) {
                // user holds other button as well
                longPressState = buttonsHeld;
            } else if (longPressCounter >= LONG_PRESS_VALUE) {
                longPressState = servoCW;
            } else {
                longPressState = button2Held;
            }
            break;

        case servoCenter:
            longPressState = buttonsOff;
            break;
        case servoCCW:
            longPressState = buttonsOff;
            break;
        case servoCW:
            longPressState = buttonsOff;
            break;
        default:
            longPressState = buttonsOff;
            break;

    }
}

void longPressStateActions() {

    switch (longPressState) {

        case buttonsOff:
            longPressCounter = 0;
            break;

        case buttonsHeld:
            if (timerFlag == 1) longPressCounter++;
            break;

        case button1Held:
            if (timerFlag == 1) longPressCounter++;
            break;

        case button2Held:
            if (timerFlag == 1) longPressCounter++;
            break;

        case servoCenter:
            setServo(CENTER);
            break;
        case servoCCW:
            setServo(CCW_MAX);
            break;
        case servoCW:
            setServo(CW_MAX);
            break;
        default:
            // do nothing
            break;

    }
}

