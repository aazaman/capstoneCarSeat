/*
 
 * File:   atod_converter.h
 * Author: Jose Hernandez and Jason Edie
 * College: University of Arkansas
 * Department: College of Engineering
 *                  Computer Science
 *                  Electrical Engineering
 * Purpose: Senior Design
 
 * Created on March 17, 2016, 7:26 PM
 * Last Update on April 6, 2016, 4:00 PM
 
 *This header file contains the necessary functionality to configure the
 * 10-but analog to digital convert. The converter will be used to convert the
 * analog voltage from the thermistor and interpret its digital meaning.
 
*/

#include "MCU_config.h"

//****************************************************************************//
//set internal timers using internal oscillator
void set_timer0(){
    T0CONbits.TMR0ON = 0;
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS   = 0;
    T0CONbits.T0SE   = 0;
    T0CONbits.PSA    = 0;
}

//****************************************************************************//
//delay for 1 millisecond
void delay_1ms(){
    T0CONbits.T0PS   = 1;
    TMR0H = 0xFE;
    TMR0L = 0x0D;
    T0CONbits.TMR0ON = 1;
    while(INTCONbits.TMR0IF == 0);
    T0CONbits.TMR0ON = 0;
    INTCONbits.TMR0IF = 0;
 
}

//****************************************************************************//
//delay for 100 milliseconds
void delay_100ms(){
    T0CONbits.T0PS   = 1;
    TMR0H = 0x3C;
    TMR0L = 0xB1;
    T0CONbits.TMR0ON = 1;
    while(INTCONbits.TMR0IF == 0);
    T0CONbits.TMR0ON = 0;
    INTCONbits.TMR0IF = 0;
 
}

//****************************************************************************//
//delay for 1 second
void delay_1s(){
    T0CONbits.T0PS   = 4;
    TMR0H = 0x0B;
    TMR0L = 0xDD;
    T0CONbits.TMR0ON = 1;
    while(INTCONbits.TMR0IF == 0);
    T0CONbits.TMR0ON = 0;
    INTCONbits.TMR0IF = 0;
 
}

//****************************************************************************//
//delay for n seconds
void delay_sec(unsigned char i){
    while(i > 0){
        delay_1s();
        i--;
    }
}