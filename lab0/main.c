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

#define led_1 LATDbits.LATD0
#define led_2 LATDbits.LATD1
#define led_3 LATDbits.LATD2

#define button PORTDbits.RD6

#define timer1_flag IFS0bits.T1IF
#define timer1_cn T1CONbits.TON

//TODO: Define states of the state machine

typedef enum stateTypeEnum {
    led1, led2, led3, wait, wait2, debouncePress, debounceRelease, debounceRelease2
} stateType;

//TODO: Use volatile variables that change within interrupts
volatile stateType state = led1;

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
                turnOnLED(1); 
                if (button == 0) { // )if the switch is pressed
                    state = debouncePress;
                    timer1_flag = 0;
                    TMR1 = 0;
                    timer1_cn = 1;
                }
                break;

            case led2:
                turnOnLED(2); 
                if (button == 0) { // if the switch is pressed
                    state = debouncePress;
                    timer1_flag = 0;
                    TMR1 = 0;
                    timer1_cn = 1;
                }
                break;

            case led3:
                turnOnLED(3); 
                if (button == 0) { // if the switch is pressed
                    state = debouncePress;
                    timer1_flag = 0;
                    TMR1 = 0;
                    timer1_cn = 1;
                }
                break;

            case wait:
                if (button == 1) {
                    if (timer1_flag == 1) { // after two seconds occurs goes to wait 2
                        state = wait2;
                    }
                    else  state = debounceRelease; // if button is released before 2 sec go to correct state
                }
                break;

            case wait2: // Then go to debounceRelease2 that will go to correct state
                state = debounceRelease2;
                break;

            case debouncePress:
                delayMs(10); // delays a few ms
                state = wait; // go to the first wait state
                break;

            case debounceRelease: // the release case for under 2 seconds to go forward
                delayMs(10);
                timer1_cn = 0;
                    if (led_1 == 1) {
                        state = led2;
                    } 
                    else if (led_2 == 1) {
                        state = led3;
                    } 
                    else if (led_3 == 1) {
                        state = led1;
                    }
                break;

            case debounceRelease2: // the release case for over 2 seconds to go backwards
                delayMs(10);// delays a few ms
                timer1_cn = 0;
                if (led_1 == 1) {
                    state = led3;
                } 
                else if (led_2 == 1) {
                    state = led1;
                } 
                else if (led_3 == 1) {
                    state = led2;
                }
                break;

        }
    }

    return 0;
}

