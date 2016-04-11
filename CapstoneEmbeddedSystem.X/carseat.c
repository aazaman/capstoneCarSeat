/*
 
 * File:   carseat.c
 * Author: Jose Hernandez and Jason Edie
 * College: University of Arkansas
 * Department: College of Engineering
 *                  Computer Science
 *                  Electrical Engineering
 * Purpose: Senior Design
 
 *This header file contains all the necessary methods to obtain the environment
 * status of the SmartSeat. These methods include...
 * 1.) Checking if there is weight in the seat
 * 2.) Check if power is coming from car
 * 3.) Get temperature
 
*/

#include "MCU_config.h"
#include "carseat.h"
#include "definitions.h"
#include "atod_converter.h"

//****************************************************************************//
//Function to determine if the child is in the seat
//Returns 1 if child is seated
unsigned char getWeightInSeat(){
    //weighBit 0 = no voltage due to weight in seat
    if(weightBit) return 0;
    return 1;
}

//****************************************************************************//
//Function to determine if the car is on
unsigned char getCarPower(){
    //Returns 1 if car is on
    //Returns 0 if car is off -> using battery
    if(carPowerBit) return 0;
    return 1;
}

//****************************************************************************//
//Function to determine the temperature inside the car
//Returns the temperature in decimal
unsigned char getTemperature(){
    unsigned char temp;
    temp = temp_adc();
    return temp;
}

//****************************************************************************//
unsigned char checkTemp(unsigned char t){
    if(t >= desiredTemp)
        return 1;
    return 0;
}

//****************************************************************************//
//Function to package the environment of the car seat
unsigned char package(unsigned char w, unsigned char c, unsigned char t){
    //0b00000tcw
    //t = temperature above 80 degrees
    //c = car on or off
    //w = weight yes or no
    c = c<<1;
    t = t<<2;
   
    return t | c | w;
}