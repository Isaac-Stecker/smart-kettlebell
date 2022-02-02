/*
 * Funcs.c
 * 
 * Implementation file for functions used in the Smart Kettlebell's main file
 */

#include <xc.h>

// Creates an N millisecond delay when T1CON = 0x8030
void ms_delay(int N){
    TMR1 = 0;
    while(TMR1 < N*(125/2));
}

// Creates a N microsecond delay when T3CON = 0x8000
void us_delay(int N){
    TMR3 = 0;
    while(TMR3 < N*16);
}
