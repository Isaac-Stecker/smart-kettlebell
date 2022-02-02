/*
 * LCD.c
 * 
 * Header file for the (part #) LCD using the PMP of the PIC24...
 */

#define LCD_SendData(data) { PMADDR = 0x0001; PMDIN1 = data; ms_delay(1); }
#define LCD_SendCommand(command, delay) { PMADDR = 0x0000; PMDIN1 = command; ms_delay(delay); }
#define LCD_COMMAND_CLEAR_SCREEN        0x01
#define LCD_COMMAND_RETURN_HOME         0x02
#define LCD_COMMAND_ENTER_DATA_MODE     0x06
#define LCD_COMMAND_CURSOR_OFF          0x0C
#define LCD_COMMAND_CURSOR_ON           0x0F
#define LCD_COMMAND_MOVE_CURSOR_LEFT    0x10
#define LCD_COMMAND_MOVE_CURSOR_RIGHT   0x14
#define LCD_COMMAND_SET_MODE_4_BIT      0x28
#define LCD_COMMAND_SET_MODE_8_BIT      0x38
#define LCD_COMMAND_ROW_0_HOME          0x80
#define LCD_COMMAND_ROW_1_HOME          0xC0
#define LCD_START_UP_COMMAND_1          0x33    
#define LCD_START_UP_COMMAND_2          0x32   
#define putLCD( d) LCD_SendData((d))
#define setCursorLine1() LCD_SendCommand(LCD_COMMAND_ROW_0_HOME, 1)
#define setCursorLine2() LCD_SendCommand(LCD_COMMAND_ROW_1_HOME, 1)

#include <xc.h>
#include "Funcs.h"

// clear the LCD screen and return the cursor to the home position
void clearScreen(){
    LCD_SendCommand ( LCD_COMMAND_CLEAR_SCREEN , 2 ) ;
    LCD_SendCommand ( LCD_COMMAND_RETURN_HOME , 2) ;
}

// Initialize the LCD
void InitLCD(){
    PMMODE = 0x03ff ;
    // Enable PMP Module, No Address & Data Muxing,
    // Enable RdWr Port, Enable Enb Port, No Chip Select,
    // Select RdWr and Enb signals Active High
    PMCON = 0x8383 ;
    // Enable A0
    PMAEN = 0x0001 ;

    ms_delay ( 60 ) ;
    ms_delay ( 60 ) ;
    
    LCD_SendCommand ( LCD_START_UP_COMMAND_1 , 1) ;
    LCD_SendCommand ( LCD_START_UP_COMMAND_2 , 1) ;

    LCD_SendCommand ( LCD_COMMAND_SET_MODE_8_BIT ,     1 ) ;
    LCD_SendCommand ( LCD_COMMAND_CURSOR_OFF ,         1 ) ;
    LCD_SendCommand ( LCD_COMMAND_ENTER_DATA_MODE ,    1 ) ;

    clearScreen ( ) ;
}

// set the cursor to a certain line of the LCD
void setCursorAtLine(int i){
    if(i == 1){
        setCursorLine1();
    }
    else if(i == 2){
        setCursorLine2();
    }
}

// write a char array to the LCD
void putsLCD(char* s){
    while(*s){
        putLCD( *s++);
    }
}
