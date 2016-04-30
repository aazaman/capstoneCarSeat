/*
 
 * File:   uart.h
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
#include "functions.h"
#include "timers.h"

//****************************************************************************//
//Initialize UART serial communication control registers
void UART_init();

//****************************************************************************//
//Initialize UART transmit control registers
void set_UARTtx();

//****************************************************************************//
//Initialize UART receive control registers
void set_UARTrx();

//****************************************************************************//
//Initialize UART Baud Rate configuration
void set_UARTBaudConfig();

//****************************************************************************//
//Set the UART Baud Rate
void set_UARTBaudRate();

//****************************************************************************//
//Transmit the bitmap on the UART transmitting port
void UART_SmartSeatStatus(unsigned char);

//****************************************************************************//
//Transmit the temperature through the UART in ASCII
void UART_Temperature(int);

//****************************************************************************//
//Transmit ASCII strings on the UART transmitting port
void UART_transmit(unsigned char*);