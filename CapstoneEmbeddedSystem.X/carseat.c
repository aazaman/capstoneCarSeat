#include "MCU_config.h"
#include "carseat.h"

//This header file contains a series of modules that observe the environment
//of the car seat

//Function to determine if the child is in the seat
//Returns 1 if child is seated
unsigned char getWeightInSeat(){
    //weighBit 0 = no voltage due to weight in seat
    if(weightBit) return 0;
    return 1;
}

//Function to determine if the car is on
unsigned char getCarPower(){
    //Returns 1 if car is on
    //Returns 0 if car is off -> using battery
    if(carPowerBit) return 1;
    return 0;
}

//Function to determine the temperature inside the car
//Returns the temperature in decimal
unsigned char getTemperature(){
    unsigned char L_byte; //grab ADRESL from A/D converter result
    unsigned char H_byte; //grab ADRESH from A/D converter result
    
    delay(100); //delay a few ms(polling)
    
    ADCON0 |= 0x02; //ADCON.GODONE = 1;
    while(ADCON0bits.GO == 1); //Hold here until A/D conversion is done
    L_byte = ADRESL; //get low byte result
    H_byte = ADRESH; //get high byte result
    L_byte = L_byte >> 2;//shift 6 MSB to 6 LSB
    H_byte = H_byte << 6;//shift 2 LSB to 2 MSB
    
    delay(100);
    
    if((L_byte | H_byte) > desiredTemp) //Combine the two and check if result is greater
        return 1;              //then 80 degrees. 1 = above 80
    return 0;
}

//Function to observe movement of the car seat
unsigned char accel(){
    return 0;
}

//Simple delay function
void delay(unsigned int x){
    unsigned int i;
    unsigned int j;
    for(i = 0; i < x; i++){
        for(j = 0; j < 165; j++){}
    }
}
//Function to package the environment of the car seat
unsigned char package(unsigned char w, unsigned char c, unsigned char t){
    //0b00000tcw
    //t = temperature above 80 degrees
    //c = car on or off
    //w = weight yes or no
    c = c<<1;
    t = t<<2;
   
    return w | c | t;
}
