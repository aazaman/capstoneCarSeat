/*
 
 * File:   atod_converter.h
 * Author: Jose Hernandez and Jason Edie
 * College: University of Arkansas
 * Department: College of Engineering
 *                  Computer Science
 *                  Electrical Engineering
 * Purpose: Senior Design
 
 * Created on March 17, 2016, 7:26 PM
 * Last Update on April 6, 2016, 4:00 PM
 
 *This header file contains the necessary functionality to configure the
 * 10-but analog to digital convert. The converter will be used to convert the
 * analog voltage from the thermistor and interpret its digital meaning.
 
*/

#include "MCU_config.h"

//****************************************************************************//
//Function to set Analog & Digital pins
//To set A/D configuration
void ADC_set();

//****************************************************************************//
//get the temperature from the a to d converter
short ADC_getTemperature();

//****************************************************************************//
//Determine if the car power is on, this is set on analog pin so need to do ADC
unsigned char ADC_getCarPower();