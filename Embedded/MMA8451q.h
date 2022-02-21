/*
 * MMA8450.h
 * 
 * Header file for the MMA8450 accelerometer interfaced with a PIC24...
 */

#ifndef MMA8450_H
#define	MMA8450_H

void mmaWriteReg(char, char);
unsigned char mmaReadAxis(char);
int convertAccelerationForAxis(unsigned char, unsigned char);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* MMA8450_H */
