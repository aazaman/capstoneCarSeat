/*
 
 * File:   bluetooth.c
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

#include "MCU_config.h"
#include "definitions.h"

//****************************************************************************//
//Sets the Oscillator frequency for the MCU
void set_Fosc(){
    OSCCON = 0xFC; //INTSOC frequency 8MHz
}

//****************************************************************************//
//Input pins for receiving data from environment
void set_input_pins(){
    TRISHbits.TRISH2 = INPUT; //Input pin for weight(digital)
    TRISFbits.TRISF4 = INPUT; //Input pin for car on or off(digital)
    TRISAbits.TRISA3 = INPUT; //Input pin for temp voltage(analog)
    TRISCbits.TRISC7 = INPUT; //Input from UART bluetooth receive
    
}

//****************************************************************************//
//Output pins for sending data
void set_output_pins(){
    TRISCbits.TRISC6 = OUTPUT; //Output for UART bluetooth transmit
    TRISAbits.TRISA4 = OUTPUT; //Bluetooth WAKE_SW
    TRISAbits.TRISA5 = OUTPUT; //Bluetooth WAKE_HW
}

//****************************************************************************//
//Helper function to set input/output/AtoD converter pins
void set_pins(){
    set_input_pins();
    set_output_pins();
}