#include <msp430.h> 
#include "msp430BuiltInIO.h"
#include "servoControl.h"
#include "encoder.h"
#include "longPressStateMachine.h"
#include "encoderStateMachine.h"
#include "global.h"

/**
 * main.c
 */

void detectButtonTap();
void configBoard();
void init();

int main(void)
{
    configBoard();
    init();

    while(1) {
        button1 = readButton1();
        button2 = readButton2();
        encoderA = readEncoderA();
        encoderB = readEncoderB();

        detectButtonTap();
        longPressTick();
        encoderTick();
        timerFlag = 0;
    }

	return 0;
}

void configBoard() {
    // IO and timer config
    WDTCTL = WDTPW | WDTHOLD;
    configureBuiltInIO();
    configureIOForServo();
    configureIOForEncoder();
    configureTimersForServo();
    PM5CTL0 &= ~LOCKLPM5;
}

void init() {
    // set initial values for states and variables
    setServo(CENTER);
    longPressState = buttonsOff;
    encoderState = waitForDetent;
    button1Previous = NOT_PRESSED;
    button2Previous = NOT_PRESSED;
}

void detectButtonTap() {
    // detect rising edge of button taps
    if (button1 == PRESSED && button1Previous == NOT_PRESSED) {
        stepServoCounterClockwise();
    }

    if (button2 == PRESSED && button2Previous == NOT_PRESSED) {
        stepServoClockwise();
    }

    button1Previous = button1;
    button2Previous = button2;
}

// Timer0_A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void timer0Interrupt (void)
{
    timerFlag = 1;
}

