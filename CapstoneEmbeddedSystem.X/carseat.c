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

#include "carseat.h"

//****************************************************************************//
//Function to determine if the child is in the seat
unsigned char getWeightInSeat(){
    //Return true if weight detected
    //Return false if no weight detected
    if(weightPin == 1)
        return true;
    return false;
}

//****************************************************************************//
//Function to determine if the car power is on
unsigned char getCarPower(){
    //Return true if car power is on
    //Return false if car power is off -> backup battery being used
    return ADC_getCarPower();
}

//****************************************************************************//
//Function to determine the temperature inside the car
short getTemperature(){
    //Returns the temperature in decimal format
    return ADC_getTemperature();
}

//****************************************************************************//
//Method to verify if the desired temperature is in range
unsigned char checkTemperature(short t){
    unsigned char c = 0;
   
    if(t >= desiredTempWarning)
        c = 1;
    if(t >= desiredTempHigh)
        c = 2;
    return c;
}

//****************************************************************************//
//Function to package the environment of the car seat
unsigned char packageBitmap(unsigned char w, unsigned char c, unsigned char t){
    unsigned char result;
    //0b00000 t1t2cw
    //t = temperature above 80 degrees
    //c = car on or off
    //w = weight yes or no
    c = c<<1;
    t = t<<2;
    
    result = t | c | w;
   
    return result;
}