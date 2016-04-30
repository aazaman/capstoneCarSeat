/*
 
 * File:   bluetooth.h
 * Author: Jose Hernandez and Jason Edie
 * College: University of Arkansas
 * Department: College of Engineering
 *                  Computer Science
 *                  Electrical Engineering
 * Purpose: Senior Design
 
 *This header file contains all the necessary methods to set the main
 * configurations of the PIC18F87J11. These setting will use the internal 
 * oscillator in the microcontroller. Also included contains 
 
*/

#include <xc.h>
#include <pic18f87j11.h>
#include "definitions.h"

//****************************************************************************//
// CONFIG1L
#pragma config DEBUG = OFF      //Enbale programer pins
#pragma config WDTEN = OFF      // Watchdog Timer Enable bit (WDT disabled (control is placed on SWDTEN bit))
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable bit (Reset on stack overflow/underflow disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

//****************************************************************************//
// CONFIG1H
#pragma config CP0 = OFF         // Code Protection bit (Program memory is code-protected)

//****************************************************************************//
// CONFIG2L
#pragma config FOSC = INTOSC    // Oscillator Selection bits (Internal oscillator)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)
#pragma config IESO = ON        // Two-Speed Start-up (Internal/External Oscillator Switchover) Control bit (Two-Speed Start-up enabled)

//****************************************************************************//
// CONFIG2H
#pragma config WDTPS = 32768    // Watchdog Timer Postscaler Select bits (1:32768)

//****************************************************************************//
// CONFIG3L
#pragma config EASHFT = ON      // External Address Bus Shift Enable bit (Address shifting enabled, address on external bus is offset to start at 000000h)
#pragma config MODE = MM        // External Memory Bus Configuration bits (Microcontroller mode - External bus disabled)
#pragma config BW = 16          // Data Bus Width Select bit (16-bit external bus mode)
#pragma config WAIT = OFF       // External Bus Wait Enable bit (Wait states on the external bus are disabled)

//****************************************************************************//
// CONFIG3H
#pragma config CCP2MX = DEFAULT // ECCP2 MUX bit (ECCP2/P2A is multiplexed with RC1)
#pragma config ECCPMX = DEFAULT // ECCPx MUX bit (ECCP1 outputs (P1B/P1C) are multiplexed with RE6 and RE5; ECCP3 outputs (P3B/P3C) are multiplexed with RE4 and RE3)
#pragma config PMPMX = DEFAULT  // PMP Pin Multiplex bit (PMP port pins connected to EMB (PORTD and PORTE))
#pragma config MSSPMSK = MSK7   // MSSP Address Masking Mode Select bit (7-Bit Address Masking mode enable)

//****************************************************************************//
//Method to set oscillator frequency
void set_Fosc();

//****************************************************************************//
//Function to set input pins for car seat environment
void set_input_pins();

//****************************************************************************//
//Function to set output pins for car seat environment 
void set_output_pins();

//****************************************************************************//
//Helper function to set pins
void set_pins();