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
   CNPUDbits.CNPUD6 = 1;       // Enable Internal Pull-up resistor to eliminate bouncing
    
}