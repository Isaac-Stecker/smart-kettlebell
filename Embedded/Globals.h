/*
 * Globals.h
 * 
 * Header file for global constants used in the Smart Kettlebell program
 */

#ifndef GLOBALS_H
#define	GLOBALS_H

// MMA8451 registers
#define F_SETUP 0x09     // reg for FIFO buffer settings. If read and value is 0, FIFO is off
#define CTRL_REG_1 0x2A  // control register 1. Only used to turn accel to active mode for now
#define WHO_AM_I 0x0D    // returns 0x1A when read
#define OUT_X_MSB 0x01   // MSB of x-axis
#define OUT_X_LSB 0x02   // LSB of x-axis
#define OUT_Y_MSB 0x03   // MSB of y-axis
#define OUT_Y_LSB 0x04   // LSB of y-axis
#define OUT_Z_MSB 0x05   // MSB of z-axis
#define OUT_Z_LSB 0x06   // LSB of z-axis

// MMA8451 Constants
#define WRITE_CMD 0x3A   // address of accel with write bit set
#define READ_CMD 0x3B    // address of accel with read bit set
#define ACTIVE 0x01      // used for setting accel to active mode (note: using this byte to write to control reg 1)
#define STANDBY 0x00     // used for setting accel to standby mode (note: using this byte to write to control reg 1)

// LCD globals

// Bluetooth globals

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* GLOBALS_H */

