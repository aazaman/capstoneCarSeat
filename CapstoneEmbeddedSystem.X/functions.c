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
#include "functions.h"


//****************************************************************************//
//Method to compare two strings, uses hard coded length
unsigned char str_cmp(unsigned char* s1, unsigned char* s2, unsigned char c){
    unsigned char i = 0;
    while(i < c){          //while s1 and s2 are still readable
        if(*s1 != *s2)     //check is one character doesn't match
            return false;  //if so, terminate 
        s1++;              //otherwise increment both
        s2++;
        i++;
    }
    return true;           //all characters pass
}

//****************************************************************************//
//Method to copy a string
//s1 is string to be copied
void str_copy(unsigned char* s1, unsigned char* s2, unsigned char c){
    unsigned char i = 0;
    while(i < c){
        *s2 = *s1;
        s1++;
        s2++;
        i++;
    }
}

//****************************************************************************//
//Method to clear the receive string buffer
void clearStringBuffer(){
    unsigned char i;
    
    for(i = 0; i < rxBufferSize; i++)
        rxBuffer[i] = 0x00;
}

//****************************************************************************//
//Method to convert integer value to array of characters
void num_to_char(unsigned char* s, int x){
    
    int temp = x;       //temporary copy of x
    int count = 0;     //hold number of digits in x
    
    //Divide by 10 and increment count until temp = 0;
    while(temp != 0){
        temp/=10;
        count++;
    }
    //Save end of string character
    s[count--] = '\r';
    //Start working backwards
    while(count >= 0){
        //Divide x/10 and save remainder/least significant digit to string
        //48 is ascii offset
        s[count--] = (char)('0' + (char)(x%10));
        //get rid of least significant digit
        x/=10;
    }
}