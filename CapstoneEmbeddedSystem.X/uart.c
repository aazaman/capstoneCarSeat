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

#include "uart.h"

//****************************************************************************//
//Method to initialize UART control registers for asynchronus communication
void UART_init(){
    
    set_UARTtx();         //Sets transmit control registers
    set_UARTrx();         //Sets receive control registers
    set_UARTBaudConfig(); //Sets baud rate control registers
    set_UARTBaudRate();   //Set actual baud rate
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
    RCSTA1bits.SPEN   = 1;  //Serial Port is enabled
    RCSTA1bits.RX9    = 0;  //Receive 9 bits
    RCSTA1bits.SREN   = 1;  //Single receive enable bit
    RCSTA1bits.CREN   = 1;  //Continuous Receive Enabled
    RCSTA1bits.ADDEN  = 0;  //Address detection is disabled
    SSP1CON2bits.RCEN = 1;  //Receive enable bit
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
    //Sets the baud rate to talk to RN4020
    //baudrate = 115200
    //Fosc = 8MHz
    SPBRG1 = (char)((Fosc/(baudrate * baudrate_prescale)) - 1.0);
}

//****************************************************************************//
//Function to transmit bitmap in ASCII on UART serial port
void UART_SmartSeatStatus(unsigned char bitmap, short temperature){
    LATD = bitmap;
    unsigned char s[6] = {83,48, 48, 48, 48, NULL};
    if(weightBit) s[4] = 49;
    if(carBit)    s[3] = 49;
    if(temp1)     s[2] = 49;
    if(temp2)     s[1] = 49;
    
    UART_transmit((char *) s);
    
    UART_transmit((char *) "\n");
    
    UART_Temperature(temperature);
    
    if(!temp1 && temp2)
        UART_transmit((char *) "Hazard: High Temperatures\r");
    else if(temp1 && ! temp2)
        UART_transmit((char *) "Warning: Reaching unsafe high temperatures\r");
    else
        UART_transmit((char *) "Safe temperature\r");
    if(carBit)
        UART_transmit((char *) "Car Power\r");
    else
        UART_transmit((char *) "No Car Power\r");
    if(weightBit)
        UART_transmit((char *) "Child is in seat\r");
    else
        UART_transmit((char *) "No Child\r");
    
    UART_transmit((char *) "\n\n");
}

//Method to send temperature on UART as string
void UART_Temperature(short t){
    unsigned char s[rxBufferSize];
    num_to_char((char *)s,t);
    
    UART_transmit((char *) "Temperature is: ");
    UART_transmit((char *) s);
    
}

//****************************************************************************//
//Function to transmit string on UART serial port
void UART_transmit(unsigned char *s){
    while(*s){
        delay_100ms();
        while(TXSTAbits.TRMT == 0);
        TXREG = *s;
        s++;
    }
    while(TXSTAbits.TRMT == 0);
}