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

#include "MCU_config.h"
#include "definitions.h"
#include "bluetooth.h"
#include "uart.h"
#include "functions.h"

extern volatile unsigned char ptr;            //buffer pointer
extern volatile unsigned char string[n];      //buffer string

//****************************************************************************//
//Send commands through UART to configure RN4020
void set_Bluetooth(){
    
    unsigned char reboot = 0; //if reboot needs to take place
    unsigned char ready = 1;
    
    //Enter Command Mode
    WAKE_SW();
    delay(100);
    clearStringBuffer();
    
    do{
        //Check to see if name is set to desired name
        UART_transmit((char *)"GN\r"); //get name
        delay(100);
        if(!str_cmp((char *)string, (char *)"SmartSeat", 9)){
            UART_transmit((char *)"SN,SmartSeat\r");  //Friendly Name
            delay(100);
            reboot = 1;
        }
        clearStringBuffer();
    
        UART_transmit((char *)"GR\r");
        delay(100);
        if(!str_cmp((char *)string, (char *)"32004000\r", 8)){
            UART_transmit((char *)"SR,32004000\r");   //Auto Advertise, Enable MLDP,
            delay(100);
            reboot = 1;
        }
        clearStringBuffer();
    
        if(reboot)
            rebootBTLE();
        
        UART_transmit((char *)"GN\r");
        delay(100);
        if(!str_cmp((char *)string, (char *)"SmartSeat", 9))
            ready = 0;
        clearStringBuffer();
        
        UART_transmit((char *)"GR\r");
        delay(100);
        if(!str_cmp((char *)string, (char *)"32004000\r", 8))
            ready = 0;
        clearStringBuffer();
        
    }while(!ready);
}

//****************************************************************************//
//Check connection status of the RN4020
unsigned char checkBTLEConnection(){
    
    unsigned char connected = 0;
    
    UART_transmit((char *)"Q\r");
    delay(100);
    connected = !str_cmp((char *)string, (char *)"No Connection", 13);
    clearStringBuffer();
    return connected;
}

//****************************************************************************//
//Enter MLDP mode for UART communication between MCU and peer device
void enterBTLE_MLDP(){
    UART_transmit((char *)"I\r");             //Bond the peer device
    delay(100);
    clearStringBuffer();
}

//****************************************************************************//
//Reboot the RN4020 to save changes and exit MLDP
void rebootBTLE(){
    UART_transmit((char *)"R,1\r");           //Reboot to set changes
    delay(100);
    clearStringBuffer();
}

//****************************************************************************//
//Enter command mode on the RN4020
void WAKE_SW(){PORTAbits.RA4 = 1;}           //Set bluetooth to command mode