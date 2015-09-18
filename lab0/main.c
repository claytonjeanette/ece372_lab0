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
typedef enum stateTypeEnum{
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
    
    
    while(1){
       
        //TODO: Implement a state machine to create the desired functionality
        switch(state){
            case led1:
                turnOnLED(1); // turns on led1
                if (IFS1bits.CNDIF == 1){ // IFS1bits.CNDIF == 1)if the switch is pressed
                          state = debouncePress;              
                }
                break;
                
            case led2:
                turnOnLED(2); // turns on led2
                if (IFS1bits.CNDIF == 1){ // if the switch is pressed
                  state = debouncePress;
                }
                break;
                
            case led3:
                turnOnLED(3); // turns on led3
                if (IFS1bits.CNDIF == 1){ // if the switch is pressed
                  state = debouncePress;
                }
                break;
                
            case wait:
                if (PORTDbits.RD6 == 1){
                    if(IFS0bits.T2IF == 1){ // after two seconds occurs goes to wait 2
                        state = wait2; 
                    }
                    if (IFS1bits.CNDIF == 1){ // if button is released before 2 sec go to correct state
                        state = debounceRelease; 
                    }  
                } 
                break;
                
            case wait2:
                state=led3;
                if (IFS1bits.CNDIF == 0) {  // wait until button is released
                   // state = debounceRelease2;
                }
                // Then go to debounceRelease2 that will go to correct state
                break;
                
            case debouncePress:
                if (T2CONbits.ON == 1){// waits for delays a few ms
                    state = wait;// go to the first wait state
                }
                break;
                
            case debounceRelease:
               if (T2CONbits.ON == 1){ // waits for delay
                 if ( LATDbits.LATD0 == 1 ){//if on led1
                     state = led2;
                  }
                 else if ( LATDbits.LATD1 == 1 ){// if on led2
                     state = led3;
                 }
                 else if (LATDbits.LATD2 == 1 ){// if on led3
                      state = led1;
                 }
               }
                // the release case for under 2 seconds to go forward
                break;
                
            case debounceRelease2:
                
                if (T2CONbits.ON == 0 && LATDbits.LATD0 == 1 ){// delays a few ms
                    state = led1;
                }
                else if (T2CONbits.ON == 0 && LATDbits.LATD1 == 1 ){// delays a few ms
                    state = led2;
                }
                else if (T2CONbits.ON == 0 && LATDbits.LATD2 == 1 ){// delays a few ms
                    state = led3;
                }
                // the release case for over 2 seconds to go backwards
                break;
                
        }
    }
    
    return 0;
}

