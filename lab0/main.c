/* 
 * File:   main.c
 * Author: jeanette
 * Description: lab 0.
 * Created on August 27, 2015, 10:14 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "switch.h"
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"

#define OUTPUT 0
#define INPUT 1

//TODO: Define states of the state machine

//LED_1 = LATDbits.LATD0;

typedef enum stateTypeEnum {
    led1, led2, led3, wait, wait2, debouncePress, debounceRelease, debounceRelease2
} stateType;

//TODO: Use volatile variables that change within interrupts
volatile stateType state = led2;

int main() {

    //This function is necessary to use interrupts. 
    enableInterrupts();

    //TODO: Write each initialization function
    initSwitch1();
    initLEDs();
    initTimer2();
    initTimer1();


    while (1) {

        //TODO: Implement a state machine to create the desired functionality
        switch (state) {
            case led1:
                turnOnLED(1); // turns on led1
                if (PORTDbits.RD6 == 0) { // IFS1bits.CNDIF == 1)if the switch is pressed
                    state = debouncePress;
                    IFS0bits.T1IF = 0;
                    TMR1 = 0;
                    T1CONbits.TON = 1;
                }
                break;

            case led2:
                turnOnLED(2); // turns on led2
                if (PORTDbits.RD6 == 0) { // if the switch is pressed
                    state = debouncePress;
                    IFS0bits.T1IF = 0;
                    TMR1 = 0;
                    T1CONbits.TON = 1;
                }
                break;

            case led3:
                turnOnLED(3); // turns on led3
                if (PORTDbits.RD6 == 0) { // && PORTDbits.RD6 == 1if the switch is pressed
                    state = debouncePress;
                    IFS0bits.T1IF = 0;
                    TMR1 = 0;
                    T1CONbits.TON = 1;
                }
                break;

            case wait:
                if (PORTDbits.RD6 == 1) {
                    if (IFS0bits.T1IF == 1) { // after two seconds occurs goes to wait 2
                        state = wait2;
                    }
                    // if button is released before 2 sec go to correct state
                    else  state = debounceRelease;
                    
                }
                break;

            case wait2:

                 // wait until button is released
                    state = debounceRelease2;
              
                // Then go to debounceRelease2 that will go to correct state
                break;

            case debouncePress:
                delayMs(10);
                // waits for delays a few ms
                    state = wait; // go to the first wait state
                
                break;

            case debounceRelease:
                delayMs(10);
                T1CONbits.TON = 0;// waits for delay
                    if (LATDbits.LATD0 == 1) {//if on led1
                        state = led2;
                    } else if (LATDbits.LATD1 == 1) {// if on led2
                        state = led3;
                    } else if (LATDbits.LATD2 == 1) {// if on led3
                        state = led1;
                    }
                
                // the release case for under 2 seconds to go forward
                break;

            case debounceRelease2:
                delayMs(10);
                T1CONbits.TON = 0;
                if (LATDbits.LATD0 == 1) {// delays a few ms
                    state = led3;
                } else if (LATDbits.LATD1 == 1) {// delays a few ms
                    state = led1;
                } else if (LATDbits.LATD2 == 1) {// delays a few ms
                    state = led2;
                }
                // the release case for over 2 seconds to go backwards
                break;

        }
    }

    return 0;
}

