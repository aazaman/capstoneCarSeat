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
//Logical Definitions
#define true 1
#define false 0
#define INPUT 1
#define OUTPUT 0

//****************************************************************************//
//Definitions for car inputs
#define mainLoop while(1)
#define weightBit PORTHbits.RH2   
#define carPowerBit PORTFbits.RF4
#define desiredTemp 70 
#define n 32