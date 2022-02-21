/*
 * LCD.h
 * 
 * Header file for the (part #) LCD using the PMP of the PIC24...
 */

#ifndef LCD_H
#define	LCD_H

void InitLCD();
void setCursorAtLine(int);
void putsLCD(char*);
void clearScreen();
void moveCursorBack(int);
void moveCursorForward(int);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */
