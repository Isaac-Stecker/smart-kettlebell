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
    float xAcceleration = 0;
    float yAcceleration = 0;
    float zAcceleration = 0;
    float baseLineAcceleration = 0;
    float currentAcceleration = 0;
    char line[16];
    
    // turn on accelerometer
    mmaWriteReg(CTRL_REG_1, ACTIVE);
    
    // obtain baseline acceleration reading
    xMSB = mmaReadAxis(OUT_X_MSB);
    us_delay(10);
    xLSB = mmaReadAxis(OUT_X_LSB);
    us_delay(10);
    xAcceleration = convertAccelerationForAxis(xMSB, xLSB);
    yMSB = mmaReadAxis(OUT_Y_MSB);
    us_delay(10);
    yLSB = mmaReadAxis(OUT_Y_LSB);
    us_delay(10);
    yAcceleration = convertAccelerationForAxis(yMSB, yLSB);
    zMSB = mmaReadAxis(OUT_Z_MSB);
    us_delay(10);
    zLSB = mmaReadAxis(OUT_Z_LSB);
    us_delay(10);
    zAcceleration = convertAccelerationForAxis(zMSB, zLSB);
    baseLineAcceleration = calculateTotalAcceleration(xAcceleration, yAcceleration, zAcceleration);
    
    // main loop
    while(1){
        xMSB = mmaReadAxis(OUT_X_MSB);
        ms_delay(20);
    }
    return 0;
}
