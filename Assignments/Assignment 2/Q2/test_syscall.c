#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>

#define SYS_kernel_2d_memcpy 449

int main(int argc, char** argv){
    float myArr[5][4] = {
        {1.020, 2.123, 3.010, 4.100},
        {1.080, 2.001, 3.020, 4.200},
        {1.050, 2.002, 3.030, 4.300},
        {1.409, 2.003, 3.040, 4.400},
        {1.011, 2.004, 3.050, 4.1234},
    };

    float myArr_copy[5][4];
    
    printf("\nTesting kernel_2d_memcpy system call\n");

    printf("\nPrinting \"original\" 2-D floating point matrix...\n");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%f ", myArr[i][j]);
        }
        printf("\n");
    }

    printf("\nPrinting \"copied\" 2-D floating point matrix...\n");
    int ret_val = syscall(SYS_kernel_2d_memcpy, myArr, myArr_copy, 80);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%f ", myArr_copy[i][j]);
        }
        printf("\n");
    }
    
    printf("\nReturn value: %d\n", ret_val); 

    return 0;
}