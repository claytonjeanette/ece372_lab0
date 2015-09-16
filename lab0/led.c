/* 
 * File:   led.c
 * Author: jeanette
 *
 * Created on August 27, 2015, 3:15 PM
 */

#include <xc.h>
#include "led.h"
#include <sys/attribs.h>


#define OUTPUT 0
#define INPUT 1



void initLEDs(){
    
    //TODO: Initialize LEDs
    TRISDbits.TRISD0 = OUTPUT;
    TRISDbits.TRISD1 = OUTPUT;
    TRISDbits.TRISD2 = OUTPUT;
}

void turnOnLED(int led){
    
    //TODO: You may choose to write this function
    // as a matter of convenience
    // turns on led1
    if(led == 1){
        LATDbits.LATD0 = 1;
        LATDbits.LATD1 = 0;
        LATDbits.LATD2 = 0;
        
    }
    // turns on led2
    else if(led == 2){
        LATDbits.LATD0 = 0;
        LATDbits.LATD1 = 1;
        LATDbits.LATD2 = 0;        
    }
    // turns on led3
    else{
        LATDbits.LATD0 = 0;
        LATDbits.LATD1 = 0;
        LATDbits.LATD2 = 1;
    }
}