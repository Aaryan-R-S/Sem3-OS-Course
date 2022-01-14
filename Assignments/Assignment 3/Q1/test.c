#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>
#include<linux/kernel.h>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/resource.h>

#define SYS_delay_sched_process 450

int main(int argc, char** argv){
	int priority = 7;
	id_t my_pid = getpid();
	int whichField = PRIO_PROCESS;
	setpriority(whichField, my_pid, priority);

	unsigned long pid;
	
	pid = fork();
	if(pid==0){
		struct timeval t1,t2;

		gettimeofday(&t1, NULL);
		for(int i=0; i<1000000000; i++);
		gettimeofday(&t2, NULL);
		
		double timeTaken = (double)(t2.tv_sec-t1.tv_sec)*1000 + (double)(t2.tv_usec-t1.tv_usec)/1000;
		printf("Time taken by Child process: %lfms\n", timeTaken);

	}

	else{
        unsigned long delay_ms = 10;

		printf("PID of Parent Process: %d \n", getpid());
        printf("PID of Child Process: %ld \n", pid);
		
        syscall(SYS_delay_sched_process, (unsigned long) getpid(), delay_ms*100000);
		
		struct timeval t1,t2;

		gettimeofday(&t1,NULL);
		for(int i=0; i<1000000000; i++);
		gettimeofday(&t2,NULL);
				
		double timeTaken = (double)(t2.tv_sec-t1.tv_sec)*1000 + (double)(t2.tv_usec-t1.tv_usec)/1000;
		printf("Time taken by Parent process: %lfms\n", timeTaken);

        int status;
		wait(&status);
	}
    return 0;
}