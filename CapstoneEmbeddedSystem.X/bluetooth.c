#include "MCU_config.h"
#include "bluetooth.h"
#include "uart.h"
#include "functions.h"

volatile unsigned char string[n];

void set_Bluetooth(){
    
    unsigned char connected = false;
    
    WAKE_SW();                               //Bluetooth Command Mode
    UART_transsmit((char *)"SB,1");          //Set Bluetooth Baud Rate
    UART_transsmit((char *)"+");             //Set echo for testing
    UART_transsmit((char *)"SF,1");          //Reset default factory settings
    UART_transsmit((char *)"SS,00100000");   //Enable Support for Device
    UART_transsmit((char *)"SR,28000000");   //Auto Advertise
    UART_transsmit((char *)"R,1");           //Reboot to set changes
    
    //wait here until a connection is established
    while(!connected){
        UART_transsmit((char *)"Q");
        connected = str_cmp((char *)string, (char *)"Not Connected");
    }
    
    UART_transsmit((char *)"B,1");          //Bond the peer device
    UART_transsmit((char *)"I");             //Enter MLPD mode
}

void WAKE_SW(){PORTAbits.RA4 = 1;}           //Set bluetooth to command mode

void SLEEP_SW(){PORTAbits.RA4 = 0;}          //Set bluetooth to sleep mode

void WAKE_HW(){PORTAbits.RA5 = 1;}           //Set bluetooth out of dorment

void SLEEP_HW(){PORTAbits.RA5 = 0;}          //Set to dorment mode