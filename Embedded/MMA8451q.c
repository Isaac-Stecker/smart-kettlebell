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
#define OUT_X_MSB 0x01
#define OUT_X_LSB 0x02
#define OUT_Y_MSB 0x03
#define OUT_Z_MSB 0x05

// order to read reg: WRITE_CMD -> ACCEL_REG -> repeated start -> READ_CMD

// read a register associated with a certain axis (x, y, z)
char mmaReadAxis(char axis){
    char dummy;
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