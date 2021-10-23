#include <msp430.h> 
#include "msp430BuiltInIO.h"
#include "servoControl.h"
#include "longPressStateMachine.h"
#include "global.h"


BUTTON_STATE button1Previous = NOT_PRESSED;
BUTTON_STATE button2Previous = NOT_PRESSED;

int timerCounter = 0;

/**
 * main.c
 */
int main(void)
{
    // stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;

    configureBuiltInIO();
    configureIOForServo();
    configureTimersForServo();

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    setServo(CENTER);
    longPressState = buttonsOff;

    while(1) {
        button1 = readButton1();
        button2 = readButton2();

        if (button1 == PRESSED && button1Previous == NOT_PRESSED) {
            stepServoCounterClockwise();

            // LED1 toggle for debugging
            //toggleLED1();
        }

        if (button2 == PRESSED && button2Previous == NOT_PRESSED) {

            stepServoClockwise();

            // LED2 toggle for debugging
            //toggleLED2();
        }

        button1Previous = button1;
        button2Previous = button2;

        longPressTick();
        timerFlag = 0;

    }

	return 0;
}

// Timer0_A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void timer0Interrupt (void) // change name of timer interrupt routine
{
    timerCounter++;
    if (timerCounter > 10) {
        //toggleLED1();
        //toggleLED2();
        timerCounter = 0;
    }
    timerFlag = 1;
}

