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

void configureIOForEncoder() {

    // input A: P2.4
    // input B: P2.5
    // input C: ground

    // P2.4 pullup resistor
    // Encoder input A
    P2REN |= (0x01 << 4);
    P2OUT |= (0x01 << 4);

    // P2.5 pullup resistor
    // encoder input B
    P2REN |= (0x01 << 5);
    P2OUT |= (0x01 << 5);
}

encoderPinState readEncoderA() {
    int input = P2IN & (0x01 << 4);
    return (input != 0) ? HIGH : LOW;
}

encoderPinState readEncoderB() {
    int input = P2IN & (0x01 << 5);
    return (input != 0) ? HIGH : LOW;
}

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
