/*
 
 * File:   definitions.h
 * Author: Jose Hernandez and Jason Edie
 * College: University of Arkansas
 * Department: College of Engineering
 *                  Computer Science
 *                  Electrical Engineering
 * Purpose: Senior Design
 
 *This header file contains all the helpful definitions of data types for better
 * understanding.
 * 
 
*/

//****************************************************************************//
//Functional Definitions
#define Fosc               (float)8000000
#define baudrate           (float)115200
#define baudrate_prescale  (float)4

//****************************************************************************//
//Logical Definitions
#define true               1
#define false              0
#define INPUT              1
#define OUTPUT             0
#define NULL               0x00

//****************************************************************************//
//Definitions UART
#define WAKE_SW            LATAbits.LATA4
#define WAKE_HW            LATAbits.LATA5
#define CMD_MLDP           LATBbits.LATB2
#define rxBufferSize       32

//****************************************************************************//
//Definitions ADC
#define ADC_ON             ADCON0bits.ADON
#define ADC_Channel        ADCON0bits.CHS
#define ADC_Convert        ADCON0bits.GODONE
#define Vin                (float)3.3
#define Vcar               (float)0.85
#define resolution         (float)1024

//****************************************************************************//
//Definitions for car seat inputs
#define weightPin          PORTHbits.RH2
#define HazardTemperature  90
#define WarningTemperature 75

    //Bitmap to represent environment of car seat
    #define weightBit          LATDbits.LATD0
    #define carBit             LATDbits.LATD1
    #define temp1              LATDbits.LATD2
    #define temp2              LATDbits.LATD3

//****************************************************************************//
//Definition Utility
#define mainLoop           while(1)
#define connectionLoop     while(1)