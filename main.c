#include <msp430.h> 
#include "msp430BuiltInIO.h"
#include "servoControl.h"
#include "longPressStateMachine.h"
#include "encoderStateMachine.h"
#include "global.h"

/**
 * main.c
 */
int main(void)
{
    // stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;

    configureBuiltInIO();
    configureIOForServo();
    configureIOForEncoder();
    configureTimersForServo();

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    setServo(CENTER);
    longPressState = buttonsOff;
    encoderState = waitForDetent;

    while(1) {
        button1 = readButton1();
        button2 = readButton2();
        encoderA = readEncoderA();
        encoderB = readEncoderB();

        buttonTapTick();
        longPressTick();
        encoderTick();
        timerFlag = 0;
    }

	return 0;
}

// Timer0_A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void timer0Interrupt (void)
{
    timerFlag = 1;
}

