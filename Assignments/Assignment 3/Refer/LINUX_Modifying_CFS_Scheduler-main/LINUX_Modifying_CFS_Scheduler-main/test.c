/* Name: Vaibhav Saxena
   Roll_Number: 2019342 */

#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/time.h>

int main()
{
	long pid;
	long tem;
	long i = 0;
	
	pid = fork();
	if(pid!=0)
	{
		//Parent Process
	
		printf("PID of Parent Process: %d \nPID of Child Process: %ld\n",(long)getpid(),pid);
		syscall(440,pid,1000000000);
		
		struct timeval t1,t2;
		gettimeofday(&t1,NULL);
		for(i=0;i<10000000000;i++);
		gettimeofday(&t2,NULL);
				
		double time = (double)(t2.tv_usec-t1.tv_usec)/1000 + (double)(t2.tv_sec-t1.tv_sec)*1000;
		printf(".\nTime taken by Parent: %lf\n",time);
		
		wait();
	}
	else
	{
		//Child Process
		
		struct timeval t1,t2;
		gettimeofday(&t1,NULL);
		for(i=0;i<10000000000;i++);
		gettimeofday(&t2,NULL);
		
		double time = (double)(t2.tv_usec-t1.tv_usec)/1000 + (double)(t2.tv_sec-t1.tv_sec)*1000;
		printf(".\nTime taken by Child: %lf\n",time);
	}
	
	return 0;
}
