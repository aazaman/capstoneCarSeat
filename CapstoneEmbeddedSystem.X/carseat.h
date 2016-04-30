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
#include "MCU_config.h"
#include "atod_converter.h"

//****************************************************************************//
//Function to determine if the child is in the seat
unsigned char getWeightInSeat();

//****************************************************************************//****************************************************************************//
//Function to determine if the car power is on
unsigned char getCarPower();

//****************************************************************************//
//Function to determine the temperature inside the car
short getTemperature();

//****************************************************************************//
//Function to determine is temperature is higher then desired
unsigned char checkTemperature(short);

//****************************************************************************//
//Package car seat environment for UART(3 least significant bits)
unsigned char packageBitmap(unsigned char, unsigned char, unsigned char);