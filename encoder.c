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

void configureTimerForEncoder() {
    // Configure Timer1_A period
    TA1CCR0 = ENCODER_TIMER_PERIOD;

    // interrupt enabled
    TA1CCTL0 = CCIE;

    // Configure TimerA1 mode and GO
    TA1CTL = TASSEL__SMCLK | MC__UP | TACLR;   // SMCLK, up mode, clear TAR

}

encoderPinState readEncoderA() {
    int input = P2IN & (0x01 << 4);
    return (input != 0) ? HIGH : LOW;
}

encoderPinState readEncoderB() {
    int input = P2IN & (0x01 << 5);
    return (input != 0) ? HIGH : LOW;
}
