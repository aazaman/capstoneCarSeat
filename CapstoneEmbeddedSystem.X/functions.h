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

//****************************************************************************//
//Function that allows some delay
void delay(unsigned int);

//****************************************************************************//
//Function to compare two string
//Return 1 if match, otherwise 0
unsigned char str_cmp(unsigned char*, unsigned char*, unsigned char c);

//****************************************************************************//
//Clear the main string buffer
void clearStringBuffer();