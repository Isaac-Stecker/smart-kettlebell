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
    char line[16];
    char test[16] = "Before read";
    
    // test read before main loop
    sprintf(line, "%s", test);
    putsLCD(&line);
    
    clearScreen();
    axis = mmaReadAxis(F_SETUP);
    sprintf(line, "Who: %d", axis);
    putsLCD(&line);
    
    // turn on accelerometer
    mmaWriteReg(CTRL_REG_1, ACTIVE);
    
    //main loop
    while(1){
        axis = mmaReadAxis(OUT_X_MSB);
        ms_delay(20);
    }
    return 0;
}
