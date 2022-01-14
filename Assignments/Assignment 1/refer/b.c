#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<unistd.h>
#include<string.h>
#include "q2.h"

void B(int64_t args){
    __asm__("mov -0x28(%rbp), %rdi");
    __asm__("add $0x30, %rsp");
    __asm__("mov %rbp, %rsp");
    __asm__("pop %rbp");

    // __asm__("mov $0x12c2, %rbp");
    __asm__("push %rbp");
    __asm__("mov %rsp,%rbp");
    __asm__("sub $0x30,%rsp");
    __asm__("mov %rdi,-0x28(%rbp)");

    write(1, "Inside B\n", 10);
    {
        char* s = (char*) malloc(8*sizeof(char));
        int myChar = 0;
        for (int i = 0; i < 8; i++){
            myChar = 0;
            for (int j = 0; j < 8; j++){
                myChar += ((args>>(j+i*8))&1)*(1<<j);
            }
            s[7-i] = (char)myChar;
        }
        for (int i = 0; i < 8; i++){     
            printf("%c", s[i]);
        }
        printf("\n");
    }
    __asm__ volatile("jmp 0x12c0");
}
