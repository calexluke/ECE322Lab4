#include <msp430.h>
#include "encoderStateMachine.h"
#include "servoControl.h"
#include "encoder.h"
#include "global.h"

/*
 * encoderStateMachine.c
 *
 *  Created on: Oct 23, 2021
 *      Author: alex
 */

bool encoderIsInDetent() {
    if (encoderA == HIGH && encoderB == HIGH) {
        return true;
    } else {
        return false;
    }
}

void encoderTick() {
    encoderStateTransition();
    encoderStateActions();
    setLEDsForDebug();
}

void encoderStateTransition() {
    switch (encoderState) {

        case waitForDetent:
            if (encoderIsInDetent() == true) {
                encoderState = detent;
            } else {
                encoderState = waitForDetent;
            }
            break;

        case detent:
            if (encoderIsInDetent() == true) {
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
            // do nothing
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

void setLEDsForDebug() {
    // allows you to see the encoder state visually using the onboard LEDs
    if (encoderA == HIGH) {
        setLED1(ON);
    } else {
        setLED1(OFF);
    }

    if (encoderB == HIGH) {
        setLED2(ON);
    } else {
        setLED2(OFF);
    }
}
