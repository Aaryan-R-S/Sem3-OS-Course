#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<unistd.h>
#include<string.h>

void C(){
    write(1, "Inside C\n", 10);
    exit(0);
}