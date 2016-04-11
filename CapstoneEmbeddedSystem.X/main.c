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
#include "definitions.h"      //Definitions
#include "MCU_config.h"       //PIC18F87J11 configuration
#include "interrupts.h"       //Interrupt configuration
#include "atod_converter.h"   //Analog to Digital converter
#include "uart.h"             //USART configuraton
#include "bluetooth.h"        //Bluetooth configuration
#include "carseat.h"          //Carseat functionality
#include "functions.h"        //Standard methods

//Interrupt Global Variables**************************************************//
volatile unsigned char asciiValue = 0;  //Temporary hold character value
volatile unsigned char ptr = 0;         //Pointer for string buffer
volatile unsigned char string[n];       //String buffer, n -> MCUconfig.h

//main function***************************************************************//
void main(void) {
    
    //Initialization**********************************************************//
    set_Fosc();                       //Set Oscillator frequency
    set_pins();                       //Set pins
    set_adc();                        //Set anaolg to digital converter
    UART_init();                      //USART configuration
    set_interrupts();                 //Set interrupts
    set_Bluetooth();                  //Set Bluetooth configurations
    
    while(true){
        
        unsigned char connected = false;
    
        connected = checkBTLEConnection();
        if(connected){       
            
            enterBTLE_MLDP(); //Enter MLDP mode to data stream UART between MCU and peer device
            
            //Variables***************************************************************//
            unsigned char weight;    //holds if weight in seat
            unsigned char car;       //holds if car is on or off
            unsigned char temp;      //holds temperature 
            unsigned char tempFlag;  //temperature flag
            unsigned char message;   //bitmap of car seat environment
            
            
            //Wait for peer response*****************************************//
            while(!str_cmp((char *)string, (char *)"Active", 6));
            clearStringBuffer(); 
            
            //Main Loop***************************************************************//
            mainLoop{
                
                //Delay some time to insure response from peer device
                delay(2000);
                
                //Insure that we are still connected
                if(!str_cmp((char *)string, (char *)"Active", 6)){
                    //If not connected, clear buffer and break out of main loop
                    clearStringBuffer();
                    break;
                }
                clearStringBuffer();            //clear buffer
                
                //SmartSeat data processing*******************************************//
                weight = getWeightInSeat();    //check if there is weight in the seat
        
                car = getCarPower();           //check if car power is on
        
                temp = getTemperature();       //get temperature from environment
        
                tempFlag = checkTemp(temp);    //check if temperature is too high
        
                message = package(weight, car, tempFlag); //package bitmap
        
                TRISD = message;               //assign bitmap to port D
        
                //Start UART transmission*********************************************//
                UART_transmit((char *) "Bitmap is: ");       //Send bitmap prefix
                UART_transmitBitmap();                       //Send bitmap
                UART_transmit((char *)"\r");                 //Send return character
        
                UART_transmit((char *) "Temperature is: ");  //Send temperature prefix
                UART_transmit((char *) (char)temp);          //Send temperature 
                UART_transmit((char *)"\r\r");               //Send 2 return characters
            }
            rebootBTLE();   //Get out of MLDP mode and enter CMD mode
        }
    }
    return;
}