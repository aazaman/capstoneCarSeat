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


#include "interrupts.h"

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

    //This interrupt is for USART communication
    //Incoming Byte
    if(PIR1bits.RC1IF){
        asciiValue = RCREG1; //Temporary save Byte
        
        //Check if end of string and that pointer does not exceed length of receive buffer
        //0x0A = "\n" and 0x0D = "\r"
        if((asciiValue != 0x0A && asciiValue !=0x0D) && (ptr < rxBufferSize)){
            if(asciiValue < 0x7F){
                rxBuffer[ptr] = asciiValue;   //save byte to buffer
                ptr++;  //increment pointer to save next byte
            }
        }
        
        //We have reached end of string
        else{
            //copy buffer string to message string
            str_copy((char *) rxBuffer, (char *) message, ptr);
            clearStringBuffer();
            ptr = 0;
        }
        PIR1bits.RCIF = 0;  //Ready for next byte 
    }
}