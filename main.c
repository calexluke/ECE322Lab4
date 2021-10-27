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

BUTTON_STATE button1;
BUTTON_STATE button2;
BUTTON_STATE button1Previous;
BUTTON_STATE button2Previous;
encoderPinState encoderA;
encoderPinState encoderB;

int timerFlag1ms = 0;
int timerFlag20ms = 0;

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
        if(timerFlag20ms) longPressTick(button1, button2);
        if(timerFlag1ms) encoderTick(encoderA, encoderB);
        timerFlag20ms = 0;
        timerFlag1ms = 0;
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
    configureTimerForEncoder();
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

// Timer0_A0 interrupt service routine - 20ms timer
#pragma vector = TIMER0_A0_VECTOR
__interrupt void timer0Interrupt (void)
{
    timerFlag20ms = 1;
}

// Timer1_A0 interrupt service routine - 1ms timer
#pragma vector = TIMER1_A0_VECTOR
__interrupt void timer1Interrupt (void)
{
    timerFlag1ms = 1;
}

