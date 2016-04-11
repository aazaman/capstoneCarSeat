/*
 
 * File:   interrupts.c
 * Author: Jose Hernandez and Jason Edie
 * College: University of Arkansas
 * Department: College of Engineering
 *                  Computer Science
 *                  Electrical Engineering
 * Purpose: Senior Design
 
 *This header file contains all the necessary methods for interrupts during
 * received data from the RN4020 BTLE module. These interrupts will execute when
 * the receive interrupt flag is set high
 
*/

#include "MCU_config.h"
#include "definitions.h"
#include "interrupts.h"
#include "uart.h"

//****************************************************************************//
//Method to set interrupt control register
void set_interrupts(){
    INTCONbits.GIE = 1;  //Enable all global interrupts
    RCONbits.IPEN = 1;   //Enable Priority interrupt levels
    PIE1bits.RCIE = 1;   //Enable USART Receive interrupt
    IPR1bits.RCIP = 1;   //Enable USART Receive interrupt high-priority
}

//****************************************************************************//
//Method to be executed for any interrupt flag, mainly receive
void interrupt ISR(){
    extern volatile unsigned char asciiValue;
    extern volatile unsigned char ptr;
    extern volatile unsigned char string[n];

    //This interrupt is for USART communication
    if(PIR1bits.RC1IF){
        int i;
        asciiValue = RCREG1;
        if((asciiValue != 0x0A) && (ptr < n)){
            string[ptr] = asciiValue;
            ptr++;
        }
        PIR1bits.RCIF = 0;
    }
}