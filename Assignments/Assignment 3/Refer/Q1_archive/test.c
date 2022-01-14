#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>
#include<linux/kernel.h>
#include<sys/time.h>


#define SYS_delay_sched_process 450

int main(int argc, char** argv){
	unsigned long pid;
	unsigned long delay_ms;
	
	pid = fork();
	if(pid==0){
        syscall(SYS_delay_sched_process, (unsigned long) getpid(), 0);

		struct timeval t1,t2;
		gettimeofday(&t1, NULL);
		for(int i=0; i<10000000000; i++);
		gettimeofday(&t2, NULL);
		
		double timeTaken = (double)(t2.tv_sec-t1.tv_sec)*1000 + (double)(t2.tv_usec-t1.tv_usec)/1000;
		printf("Time taken by Child process: %lf \n", timeTaken);
	}
	else{
		printf("PID of Parent Process: %d \n", getpid());
        printf("PID of Child Process: %ld \n", pid);
        syscall(SYS_delay_sched_process, (unsigned long) getpid(), 1);
		
		struct timeval t1,t2;
		gettimeofday(&t1,NULL);
		for(int i=0; i<10000000000; i++);
		gettimeofday(&t2,NULL);
				
		double timeTaken = (double)(t2.tv_sec-t1.tv_sec)*1000 + (double)(t2.tv_usec-t1.tv_usec)/1000;
		printf("Time taken by Parent process: %lf \n", timeTaken);
		wait();
	}
    return 0;
}