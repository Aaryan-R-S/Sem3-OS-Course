#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>
#include<fcntl.h>
#include<stdlib.h>

int main(){
    int fd = open("/dev/urandom", O_RDONLY);
    if(fd<0){
        printf("Cannot open /dev/urandom file\n");
        exit(1);
    }

    char my_data[8];
    int my_len = read(fd, my_data, sizeof(my_data));
    if(my_len<0){
        printf("Cannot read content from /dev/urandom file\n");
        exit(1);
    }
    printf("Read %s from /dev/urandom\n", my_data);

    int ret_val = syscall(451, my_data);
    if(ret_val==0){
        printf("Successfully queued data\n");
    }
    else{
        printf("Encountered some error while queueing data\n");
        exit(1);
    }
    return 0;
}