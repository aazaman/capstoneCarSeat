/*
 
 * File:   interrupts.h
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

//****************************************************************************//
//Method to set interrupt bits for the PIC18F87J11
void set_interrupts();

//****************************************************************************//
//Method for receive interrupt service routine 
void interrupt ISR();