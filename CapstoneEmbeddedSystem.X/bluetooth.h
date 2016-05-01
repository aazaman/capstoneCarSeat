/*
 
 * File:   bluetooth.h
 * Author: Jose Hernandez and Jason Edie
 * College: University of Arkansas
 * Department: College of Engineering
 *                  Computer Science
 *                  Electrical Engineering
 * Purpose: Senior Design
 
 *This header file contains all the necessary methods to all the configuration of
    the RN4020 Bluetooth Low Energy module as well as bonding the peer device
    and enabling the MLDP mode for UART serial communication between the
    PIC18f87J11 microcontroller and the peer device
 
*/
#include "MCU_config.h"
#include "functions.h"
#include "timers.h"
#include "uart.h"


extern volatile unsigned char message[rxBufferSize];

//****************************************************************************//
//Initialize the RN4020
void BTLE_set();

//****************************************************************************//
//Check bluetooth connection status during CMD
unsigned char BTLE_checkConnection();

//****************************************************************************//
//Reboot the bluetooth, saves setting and exit MLDP mode
void BTLE_reboot();

//****************************************************************************//
//Enter CMD (command) mode for RN4020
void BTLE_enterCMD();

//****************************************************************************//
//Enter MLDP mode for UART transmission between peer and MCU
void BTLE_enterMLDP();

//****************************************************************************//
//Wake the RN4020 bluetooth up
void BTLE_Wake();
