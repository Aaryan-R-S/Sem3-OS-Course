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

void signal_handler_SR(int signo);
pid_t child_S1;

ll getRandNum(){
    ll randNum=0;
    while(randNum==0){
        asm("rdrand %0\n\t"
            :"=a"(randNum)
            :
            :
        );
    }
    return randNum;
}

int main(int argc, const char* argv[]){
    if(argc!=1){
        printf("Some arguments are missing in execl\n");
        exit(1);
    }
    sscanf(argv[0], "%d", &child_S1);

    if(signal(SIGTERM, signal_handler_SR) == SIG_ERR) {
        fprintf(stderr, "Cannot handle SIGTERM in SR!\n");
        exit(1);
    }

    struct sigaction my_action;
    my_action.sa_handler = &signal_handler_SR;
    my_action.sa_flags = SA_RESTART | SA_SIGINFO;
    if(sigaction(SIGALRM, &my_action, NULL)!=0){
        printf("Some error encountered in sigaction\n");
		exit(1);
    }

    struct itimerval timer;
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 2;
    timer.it_interval.tv_usec = 0;
    
    if(setitimer(ITIMER_REAL, &timer, NULL)!=0){
        printf("Some error encountered in settimer\n");
		exit(1);
    }

    while(1){
        pause();
    }

	return 0;
}

void signal_handler_SR(int signo){
	if(signo == SIGTERM){
		printf("\n[Caught SIGTERM in SR]\n");
        printf("%d\n\n", (int)getRandNum());
	}
	else if(signo == SIGALRM){  
		printf("[Caught SIGALRM in SR]\n");
        kill(getpid(), SIGTERM);
		union sigval queue_val = {getRandNum()};
		if(sigqueue(child_S1, SIGTERM, queue_val)!=0){
            printf("Some error encountered in sigqueue\n");
            exit(1);
        }
	}
	else{
		fprintf(stderr, "Unexpected signal!\n");
		exit(1);
	}
}