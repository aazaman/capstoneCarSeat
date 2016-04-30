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

#include "atod_converter.h"

//****************************************************************************//
//Method to set the control registers of the Analog to digital converter
void ADC_set(){
    //Set ADCON Configuration bits
    WDTCONbits.ADSHR = 0;  //Share address SFR for ADCON0 & ADCON1(p. 340)
    ADCON1bits.ADFM  = 1;  //Save ADC result as right justified 
    ADCON1bits.ACQT  = 2;  //Acquisition time is 4 TAD
    ADCON1bits.ADCS  = 4;  // Fosc/4
}

//****************************************************************************//
//Get the temperature from the a to d converter
short ADC_getTemperature(){
    //The board uses an NTC thermistor, where resistance decreases as temperature
    //increase. By consequence, the voltage also drop with the drop of resistance.
    //The resistance vs temperature is close to linear between 50-90 degrees. This
    //is a desirable range for the purpose of this system.
    //the formula derived is...
    //temperate = m * (step number) + b for temperature vs. step number
    //where the step number is determined by the ADC, Vdd and Vin
    
    
    short L_byte = 0;              //Grab ADRESL from A/D converter result
    short H_byte = 0;              //Grab ADRESH from A/D converter result
    float b = 81.8193832599119;    //b constant
    float m = -0.039647577092511;  //Slope of linear line between 50 -90 degrees
    float stepNumber = 0;          //ADC step number        
    short result = 0;              //Temporary hold temperature
    
    ADC_ON = true;                 //Turn on ADC
    ADC_Channel = 3;               //Convert analog signal on channel 3
    ADC_Convert = true;            //Start ADC conversion
    while(ADC_Convert);            //Hold here until ADC conversion is done
    ADC_ON = false;                //Turn off ADC
    
    L_byte = ADRESL;               //Get low byte result
    H_byte = ADRESH;               //Get high byte result
    H_byte = H_byte << 8;          //Shift 8 LSB to 8 MSB
    
    stepNumber = (H_byte | L_byte);//OR bits together to get step number
    
    //calculate the temperature
    result = (short)(m*stepNumber + b);       
    
    return result;
}

//****************************************************************************//
//Determine if the car power is on, this is set on analog pin so need to do ADC
unsigned char ADC_getCarPower(){
    //This function will determine if the voltage from the car power is strong
    //enough. For easier understanding, we convert the step number back to the
    //reference voltage.
    
    short L_byte = 0;               //Grab ADRESL from A/D converter result
    short H_byte = 0;               //Grab ADRESH from A/D converter result
    short stepNumber = 0;           //ADC step number
    float Vref = 0;                 //Voltage reference is car power voltage
    
    ADC_ON = true;                  //Turn on ADC
    ADC_Channel = 9;                //Convert analog signal on channel 3
    ADC_Convert = true;             //Start ADC conversion
    while(ADC_Convert);             //Hold here until ADC conversion is done
    ADC_ON = false;                 //Turn off ADC
    
    L_byte = ADRESL;                //Get low byte result
    H_byte = ADRESH;                //Get high byte result
    
    H_byte = H_byte<<8;             //Shift 8 LSB to 8 MSB
    
    stepNumber = (H_byte | L_byte); //OR bits together to get step number  

    // Vin = 3.3V, resolution = 2^10 || 1024
    Vref = (stepNumber * Vin) / resolution; //calculate Vref
    
    //Check if voltage is high enough, Vcar = .85V
    if(Vref >= Vcar)
        return true;
    return false;
}