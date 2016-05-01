/*
 
 * File:   functions.h
 * Author: Jose Hernandez and Jason Edie
 * College: University of Arkansas
 * Department: College of Engineering
 *                  Computer Science
 *                  Electrical Engineering
 * Purpose: Senior Design
 
 *THis header contains necessary utility or helper functions to all data
 * processing which include a timer delay, string comparison between two strings
 * and clear the buffer for receive responses  
 
*/

#include "MCU_config.h"

extern volatile unsigned char rxBuffer[rxBufferSize];

//****************************************************************************//
//Function to compare two string
//Return 1 if match, otherwise 0
unsigned char str_cmp(unsigned char*, unsigned char*, unsigned char);

//****************************************************************************//
//Method to copy a string
void str_copy(unsigned char*, unsigned char*, unsigned char);

//****************************************************************************//
//Clear the main string buffer
void clearStringBuffer();

//****************************************************************************//
//Convert integer to string
void num_to_char(unsigned char*, short);