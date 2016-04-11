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

//****************************************************************************//
//Initialize the RN4020
void set_Bluetooth();

//****************************************************************************//
//Check bluetooth connection status
unsigned char checkBTLEConnection();

//****************************************************************************//
//Enable MLDP mode for serial communication
void enterBTLE_MLDP();

//****************************************************************************//
//Reboot the bluetooth, saves setting and exit MLDP mode
void rebootBTLE();

//****************************************************************************//
//Enter command mode
void WAKE_SW();