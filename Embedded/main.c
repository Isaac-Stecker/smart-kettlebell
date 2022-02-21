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
    unsigned char xMSB;
    unsigned char xLSB;
    unsigned char yMSB;
    unsigned char yLSB;
    unsigned char zMSB;
    unsigned char zLSB;
    int xAcceleration = 0;
    int yAcceleration = 0;
    int zAcceleration = 0;
    int baselineX = 0;
    int baselineY = 0;
    int baseilneZ = 0;
    char line[16];
    int temp1 = 0;
    int temp2 = 0;
    
    // turn on accelerometer
    mmaWriteReg(CTRL_REG_1, ACTIVE);
    
    // test conversion functions
    xMSB = mmaReadAxis(OUT_X_MSB);
    us_delay(10);
    xLSB = mmaReadAxis(OUT_X_LSB);
    xAcceleration = convertAccelerationForAxis(xMSB, xLSB);
    sprintf(line, "X: %d", xAcceleration);
    putsLCD(&line);
    moveCursorBack(3);
    putsLCD("abc");
    
    // main loop
    while(1){
        xMSB = mmaReadAxis(OUT_X_MSB);
        ms_delay(20);
    }
    return 0;
}
