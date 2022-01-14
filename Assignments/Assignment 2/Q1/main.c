#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/signal.h>
#include<sys/time.h>
#include<time.h>
#include<sys/ipc.h>
#include<sys/shm.h>

typedef unsigned long long ull;
typedef signed long long ll;

void signal_handler_S1(int signo, siginfo_t *si, void *ucontext);

int main(int argc, const char* argv[]){
	// Fork
	pid_t child_S1 = 0;
	pid_t child_SR = 0;
	pid_t child_ST = 0;

	child_S1 = fork();
	if(child_S1<0){
		printf("Some error encountered in fork\n");
		exit(1);
	}
	if(child_S1 == 0){
		// Child Process - S1
		struct sigaction my_action;
		my_action.sa_sigaction = &signal_handler_S1;
		my_action.sa_flags = SA_RESTART | SA_SIGINFO;
		if(sigaction(SIGTERM, &my_action, NULL)!=0){
			printf("Some error encountered in sigaction\n");
			exit(1);
		}
		while(1){
			pause();
		}
	}
	else{
		child_SR = fork();
		if(child_SR<0){
			printf("Some error encountere in fork\n");
			exit(1);
		}
		if(child_SR == 0){
			// Child Process - SR
			char child_S1_str[10];
			sprintf(child_S1_str, "%d", child_S1);
			if(execl("sr", child_S1_str, NULL)==-1){
				printf("Some error encountered in execl\n");
				exit(1);
			}
		}
		else{
			child_ST = fork();
			if(child_ST<0){
				printf("Some error encountered in fork\n");
				exit(1);
			}
			if(child_ST == 0){
				// Child Process - ST
				char child_S1_str[10];
				sprintf(child_S1_str, "%d", child_S1);
				if(execl("st", child_S1_str, NULL)==-1){
					printf("Some error encountere in execl\n");
					exit(1);
				}
			}
			else{
				// Parent Process
				printf("-------------------------------------------------------------------------------------------------\n");
				printf("Parent PID: %d, S1 PID: %d, SR PID: %d & ST PID: %d\n", getpid(), child_S1, child_SR, child_ST);
				printf("-------------------------------------------------------------------------------------------------\n");
				while(1){
					sleep(60);
				}
			}
		}
	}
	return 0;
}

void signal_handler_S1(int signo, siginfo_t *si, void *ucontext){
	if(signo == SIGTERM){
		printf("[Caught SIGTERM in S1]\n");
		if(si->si_int!=0){
			printf("Random Number (an int): %d\n", si->si_int);
		}
		else{
			key_t key = ftok("shmfile",65);
			int shmid = shmget(key,1024,0666|IPC_CREAT);
			char *str = (char*) shmat(shmid,(void*)0,0);
			printf("Timestamp (UTC): %s",str);
			printf("-------------------------------------------------------------------------------------------------\n");
		}
	}
	else{
		printf("Unexpected signal!\n");
		exit(1);
	}
}