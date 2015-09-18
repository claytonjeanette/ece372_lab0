/* 
 * File:   timer.c
 * Author: jeanette
 *
 * Created on August 27, 2015, 3:26 PM
 */

#include <xc.h>

void initTimer1(){
    //TODO: Initialize Timer 1 to have a period of
    // 1 second. Enable its interrupt
    TMR1 = 0;// clears Timer1
    PR1 = 1221*4;// Initialize PR1 for a 1 sec timer
    T1CONbits.TCKPS = 3; // Initialize pre-scalar
    T1CONbits.TCS = 0; // Setting the oscillator for Timer 1
    //IEC0bits.T1IE = 1;// Enable the interrupt
   // IFS0bits.T1IF = 0;// Put the flag down
   // IPC1bits.T1IP = 3;// Configure the Interrupt Priority
    T1CONbits.TON = 1;// Turn the timer on
}

initTimer2(){
    //TODO: Initialize Timer 2.
    TMR2 = 0;// clears Timer2
   // Initialize Priority Register 1 for a 2 sec timer
    T2CONbits.TCKPS = 0; // Initialize pre-scalar
    T2CONbits.TCS = 0; // Setting the oscillator for Timer 2
   // IEC0bits.T2IE = 1;// Enable the interrupt for Timer 2
   // IFS0bits.T2IF = 0;// Put the flag down
   // IPC2bits.T2IP = 3;// Configure the Interrupt Priority
    T2CONbits.TON = 1;// Turn the timer on
    
}

delayMs(int delay){
    //TODO: Using timer 2, create a delay
    // that is delay amount of 1 ms
    TMR2 = 0;
    PR2 = delay*624;
    IFS0bits.T2IF = 0;
    T2CONbits.ON = 1;
    while(IFS0bits.T2IF == 0);
    T2CONbits.ON = 0;
}