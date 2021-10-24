#include <msp430.h>
#include "encoder.h"

/*
 * encoder.c
 *
 *  Created on: Oct 23, 2021
 *      Author: alex
 */

void configureIOForEncoder() {

    // pin A: P2.4
    // pin B: P2.5
    // pin C: ground

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
