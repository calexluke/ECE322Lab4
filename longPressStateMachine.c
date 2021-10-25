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

// counter increments every 20ms period
#define LONG_PRESS_LENGTH 500
#define LONG_PRESS_COUNTER_MAX (LONG_PRESS_LENGTH / 20)

int longPressCounter = 0;

void longPressTick(BUTTON_STATE button1, BUTTON_STATE button2) {
    longPressStateTransition(button1, button2);
    longPressStateActions();
}

void longPressStateTransition(BUTTON_STATE button1, BUTTON_STATE button2) {

    switch (longPressState) {

        case buttonsOff:
            if (button1 == PRESSED && button2 == NOT_PRESSED) {
                longPressState = button1Held;
            } else if (button1 == NOT_PRESSED && button2 == PRESSED) {
                longPressState = button2Held;
            } else if (button1 == PRESSED && button2 == PRESSED) {
                longPressState = bothButtonsHeld;
            } else {
                longPressState = buttonsOff;
            }
            break;

        case bothButtonsHeld:
            if (button1 == NOT_PRESSED || button2 == NOT_PRESSED) {
                // stopped holding button
                longPressState = buttonsOff;
            } else if (longPressCounter >= LONG_PRESS_COUNTER_MAX) {
                longPressState = servoCenter;
            } else {
                longPressState = bothButtonsHeld;
            }
            break;

        case button1Held:
            if (button1 == NOT_PRESSED) {
                // stopped holding button
                longPressState = buttonsOff;
            } else if (button1 == PRESSED && button2 == PRESSED) {
                // user holds other button as well
                longPressState = bothButtonsHeld;
            } else if (longPressCounter >= LONG_PRESS_COUNTER_MAX) {
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
                longPressState = bothButtonsHeld;
            } else if (longPressCounter >= LONG_PRESS_COUNTER_MAX) {
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

        case bothButtonsHeld:
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

