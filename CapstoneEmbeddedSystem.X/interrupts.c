#include "MCU_config.h"
#include "interrupts.h"
#include "uart.h"

void set_interrupts(){
    INTCONbits.GIE = 1;  //Enable all global interrupts
    RCONbits.IPEN = 1;   //Enable Priority interrupt levels
    PIE1bits.RCIE = 1;   //Enable USART Receive interrupt
    IPR1bits.RCIP = 1;   //Enable USART Receive interrupt high-priority
}

void interrupt ISR(){
    extern volatile unsigned char asciiValue;
    extern volatile unsigned char ptr;
    extern volatile unsigned char string[n];

    //This interrupt is for USART communication
    if(PIR1bits.RC1IF){
        int i;
        asciiValue = RCREG1;
        if((asciiValue != 0x0A) &&(ptr < n)){
            string[ptr] = asciiValue;
            ptr++;
        }
        else{
            string[ptr] = 0x0A;
            UART_transsmit((char*)string);
            for(i = 0; i < ptr; i++)
                string[i] = 0x00;
            ptr = 0;
        }
        PIR1bits.RCIF = 0;
    }
}