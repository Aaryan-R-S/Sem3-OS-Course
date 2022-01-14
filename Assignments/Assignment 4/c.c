#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>
#include<fcntl.h>
#include<stdlib.h>

int main(){
    char my_data[8];

    int ret_val = syscall(452, my_data);
    if(ret_val==0){
        printf("Successfully dequeued data\n");
        printf("Read data %s\n", my_data);
    }
    else{
        printf("Queue is empty\n");
    }
    return 0;
}