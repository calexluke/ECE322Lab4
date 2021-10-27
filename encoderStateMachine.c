#include <msp430.h>
#include "encoderStateMachine.h"
#include "servoControl.h"
#include "global.h"

/*
 * encoderStateMachine.c
 *
 *  Created on: Oct 23, 2021
 *      Author: alex
 */

#define DEBOUNCE_DELAY_MS 10
int debounceCounter = 0;

bool encoderIsInDetent(encoderPinState encoderA, encoderPinState encoderB) {
    if (encoderA && encoderB) {
        return true;
    } else {
        return false;
    }
}

void encoderTick(encoderPinState encoderA, encoderPinState encoderB) {
    encoderStateTransition(encoderA, encoderB);
    encoderStateActions();
    setLEDsForDebug(encoderA, encoderB);
}

void encoderStateTransition(encoderPinState encoderA, encoderPinState encoderB) {
    switch (encoderState) {

        case waitForDetent:
            if (encoderIsInDetent(encoderA, encoderB)) {
                encoderState = debounce;
            } else {
                encoderState = waitForDetent;
            }
            break;

        case debounce:
            // check for detent again after debounce delay to make sure we really are in detent
            if (debounceCounter >= DEBOUNCE_DELAY_MS && encoderIsInDetent(encoderA, encoderB)) {
                // debounce period over, still in detent.
                encoderState = detent;
            } else if (debounceCounter < DEBOUNCE_DELAY_MS) {
                // keep waiting for debounce period
                encoderState = debounce;
            } else {
                // debounce period over, but encoder not in detent. Must have caught a bounce in waitForDetent.
                // go back and look for another detent state
                encoderState = waitForDetent;
            }
            break;

        case detent:
            if (encoderIsInDetent(encoderA, encoderB)) {
                encoderState = detent;
            } else if (encoderA == LOW && encoderB == HIGH){
                encoderState = CCWTick;
            } else if (encoderA == HIGH && encoderB == LOW){
                encoderState = CWTick;
            } else {
                encoderState = waitForDetent;
            }
            break;

        case CCWTick:
            encoderState = waitForDetent;
            break;

        case CWTick:
            encoderState = waitForDetent;
            break;

        default:
            encoderState = waitForDetent;
            break;
        }
}

void encoderStateActions() {
    switch (encoderState) {
        case waitForDetent:
            debounceCounter = 0;
            break;
        case debounce:
            debounceCounter += 1;
            break;
        case detent:
            // do nothing
            break;
        case CCWTick:
            stepServoCounterClockwise();
            break;
        case CWTick:
            stepServoClockwise();
            break;
        default:
            // do nothing
            break;
        }
}

void setLEDsForDebug(encoderPinState encoderA, encoderPinState encoderB) {
    // allows you to see the encoder state visually using the onboard LEDs
    if (encoderA) {
        setLED1(ON);
    } else {
        setLED1(OFF);
    }

    if (encoderB) {
        setLED2(ON);
    } else {
        setLED2(OFF);
    }
}
