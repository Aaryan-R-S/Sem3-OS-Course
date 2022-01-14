#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/signal.h>
#include<sys/time.h>
#include<time.h>
#define BUF_LEN 256
typedef unsigned long long ull;
typedef signed long long ll;

void signal_handler_S1(int signo, siginfo_t *si, void *ucontext);
void signal_handler_SR(int signo);
void signal_handler_ST(int signo);

int run_SR_only = 0;
int run_ST_only = 0;

pid_t child_S1 = 0;
pid_t child_SR = 0;
pid_t child_ST = 0;

int flag = 0;

ll getRandNum(){
    ll randNum;
    const int to = 10;
    int i=0;
    while (i<to){
        asm("rdrand %0\n\t"
            :"=a"(randNum)
			:
			:
		);
        if(randNum){
			break;
		} 
        i++;
    }
    return randNum;
}

char* getTimeStamp() {
    ull myVal;
    unsigned int h, l;
	__asm__ __volatile__("rdtsc" : "=a" (l), "=d" (h));
	myVal = ((ull)l) | (((ull)h) << 32);
	myVal /= 1.6e9;
	myVal += 1637447170;
	// printf("%llu \n", myVal);
	time_t rawtime = myVal;

    if (rawtime == -1) {
        // puts("The time() function failed");
        return "Some error encountered retrying...\0";
    }
    
    struct tm* ptm = localtime(&rawtime);
    if (ptm == NULL) {
        // puts("The localtime() function failed");
        return "Some error encountered retrying...\0";
    }

	char* dt = asctime(ptm);
    // printf("UTC time: %s", asctime(ptm));
	return dt; 
}

int main(int argc, const char* argv[]){
	run_SR_only = (int)(argv[1][0]-'0');
	run_ST_only = (int)(argv[2][0]-'0');

	// Fork
	child_S1 = fork();
	if(child_S1 == 0){
		// Child Process - S1
		// printf("S1\n");
		struct sigaction my_action;
		my_action.sa_sigaction = &signal_handler_S1;
		my_action.sa_flags = SA_SIGINFO;
		sigaction(SIGTERM, &my_action, NULL);
		while(1){
			pause();
		}
	}
	else{
		// Parent Process
		child_SR = fork();
		if(child_SR == 0){
			// Child Process - SR
			// printf("SR\n");
			if(signal(SIGTERM, signal_handler_SR) == SIG_ERR) {
				fprintf(stderr, "Cannot handle SIGTERM in SR!\n");
				exit(1);
			}

			struct sigaction my_action;
			my_action.sa_handler = &signal_handler_SR;
			my_action.sa_flags = SA_SIGINFO;
			sigaction(SIGALRM, &my_action, NULL);

			struct itimerval timer;
			timer.it_value.tv_sec = 1;
			timer.it_value.tv_usec = 0;
			timer.it_interval.tv_sec = 4;
			timer.it_interval.tv_usec = 0;
			
			if(run_ST_only!=1){
				setitimer(ITIMER_REAL, &timer, NULL);
			}

			while(1){
				// kill(getpid(), SIGALRM);
				sleep(60);
			}
		}
		else{
			child_ST = fork();
			if(child_ST == 0){
				// Child Process - ST
				// printf("ST\n");
				if(signal(SIGTERM, signal_handler_ST) == SIG_ERR) {
					fprintf(stderr, "Cannot handle SIGTERM in ST!\n");
					exit(1);
				}

				struct sigaction my_action;
				my_action.sa_handler = &signal_handler_ST;
				my_action.sa_flags = SA_SIGINFO;
				sigaction(SIGALRM, &my_action, NULL);

				struct itimerval timer;
				timer.it_value.tv_sec = 1;
				timer.it_value.tv_usec = 0;
				timer.it_interval.tv_sec = 4;
				timer.it_interval.tv_usec = 0;
				
				if(run_SR_only!=1){
					setitimer(ITIMER_REAL, &timer, NULL);
				}

				while(1){
				// 	kill(getpid(), SIGALRM);
					sleep(60);
				}
			}
			else{
				// printf("Parent\n");
				printf("Parent PID: %d, S1 PID: %d, SR PID: %d & ST PID: %d\n", getpid(), child_S1, child_SR, child_ST);
				printf("----------------------------------\n");
				while(1){
					sleep(60);
					exit(0);
				}
			}
		}
	}
	return 0;
}

void signal_handler_S1(int signo, siginfo_t *si, void *ucontext){
	if(signo == SIGTERM){
		printf("Caught SIGTERM in S1!\n");
		// printf("ok!\n");
		if(run_SR_only!=1){
			printf("Queued Data: %s\n", (char*)si->si_ptr);
		}
		if(run_ST_only!=1){
			printf("Queued Data: %d\n", si->si_int);
		}
		// printf("ok!\n");
		sleep(0.5);
		// }
	}
	else{
		printf("Unexpected signal!\n");
		exit(1);
	}
}

void signal_handler_SR(int signo){
	if(signo == SIGTERM){
		printf("Caught SIGTERM in SR!\n");
	}
	else if(signo == SIGALRM){
		printf("Caught SIGALRM in SR!\n");
		sleep(1);
		union sigval queue_val = {getRandNum()};
		sigqueue(child_S1, SIGTERM, queue_val);
		sleep(1);
		kill(getpid(), SIGTERM);
		printf("----------------------------------\n");
	}
	else{
		fprintf(stderr, "Unexpected signal!\n");
		exit(1);
	}
}

void signal_handler_ST(int signo){
	if(signo == SIGTERM){
		printf("Caught SIGTERM in ST!\n");
	}
	else if(signo == SIGALRM){
		printf("Caught SIGALRM in ST!\n");
		sleep(1);
		union sigval queue_val;
		char *x = getTimeStamp();
		queue_val.sival_ptr = x;
		// printf("%s", (char*) queue_val.sival_ptr);
		sigqueue(child_S1, SIGTERM, queue_val);
		sleep(1);
		kill(getpid(), SIGTERM);
		printf("----------------------------------\n");
	}
	else{
		fprintf(stderr, "Unexpected signal!\n");
		exit(1);
	}
}
