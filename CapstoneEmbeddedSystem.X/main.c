/*
 * File:   main.c
 * Author: joseherna0709
 *
 * Created on March 17, 2016, 7:26 PM
 */

// PIC18F87J11 Configuration Bit Settings

#include "MCU_config.h"
#include "carseat.h"
#include "uart.h"

volatile unsigned char asciiValue = 0;
volatile unsigned char ptr = 0;
volatile unsigned char string[n];


void main(void) {
    set_pins_ExplorerBoard();
    set_Fosc();
    set_interrupts();
    
    //Variables
    unsigned char weight;
    unsigned char car;
    unsigned char temp;
    unsigned char message;
    
    while(1){
        weight = getS2ExplorerBoard();
        car = getS1ExplorerBoard();
        temp = getTemperature();
        message = package(weight, car, temp);
        TRISD = message;
        
        delay(1000);
        
        UART_init();
        UART_transmit();
        
        delay(3000);
    }
    return;
}