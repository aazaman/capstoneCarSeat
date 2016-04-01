#include "MCU_config.h"
#include "functions.h"

//Simple delay function
void delay(unsigned int x){
    unsigned int i;
    unsigned int j;
    for(i = 0; i < x; i++){
        for(j = 0; j < 165; j++){}
    }
}

unsigned char str_cmp(unsigned char* s1, unsigned char* s2){
    while(s1 && s2){       //while s1 and s2 are still readable
        if(*s1 != *s2)     //check is one character doesnt match
            return false;  //if so, terminate 
        s1++;              //otherwise increment both
        s2++;
    }
    return true;           //all characters pass
}