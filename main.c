/* 
 * File:   main.c
 * Author: rd106
 *
 * Created on November 13, 2021, 5:32 PM
 */
#include "mcc_generated_files/system.h"
#include <stdio.h>
#include "xc.h"


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

//Delay Function
void ms_delay(int N){
    T1CON = 0x8030;
    TMR1 = 0;
     while(TMR1 < N*(125/2));
}
//LCD Functions
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

    clearScreen () ;
}
void setCursorAtLine(int i){
    if(i == 1){
        setCursorLine1();
    }
    else if(i == 2){
        setCursorLine2();
    }
}
void putsLCD(char* s){
    while(*s){
        putLCD( *s++);
    }
}
void clearScreen(){
    LCD_SendCommand ( LCD_COMMAND_CLEAR_SCREEN , 2 ) ;
    LCD_SendCommand ( LCD_COMMAND_RETURN_HOME , 2) ;
}

//uart
#define CTS _RD6
#define RTS _RF12
/*void initUART(int BRG)
{
    U2BRG=BRG;
    U2MODE = 0x8000;
    
    U2STA = 0x0400;
    /*U2MODEbits.UARTEN = 1;
    U2STAbits.UTXEN = 1;       
    IEC1bits.U2RXIE = 0;        // Enable the uart RX interrupt;
    IFS1bits.U2RXIF = 0;        // Reset the rx interrupt flag
     //reset RX interrupt flag     
    IFS0bits.U1RXIF = 0;  
    //set up interrupt for UART1, receive and transmit  
    IFS0bits.U1RXIF = 0;  
    TRISFbits.TRISF12=1;
    RTS=1;
}
void putUART(char c)
{
    while(CTS);
    while(U2STAbits.UTXBF);
    U2TXREG = c;
}
char getUART(void)
{
    RTS=0;
    while(!U2STAbits.URXDA);
    RTS=1;
    return U2RXREG;
}
void putsUART(unsigned int *buffer)
{
   char * temp_ptr = (char *) buffer;

   if(U2MODEbits.PDSEL == 3)        //check if TX is 8bits or 9bits 
   {
       while(*buffer != '\0')
       {
           while(U2STAbits.UTXBF); // wait if the buffer is full 
           U2TXREG = *buffer++;    // transfer data word to TX reg 
       }
   }
   else
   {
       while(*temp_ptr != '\0')
       {
        printf ("\n\r%c\n\r",*temp_ptr);
        while(U2STAbits.UTXBF);  // wait if the buffer is full 
           U2TXREG = *temp_ptr++;   // transfer data byte to TX reg 
       }
   }
}



void ConfigIntUART2(unsigned int config)
{
   // clear IF flags 
   IFS1bits.U2RXIF = 0;
   IFS1bits.U2TXIF = 0;

   // enable/disable interrupt 
   IEC1bits.U2RXIE = (0x0008 & config) >> 3;
   IEC1bits.U2TXIE = (0x0080 & config) >> 7;
}*/
void initU2(int BRG)
{
    U2BRG=BRG;          //Baud Rate Calc
    U2MODE = 0x8008 ;    //Enable the module with low speed mode
    U2STA = 0x0400;     //Transmit Enable
    TRISFbits.TRISF12=1;//RF12 input
    //RTS=1;            //Non-Asserted RTS
}

char putU2(char c)
{
    //while(CTS);             //Wait for Clear to send (CTS))
    while(U2STAbits.UTXBF); //Wait for Transmit buffer to fill
    U2TXREG = c;            //Transmit char
    return c;               //Echo return transmitted character
}
char getU2(void)            
{
    //RTS=0;                  //Assert a request to send (RTS))
    while(!U2STAbits.URXDA);//Wait for Receive buffer data to be available
    //RTS=1;                  //De-Assert Request to send
    return U2RXREG;         //Return Receive buffer
}
 

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    //Initialize and setup of LCD
    InitLCD();
    TRISA = 0;
    ms_delay(120);
    InitLCD();
    int line = 1;
    char n[] = "Not Connected";
    char c[] = "Connected";
    char s[] = "Data Sent";
    char r[] = "Reps: ";
    char t[] = " Time: ";
    char reps[] = "3";
    char mins[] = "10";
    char sec[] = "30";
    setCursorAtLine(line); 
    putsLCD(n);
     
    //Initialize UART for Baud rate of 115 kbps
    initU2(34);
    //Set RD6 as an input
    TRISDbits.TRISD6 = 1;
    
    while(1){ 
        //Button push to send data
        if(PORTDbits.RD6 == 0)
        {
            clearScreen();
            setCursorAtLine(line);
            putsLCD(c);
            ms_delay(25000);
            int k;
            char c;
            //Reps
            for(k = 0; k < sizeof r-1; k++)
            {
                c = r[k];
                putU2(c);            
            }
            for(k = 0; k < sizeof reps-1; k++)
            {
                c = reps[k];
                putU2(c);
            }
            //Time
            for(k = 0; k < sizeof t-1; k++)
            {
                c = t[k];
                putU2(c);
            }
            for(k = 0; k < sizeof mins-1; k++)
            {
                c = mins[k];
                putU2(c);
            }
            putU2(':');
            for(k = 0; k < sizeof sec-1; k++)
            {
                c = sec[k];
                putU2(c);
            }
            
            
            //clear 
            clearScreen();
            //Reset LCD and print "Connected" on LCD and turn on lights
            //Print "Data sent"
            setCursorAtLine(line+1);
            putsLCD(s);
            ms_delay(2500);
            PORTA = 0xff;
        }
        
        
        
        //send string to UART by each character
       /* char c;
        for(k = 0; k < sizeof p-1; k++)
        {
            c = p[k];
            putU2(c);
            ms_delay(250);
        }*/
    }
    return 1;
}

// CONFIG3
/*#pragma config WPFP = WPFP511           // Write Protection Flash Page Segment Boundary (Highest Page (same as page 85))
#pragma config WPDIS = WPDIS            // Segment Write Protection Disable bit (Segmented code protection disabled)
#pragma config WPCFG = WPCFGDIS         // Configuration Word Code Page Protection Select bit (Last page(at the top of program memory) and Flash configuration words are not protected)
#pragma config WPEND = WPENDMEM         // Segment Write Protection End Page Select bit (Write Protect from WPFP to the last page of memory)
 
// CONFIG2
#pragma config POSCMOD = XT             // Primary Oscillator Select (XT oscillator mode selected)
#pragma config IOL1WAY = ON             // IOLOCK One-Way Set Enable bit (Write RP Registers Once)
#pragma config OSCIOFNC = OFF           // Primary Oscillator Output Function (OSCO functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-safe Clock Monitor are disabled)
#pragma config FNOSC = PRI              // Oscillator Select (Primary oscillator (XT, HS, EC))
#pragma config IESO = ON                // Internal External Switch Over Mode (IESO mode (Two-speed start-up) enabled)
 
// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Standard Watchdog Timer is enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = ON              // Watchdog Timer Enable (Watchdog Timer is enabled)
#pragma config ICS = PGx1               // Comm Channel Select (Emulator functions are shared with PGEC1/PGED1)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = ON              // JTAG Port Enable (JTAG port is enabled) 0\
 */