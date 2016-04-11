/*
 
 * File:   carseat.h
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

//****************************************************************************//
//Function to determine if the child is in the seat
//Returns 1 if child is in seated
unsigned char getWeightInSeat();

//****************************************************************************//
//Function to determine if the car is on
//Returns 0 if car is on
//Returns 1 if car is off -> using battery
unsigned char getCarPower();

//****************************************************************************//
//Function to determine the temperature inside the car
//Returns the temperature in decimal
unsigned char getTemperature();

//****************************************************************************//
//Function to determine is temperature is higher then desired
unsigned char checkTemp(unsigned char);

//****************************************************************************//
//Function to observe movement of the car seat
unsigned char accel();

//****************************************************************************//
//Package car seat environment for UART(3 least significant bits)
unsigned char package(unsigned char, unsigned char, unsigned char);