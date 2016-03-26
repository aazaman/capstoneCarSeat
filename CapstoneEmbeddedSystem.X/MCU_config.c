#include "MCU_config.h"

//Sets the Oscilator frequency for the MCU
void set_Fosc(){
    OSCCON = 0x6F; //INTSOC frequency 4MHz
}

//Input pins for recieving data from enviornment
void set_input_pins(){
    TRISHbits.TRISH2 = INPUT; //Input pin for weight(digital)
    TRISFbits.TRISF4 = INPUT; //Input pin for car on or off(digital)
    TRISAbits.TRISA3 = INPUT; //Input pin for temp voltage(analog)
    TRISCbits.TRISC7 = INPUT; //Input from UART bluetooth receive
}

//Output pins for sending data
void set_output_pins(){
    TRISCbits.TRISC6 = INPUT;//Output for UART bluetooth transmit
}
//Analog to Digital Converter Configuration
void set_adc(){
    //Set ANCON Configuration bits
    WDTCONbits.ADSHR = 1; //Share address SFR for ANCON0 & ANCON1(p. 340)
    ANCON1 = 0xFF; //AN15-AN8 are all digital I/O (p. 311)
    ANCON0 = 0xD7; //AN7:AN6, AN4, AN2-AN0 are digital, AN3 is analog(p.311)
                   //RA3 = AN3 analog input for temperature voltage
    
    //Set ADCON Configuration bits
    WDTCONbits.ADSHR = 0; //Share address SFR for ADCON0 & ADCON1(p. 340)
    ADCON0 = 0x0D; //ADCON0 = (0)(0)(0011)(0)(1) (p.309)
                   //(Vss)(Vdd)(CH3)(G0)(ADON)
    ADCON1 = 0xBA; //ADCON1 = (1)(0)(111)(010) (p.310)
                   //(Right Just.)(ADCAL)(20TAD)(Fosc/32)
}

void set_interrupts(){
    INTCONbits.GIE = 1;  //Enable all global interrupts
    RCONbits.IPEN = 1;   //Enable Priority interrupt levels
    PIE1bits.RCIE = 1;   //Enable USART Receive interrupt
    IPR1bits.RCIP = 1;   //Enable USART Receive interrupt high-priority
}

//Helper function to set input/output/AtoD converter pins
void set_pins(){
    set_input_pins();
    set_output_pins();
    set_adc();
}

//Function for Explorer Board
void set_input_ExplorerBoard(){
    TRISAbits.TRISA1 = INPUT;
    TRISAbits.TRISA5 = INPUT; //S1 Button
    TRISBbits.TRISB0 = INPUT; //S2 Button
    TRISCbits.TRISC7 = INPUT; //Input from UART receive
    
}

void set_output_ExplorerBoard(){
    TRISD = OUTPUT;
    TRISCbits.TRISC6 = INPUT;
    
}
void set_pins_ExplorerBoard(){
    set_input_ExplorerBoard();
    set_output_ExplorerBoard();
    set_adc_ExplorerBoard();
}

unsigned char getS1ExplorerBoard(){
    if(S1 == 0) return 1;
    return 0;
}

unsigned char getS2ExplorerBoard(){
    if(S2 == 0) return 1;
    return 0;
}

void set_adc_ExplorerBoard(){
    //Set ANCON Configuration bits
    WDTCONbits.ADSHR = 1; //Share address SFR for ANCON0 & ANCON1(p. 340)
    ANCON1 = 0xFF; //AN15-AN8 are all digital I/O (p. 311)
    ANCON0 = 0xDD; //AN7:AN6, AN4-AN2, AN0 are digital, AN1 is analog(p.311)
                   //RA1 = AN1 analog input for temperature voltage
    
    //Set ADCON Configuration bits
    WDTCONbits.ADSHR = 0; //Share address SFR for ADCON0 & ADCON1(p. 340)
    ADCON0 = 0x05; //ADCON0 = (0)(0)(0001)(0)(1) (p.309)
                   //(Vss)(Vdd)(CH1)(G0)(ADON)
    ADCON1 = 0xBA; //ADCON1 = (1)(0)(111)(010) (p.310)
                   //(Right Just.)(ADCAL)(20TAD)(Fosc/32)
}