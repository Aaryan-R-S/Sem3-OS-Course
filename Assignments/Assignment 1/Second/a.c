#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<unistd.h>
#include<string.h>
extern void B();

void A(){
    write(1, "Inside A\n", 10);
    int64_t num = 478560413000; 
    B(num);
    write(1, "Inside A again\n", 16);
}

