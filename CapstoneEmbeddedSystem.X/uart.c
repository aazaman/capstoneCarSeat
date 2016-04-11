/*
 
 * File:   uart.c
 * Author: Jose Hernandez and Jason Edie
 * College: University of Arkansas
 * Department: College of Engineering
 *                  Computer Science
 *                  Electrical Engineering
 * Purpose: Senior Design
 
 *This header file contains all the necessary methods to allow UART serial
 * communication between the PIC18F87J11 and the RN40 BTLE module. The following
 * methods include initialization of both the receive and transmit control
 * register and baud rate configuration register. 
 
*/

#include "MCU_config.h"
#include "uart.h"

//****************************************************************************//
//Method to initialize UART control registers for asynchruonus communication
void UART_init(){
    
    set_UARTtx();
    set_UARTrx();
    set_UARTBaudConfig();
    set_UARTBaudRate();
}

//****************************************************************************//
//Set transmit control registers
void set_UARTtx(){
    TXSTA1bits.CSRC  = 0;  //Don't care
    TXSTA1bits.TX9   = 0;  //Use 8-bit data communication
    TXSTA1bits.TXEN  = 1;  //Transmit is enabled;
    TXSTA1bits.SYNC  = 0;  //Asynchronous mode
    TXSTA1bits.SENDB = 0;  //Sync Break transmission has completed 
    TXSTA1bits.BRGH  = 1;  //High Baud Rate
}

//****************************************************************************//
//Set receive control registers
void set_UARTrx(){
    RCSTA1bits.SPEN  = 1;  //Serial Port is enabled
    RCSTA1bits.RX9   = 0;  //Receive 9 bits
    RCSTA1bits.SREN  = 1;  //
    RCSTA1bits.CREN  = 1;  //Continuous Receive Enabled
    RCSTA1bits.ADDEN = 0;  //Address detection is disabled
    SSP1CON2bits.RCEN = 1;
}

//****************************************************************************//
//Set baud rate control register
void set_UARTBaudConfig(){
    BAUDCON1bits.ABDOVF = 0;  //No Auto-Baud Detection
    BAUDCON1bits.RXDTP  = 0;  //Receive data is not inverted
    BAUDCON1bits.TXCKP  = 0;  //Idle state for transmit is a high level
    BAUDCON1bits.BRG16  = 1;  //8bit Baud Rate Generator
    BAUDCON1bits.WUE    = 0;  //Wake up Enable is off, RXx pin is not monitored
}

//****************************************************************************//
//Set Baud Rate 
void set_UARTBaudRate(){
    //Seconds per bit = 1/baudrate
    //SPBRG value is only a number that references the baudrate
    //115200 baudrate to talk to RN420 BTLE
    SPBRGH1 = 0;
    SPBRG1 = 16;
}

//****************************************************************************//
//Function to transmit bitmap in ASCII on UART serial port
void UART_transmitBitmap(){
    
    while(TXSTAbits.TRMT == 0);
    if(TRISDbits.RD2)
        TXREG = 0x31;
    else
        TXREG = 0x30;
    while(TXSTAbits.TRMT == 0);
    if(TRISDbits.RD1)
        TXREG = 0x31;
    else
        TXREG = 0x30;
    while(TXSTAbits.TRMT == 0);
    if(TRISDbits.RD0)
        TXREG = 0x31;
    else
        TXREG = 0x30;
    while(TXSTAbits.TRMT == 0);
    
    //TXREG = 0x0A;
    while(TXSTAbits.TRMT == 0);
}

//****************************************************************************//
//Function to transmit string on UART serial port
void UART_transmit(unsigned char *s){
    while(*s){
        while(TXSTAbits.TRMT == 0);
        TXREG = *s;
        s++;
    }
    while(TXSTAbits.TRMT == 0);
}