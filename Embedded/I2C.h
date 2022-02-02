/* 
 * I2C.h
 * 
 * Header file for I2C functions
 */

#ifndef I2C_H
#define	I2C_H

void initI2C(int);
void startI2C();
void repStartI2C();
void stopI2C();
void sendByteI2C(char);
char getByteI2C();

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

