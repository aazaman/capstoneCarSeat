/*
 
 * File:   atod_converter.c
 * Author: Jose Hernandez and Jason Edie
 * College: University of Arkansas
 * Department: College of Engineering
 *                  Computer Science
 *                  Electrical Engineering
 * Purpose: Senior Design
 
 *This header file contains the necessary functionality to configure the
 * 10-but analog to digital convert. The converter will be used to convert the
 * analog voltage from the thermistor and interpret its digital meaning
 
*/

//Function to set Analog & Digital pins
//To set A/D configuration

//Analog to Digital Converter Configuration
#include "MCU_config.h"

//****************************************************************************//
//Method to set the control registers of the Analog to digital converter
void set_adc(){
    //Set ANCON Configuration bits
    WDTCONbits.ADSHR = 1; //Share address SFR for ANCON0 & ANCON1(p. 340)
    ANCON1 = 0xFF; //AN15-AN8 are all digital I/O (p. 311)
    
    ANCON0 = 0xC7; //AN7:AN6, AN2-AN0 are digital, AN3 and AN4 is analog(p.311)
    
    //Set ADCON Configuration bits
    WDTCONbits.ADSHR = 0; //Share address SFR for ADCON0 & ADCON1(p. 340)
    ADCON0 = 0x0D; //ADCON0 = (0)(0)(0011)(0)(1) (p.309)
                   //(Vss)(Vdd)(CH3)(G0)(ADON)
    
    ADCON1 = 0x94; //ADCON1 = (1)(0)(010)(100) (p.310)
                   //(Right Just.)(ADCAL)(20TAD)(Fosc/4)
}

//****************************************************************************//
//Get the temperature from the a to d converter
unsigned char temp_adc(){
    unsigned char L_byte; //grab ADRESL from A/D converter result
    unsigned char H_byte; //grab ADRESH from A/D converter result
    unsigned char result; // temporary hold temperature
    
    
    ADCON0 |= 0x02; //ADCON.GODONE = 1;
    while(ADCON0bits.GO == 1); //Hold here until A/D conversion is done
    
    L_byte = ADRESL; //get low byte result
    H_byte = ADRESH; //get high byte result
    L_byte = L_byte >> 1;//shift 6 MSB to 6 LSB
    H_byte = H_byte << 7;//shift 2 LSB to 2 MSB
    
    result = (H_byte | L_byte)/3; //OR bits together
    
    return result;
}