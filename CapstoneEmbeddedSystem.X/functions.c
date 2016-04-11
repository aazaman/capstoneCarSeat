/*
 
 * File:   functions.c
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
#include "definitions.h"
#include "functions.h"

//****************************************************************************//
//Simple delay function
void delay(unsigned int x){
    unsigned int i;
    unsigned int j;
    for(i = 0; i < x; i++){
        for(j = 0; j < 165; j++){}
    }
}

//****************************************************************************//
//Method to compare two strings, uses hard coded length
unsigned char str_cmp(unsigned char* s1, unsigned char* s2, unsigned char c){
    unsigned char i = 0;
    while(i < c){       //while s1 and s2 are still readable
        if(*s1 != *s2)     //check is one character doesnt match
            return false;  //if so, terminate 
        s1++;              //otherwise increment both
        s2++;
        i++;
    }
    return true;           //all characters pass
}

//****************************************************************************//
//Method to clear the string receive string buffer
void clearStringBuffer(){
    extern volatile unsigned char ptr;
    extern volatile unsigned char string[n];
    unsigned char i;
    
    for(i = 0; i < n; i++){
        string[i] = 0x00;
    }
    ptr = 0;
}