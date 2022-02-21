/*
 * MMA8450.c
 * 
 * Implementation file for the MMA8450 accelerometer interfaced with a PIC24...
 */

#include <xc.h>
#include "I2C.h"
#include "Funcs.h"

#define WRITE_CMD 0x3A
#define READ_CMD 0x3B

#define MSB_BIT_7 10000
#define MSB_BIT_6 5000
#define MSB_BIT_5 2500
#define MSB_BIT_4 1250
#define MSB_BIT_3 625
#define MSB_BIT_2 313
#define MSB_BIT_1 156
#define LSB_BIT_8 78
#define LSB_BIT_7 39
#define LSB_BIT_6 20
#define LSB_BIT_5 10
#define LSB_BIT_4 5
#define LSB_BIT_3 2


// order to read reg: WRITE_CMD -> ACCEL_REG -> repeated start -> READ_CMD

//initialize the accelerometer. reg selects the control register, value is the value assigned to the register
void mmaWriteReg(char reg, char value){
    startI2C();
    sendByteI2C(WRITE_CMD);
    while(I2C1STATbits.ACKSTAT);
    us_delay(100);
    sendByteI2C(reg);
    while(I2C1STATbits.ACKSTAT);
    us_delay(100);
    sendByteI2C(value);
    while(I2C1STATbits.ACKSTAT);
    us_delay(100);
    stopI2C();
}

// read a register associated with a certain axis (x, y, z)
unsigned char mmaReadAxis(char axis){
    unsigned char dummy;
    startI2C();
    sendByteI2C(WRITE_CMD);
    while(I2C1STATbits.ACKSTAT);
    us_delay(100);
    sendByteI2C(axis);
    while(I2C1STATbits.ACKSTAT);
    us_delay(100);
    repStartI2C();
    us_delay(2);
    sendByteI2C(READ_CMD);
    while(I2C1STATbits.ACKSTAT);
    us_delay(100);
    dummy = getByteI2C();
    us_delay(100);
    stopI2C();
    return dummy;
}

// convert MSB and LSB accelerometer measurement to g's in fractional form. Returns a integer that was shifted 4 times from a decimal, i.e., 0.5 = 5000
int convertAccelerationForAxis(unsigned char axisMSB, unsigned char axisLSB) {
    int acceleration = 0;
    int sign = 0;
    
    // determine the sign of the acceleration
    if(axisMSB > 0x7F){
        sign = 1;
        
        //convert 2s complement to binary
        axisMSB = ~axisMSB;
        axisMSB += 0x01;
    }
    
    // determine the magnitude of the acceleration's MSBs
    if(axisMSB & 0x40){
        acceleration += MSB_BIT_7;
    }
    if(axisMSB & 0x20){
        acceleration += MSB_BIT_6;
    }
    if(axisMSB & 0x10){
        acceleration += MSB_BIT_5;
    }
    if(axisMSB & 0x08){
        acceleration += MSB_BIT_4;
    }
    if(axisMSB & 0x04){
        acceleration += MSB_BIT_3;
    }
    if(axisMSB & 0x02){
        acceleration += MSB_BIT_2;
    }
    if(axisMSB & 0x01){
        acceleration += MSB_BIT_1;
    }
    
    // determine the magnitude of the acceleration's LSBs
    if(axisLSB & 0x80){
        acceleration += LSB_BIT_8;
    }
    if(axisLSB & 0x40){
        acceleration += LSB_BIT_7;
    }
    if(axisLSB & 0x20){
        acceleration += LSB_BIT_6;
    }
    if(axisLSB & 0x10){
        acceleration += LSB_BIT_5;
    }
    if(axisLSB & 0x08){
        acceleration += LSB_BIT_4;
    }
    if(axisLSB & 0x04){
        acceleration += LSB_BIT_3;
    }
    
    // set the sign of the acceleration
    if(sign){
        acceleration *= -1;
    }
    return acceleration;
}
