/*
 
 * File:   main.c
 * Author: Jose Hernandez and Jason Edie
 * College: University of Arkansas
 * Department: College of Engineering
 *                  Computer Science
 *                  Electrical Engineering
 * Purpose: Senior Design
 
 *This software system is embedded in a Microchip microcontroller, PIC18F87J11. The system is designed
 * to observe the environment of a car seat to ensure the the car seat is in a safe state for a child.
 * The system uses a 3-bit bitmap in the for of tcw to represent the state of the car set, where
 * t->temperature flag
 * c->batter power
 * w->weight in seat
 * Temperature will be processed by the internal 10-bit analog to digital converter. The t bit for the
 * bit map is a flag bit, which will indicate if the temperature is above a desired level.
 * 
 * The c bit flag represents if the car is running on the back up battery or not. If the car is running
 * this bit will be set low and vice versa
 * 
 * The w bit flag will represent if their is weight in the car seat itself
 * 
 * This embedded system will monitor the stimulus of the car seat and send the bitmap and temperature
 * through UART communication to an RN4020 Bluetooth Low Energy module. This information will then be
 * sent the care givers device to notify the care giver the sate in which the child is in with respect
 * to the car seat.
 
*/

//Include Header Files********************************************************//
#include "MCU_config.h"                  //PIC18F87J11 configuration
#include "interrupts.h"                  //Interrupt configuration
#include "atod_converter.h"              //Analog to Digital converter
#include "uart.h"                        //USART configuraton
#include "bluetooth.h"                   //Bluetooth configuration
#include "carseat.h"                     //Carseat functionality
#include "functions.h"                   //Utility functions
#include "timers.h"                      //Timer functions

//Interrupt Global Variables**************************************************//
volatile unsigned char asciiValue = 0;         //Temporary hold character value
volatile unsigned char ptr = 0;                //Pointer for string buffer
volatile unsigned char rxBuffer[rxBufferSize]; //String buffer to receive
volatile unsigned char message[rxBufferSize];  //Hold BTLE message

//Main function***************************************************************//
void main(void) {
    
    //Initialization**********************************************************//
    clearStringBuffer();
    set_Fosc();                          //Set Oscillator frequency
    set_pins();                          //Set pins
    ADC_set();                           //Set analog to digital converter
    UART_init();                         //Set USART configuration
    set_interrupts();                    //Set interrupts
    set_timer0();                        //Set timer
    BTLE_set();                          //Set Bluetooth configurations
    
    //Variables***************************************************************//
    unsigned char weight      = 0;       //holds weight flag
    unsigned char carPower    = 0;       //holds car power flag
    short         temperature = 0;       //holds temperature value
    unsigned char tempFlag    = 0;       //temperature flag
    unsigned char bitmap      = 0;       //Bitmap for car seat environment
    
    //Connection Loop*********************************************************//
    connectionLoop{
        while(str_cmp((char*) message, (char*) "Connection End", 14));
        //Delay some time between each data stream
        delay_sec(1);

        //SmartSeat data processing*******************************************//
        //check if there is weight in the seat
        weight = getWeightInSeat();
        
        //check if car power is on
        carPower = getCarPower();
        
        //get temperature from environment
        temperature = getTemperature();
        
        //check if temperature is too high
        tempFlag = checkTemperature(temperature);
        
        //package bitmap
        bitmap = packageBitmap(weight, carPower, tempFlag);   

        //send status of smart seat
        UART_SmartSeatStatus(bitmap, temperature);
    }
    return;
}