#include "MCU_config.h"
#include "uart.h"
#define n 32

#define baudrate 9600 //bits per second
#define Fosc 4000000 //4MHZ

void UART_init(){
    
    set_UARTtx();
    set_UARTrx();
    set_UARTBaudConfig();
    set_UARTBaudRate();
}

void set_UARTtx(){
    TXSTA1bits.CSRC  = 0;  //Don't care
    TXSTA1bits.TX9   = 0;  //Use 8-bit data communication
    TXSTA1bits.TXEN  = 1;  //Transmit is enabled;
    TXSTA1bits.SYNC  = 0;  //Asynchronous mode
    TXSTA1bits.SENDB = 0;  //Sync Break transmission has completed 
    TXSTA1bits.BRGH  = 1;  //High Baud Rate
}

void set_UARTrx(){
    RCSTA1bits.SPEN  = 1;  //Serial Port is enabled
    RCSTA1bits.RX9   = 0;  //Receive 8 bits
    RCSTA1bits.SREN  = 0;  //Don't care
    RCSTA1bits.CREN  = 1;  //Continuous Receive Enabled
    RCSTA1bits.ADDEN = 0;  //Address detection is disabled
}

void set_UARTBaudConfig(){
    BAUDCON1bits.ABDOVF = 0;  //No Auto-Baud Detection
    BAUDCON1bits.RXDTP  = 0;  //Receive data is not inverted
    BAUDCON1bits.TXCKP  = 0;  //Idle state for transmit is a high level
    BAUDCON1bits.BRG16  = 0;  //8bit Baud Rate Generator
    BAUDCON1bits.WUE    = 0;  //Wake up Enable is off, RXx pin is not monitored
}

void set_UARTBaudRate(){
    //Second per bit = 1/baudrate
    //SPBRG value is only a number that references the baudrate
    //it is calculated by the formula bellow
    SPBRG = 25;
}
     
//Function to test transmission
void UART_transmit(){
    while(TXSTAbits.TRMT == 0);
    if(TRISDbits.RD2)
        TXREG = 0x31;
    else
        TXREG = 0x30;
    while(TXSTAbits.TRMT == 0);
    if(TRISDbits.RD1)
        TXREG = 0x31;
    else
        TXREG = 0x30;
    while(TXSTAbits.TRMT == 0);
    if(TRISDbits.RD0)
        TXREG = 0x31;
    else
        TXREG = 0x30;
    while(TXSTAbits.TRMT == 0);
    TXREG = 0x0A;
}

void USART_echo(unsigned char *s){
    while(*s){
        while(TXSTAbits.TRMT == 0);
        TXREG = *s;
        s++;
    }
}

void interrupt ISR(){
    extern volatile unsigned char asciiValue;
    extern volatile unsigned char ptr;
    extern volatile unsigned char string[n];

    int i;
    
    if(PIR1bits.RC1IF){
        asciiValue = RCREG1;
        
        if((asciiValue != 0x0A) &&(ptr < n)){
            string[ptr] = asciiValue;
            ptr++;
        }
        else{
            USART_echo(string);
            for(i = 0; i < ptr; i++)
                string[i] = 0x00;
            ptr = 0;
        }
        PIR1bits.RCIF = 0; //Clear interrupt flag;
    }
}