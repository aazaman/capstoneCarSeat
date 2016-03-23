//This header file contains a series of modules that observe the environment
//of the car seat

//Function to determine if the child is in the seat
//Returns 1 if child is seated
unsigned char getWeightInSeat();

//Function to determine if the car is on
//Returns 1 if car is on
//Returns 0 if car is off -> using battery
unsigned char getCarPower();

//Function to determine the temperature inside the car
//Returns the temperature in decimal
unsigned char getTemperature();

//Function to observe movement of the car seat
unsigned char accel();

//Poll Delay
void delay(unsigned int);

//Package car seat environment for UART(3 least significant bits)
unsigned char package(unsigned char, unsigned char, unsigned char);