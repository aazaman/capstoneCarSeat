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
void set_timer0();

//****************************************************************************//
//delay for 1 millisecond
void delay_1ms();

//****************************************************************************//
//delay for 100 milliseconds
void delay_100ms();

//****************************************************************************//
//delay for 1 second
void delay_1s();

//****************************************************************************//
//delay for n seconds
void delay_sec(unsigned char i);