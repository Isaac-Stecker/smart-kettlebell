/* 
 * I2C.c
 * 
 * Implementation file for I2C functions
 */

#include "I2C.h"
#include "Funcs.h"
#include <xc.h>

// initialize the I2C module
void initI2C(int BRIG){
    I2C1BRG = BRIG;
    I2C1CONbits.I2CEN = 1;
}

// create a I2C start condition
void startI2C(){
    us_delay(10);
    I2C1CONbits.SEN = 1;
    while(I2C1CONbits.SEN);
    us_delay(10);
}

// create a I2C repeated start condition
void repStartI2C(){
    I2C1CONbits.RSEN = 1;
    while(I2C1CONbits.RSEN);
    us_delay(10);
}

// create a I2C stop condition
void stopI2C(){
    us_delay(10);
    I2C1CONbits.PEN = 1;
    while(I2C1CONbits.PEN);
    us_delay(10);
}

// send a byte via I2C
void sendByteI2C(char data){
    while(I2C1STATbits.TBF);
    I2C1TRN = data;
    us_delay(10);
}

// receive a byte via I2C
char getByteI2C(){
    //char message[] = "Entered getByte";
    //putsLCD(message);
    I2C1CONbits.RCEN = 1;
    while(I2C1STATbits.RBF);
    I2C1CONbits.ACKEN = 1;
    us_delay(10);
    return(I2C1RCV);
}
