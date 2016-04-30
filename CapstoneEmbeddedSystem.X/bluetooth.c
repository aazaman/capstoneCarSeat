/*
 
 * File:   bluetooth.c
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

#include "bluetooth.h"

//****************************************************************************//
//Send commands through UART to configure RN4020
void BTLE_set(){
    clearStringBuffer();
    
    CMD_MLDP = 0;
    delay_1s();
    WAKE_SW = 1;
    delay_1s();
    
    UART_transmit((char *)"SN,SmartSeat\r");
    delay_1s();
    clearStringBuffer();

    UART_transmit((char *)"SR,36004800\r");
    delay_1s();
    clearStringBuffer();

    BTLE_reboot();

    WAKE_SW = 1;
    delay_1s();
    CMD_MLDP = 1;
    delay_1s();
}

//****************************************************************************//
//Check connection status of the RN4020
unsigned char BTLE_checkConnection(){
    clearStringBuffer();
    CMD_MLDP = 0;
    delay_1s();
    UART_transmit((char *)"Q\r");
    delay_1s();
    if(!str_cmp((char *)message, (char *)"No Connection", 13)){
        CMD_MLDP = 1;
        delay_1s();
        return 1;
    }
    return 0;
}

//****************************************************************************//
//Reboot the RN4020 to save changes and exit MLDP
void BTLE_reboot(){
    UART_transmit((char *)"R,1\r");           //Reboot to set changes
    delay_1s();
}