#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void* func(void* arg){
	int status;

/*
	// thread releases resources the moment it ends, so joining is not mandatory
	// but in that case, pthread_exit in main function becomes mandatory
	if(status = pthread_detach(pthread_self())){
		fprintf(stderr, "pthread_detach: %s\n", strerror(status));
		pthread_exit(NULL); 
	}
*/

	puts("We are inside the thread.");
	printf("PID in thread: [%d]. Compare to the PID of the process.\n", getpid());

	char* buf = arg;
	printf("Text from main: %s\n", buf);
	strcpy(buf, "Yes");

	pthread_exit(NULL);
}

int main(int argc, char** argv){
	printf("PID: [%d]\n", getpid());

	int status;
	char buf[] = "Hi!";

	pthread_t ptid;
	if(status = pthread_create(&ptid, NULL, &func, buf)){
		fprintf(stderr, "pthread_create: %s\n", strerror(status));
		return EXIT_FAILURE;
	}

	if(argc > 1 && argv[1][0] == '1') sleep(1);
	puts("This may or may not execute before thread terminates.");

	if(status = pthread_join(ptid, NULL)){
		fprintf(stderr, "pthread_join: %s\n", strerror(status));
		return EXIT_FAILURE;
	}

	puts("This executes definitely after the thread ends.");

	printf("Text from thread: %s\n", buf);

	return 0;
}

