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

void signal_handler_ST(int signo);
pid_t child_S1;

char* getTimeStamp() {
    ull myVal;
    unsigned int h, l;
	__asm__ __volatile__("rdtsc" : "=a" (l), "=d" (h));
	myVal = ((ull)l) | (((ull)h) << 32);
	myVal /= 1.6e9;
	myVal += 1637699314;
	// printf("%llu \n", myVal);
    
	time_t rawtime = myVal;
    if (rawtime == -1) {
        return "Some error encountered in getTimeStamp...\0";
    }
    struct tm* ptm = localtime(&rawtime);
    if (ptm == NULL) {
        return "Some error encountered in getTimeStamp...\0";
    }
	char* dt = asctime(ptm);
	return dt; 
}

int main(int argc, const char* argv[]){
    if(argc!=1){
        exit(-1);
    }
    sscanf(argv[0], "%d", &child_S1);

    if(signal(SIGTERM, signal_handler_ST) == SIG_ERR) {
        fprintf(stderr, "Cannot handle SIGTERM in ST!\n");
        exit(1);
    }

    struct sigaction my_action;
    my_action.sa_handler = &signal_handler_ST;
    my_action.sa_flags = SA_RESTART | SA_SIGINFO;
    if(sigaction(SIGALRM, &my_action, NULL)!=0){
        printf("Some error encountered in sigaction\n");
		exit(1);
    }

    struct itimerval timer;
    timer.it_value.tv_sec = 2;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 2;
    timer.it_interval.tv_usec = 0;
    
    if(setitimer(ITIMER_REAL, &timer, NULL)!=0){
        printf("Some error encountered in sigqueue\n");
		exit(1);
    }

    while(1){
        pause();
    }

	return 0;
}

void signal_handler_ST(int signo){
	if(signo == SIGTERM){
		printf("\n[Caught SIGTERM in ST]\n");
        printf("%s\n", getTimeStamp());
	}
	else if(signo == SIGALRM){
		printf("\n[Caught SIGALRM in ST]\n");
        kill(getpid(), SIGTERM);
        key_t key = ftok("shmfile",65);
        int shmid = shmget(key,1024,0666|IPC_CREAT);
        char *str = (char*) shmat(shmid,(void*)0,0);
		char *temp = getTimeStamp();
        strcpy(str, temp);

		union sigval queue_val;
		queue_val.sival_int = 0;
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
