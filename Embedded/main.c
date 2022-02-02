/*
 * main.c
 *
 * Main file for the Smart Kettlebell
 */

#include "config.h"
#include "Globals.h"
#include "I2C.h"
#include "Funcs.h"
#include "LCD.h"
#include "MMA8451q.h"
#include <stdio.h>

int main(void) {
    // initialization of PIC24... internals
    T1CON = 0x8030;
    T3CON = 0x8000;
    InitLCD();
    ms_delay(120);
    initI2C(0x9D);
    
    // variable declarations
    char axis;
    
    //main loop
    while(1){
        axis = mmaReadAxis(WHO_AM_I);
        ms_delay(20);
    }
    return 0;
}
