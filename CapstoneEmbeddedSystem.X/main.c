/*
 * File:   main.c
 * Author: Jason Eide & Jose Hernandez
 *
 * Created on March 13, 2016, 10:11 AM
 */


#include <xc.h>
#include <p18f87j11.h>

#pragma config XINST = OFF

typedef int bool;
#define true 1
#define false 0
#define weightBit PORTHbits.RH2
#define carOnOffBit PORTFbits.RF4

bool weightSensor(); 
bool carOnOffSensor();
void init();
void delay(unsigned int);
void test();

void main(void) {
    
    init();
    test();
     
    return;
}

void init() {
    
    TRISHbits.TRISH2 = 1;
    TRISFbits.TRISF4 = 1;
}

void test() {
    
    bool weightTest     = weightSensor();
    bool carOnOffTest   = carOnOffSensor();
    
    delay(200);
}

void delay(unsigned int ms) {
    
    unsigned int i;
    unsigned int j;
    for (i=0; i<ms; i++) {
        for (j=0; j<165; j++);
    }
}

// Returns 1 if weight found, 0 otherwise
bool weightSensor() {
    
    if (weightBit == 0) return true;
    return false;
}

// Returns 1 if car is on, 0 otherwise
bool carOnOffSensor() {
    
    if (carOnOffBit == 0) return false;
    return true;
}


