/* 
 * File:   switch.c
 * Author: jeanette
 *
 * Created on August 27, 2015, 3:12 PM
 */

#include <xc.h>

#define INPUT 1
#define OUTPUT 0

void initSwitch1(){
    //TODO: Initialize switch 1
    
   TRISDbits.TRISD6 = INPUT;   // Enable input for switch (next to red LED)
    //CNCONDbits.ON = 1;          // Turn on Change Notification(CN) device
    //CNENDbits.CNIED6 = 1;       // Enable CN interrupt for pin
    //IEC1bits.CNDIE = 1;         // Enable overall CN Interrupt
   // IFS1bits.CNDIF = 0;         // Put Interrupt flag down
    CNPUDbits.CNPUD6 = 1;       // Enable Internal Pull-up resistor to eliminate bouncing
    
}