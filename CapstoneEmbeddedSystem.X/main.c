/*
 * File:   main.c
 * Author: Jose Hernandez and Jason Edie
 *
 * Created on March 17, 2016, 7:26 PM
 */

//Include Header Files--------------------------------------------------------//
#include "MCU_config.h"  //PIC18F87J11 configuration
#include "interrupts.h"  //interrupt configuration
#include "uart.h"        //USART configuraton
#include "bluetooth.h"   //Bluetooth configuration
#include "carseat.h"     //carseat functionality
#include "functions.h"

//Interrupt Global Variables--------------------------------------------------//
volatile unsigned char asciiValue = 0;
volatile unsigned char ptr = 0;
volatile unsigned char string[n];

//main function---------------------------------------------------------------//
void main(void) {
    
    //Initialization------------------------------------------------------//
    set_Fosc(); //Set Oscillator frequency
    set_pins_ExplorerBoard(); //set pins
    UART_init(); //USART configuration
    set_interrupts(); //set interrupts
    set_Bluetooth();  //set Bluetooth configurations and connect
    
    //Variables-----------------------------------------------------------//
    unsigned char weight;    //holds if weigh in seat
    unsigned char car;       //holds if car is on or off
    unsigned char temp;      //holds temperature 
    unsigned char tempFlag;  //temperature flag
    unsigned char message;   //bitmap of car seat environment
    
    //Main Loop-----------------------------------------------------------//
    mainLoop{
        
        //Begin gathering all the data for the car seat-------------------//
        weight = getS1ExplorerBoard(); //check if there is weight in the seat
        
        car = getS2ExplorerBoard(); //check if car power is on
                                    //if not battery is being used
        
        temp = getTemperature();    //get temperature from environment
        
        tempFlag = checkTemp(temp); //check if temperature is too high
        
        message = package(weight, car, tempFlag); //package bitmap
        
        //Start UART transmission------------------------------------------//
        UART_transsmit(message);
        UART_transsmit(temp);
        
        delay(100);
        PORTD = message; //display output on board(Temporary)
    }
    return;
}