#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/wait.h>

int func(void* args){
	int* buf = args;
	buf[1] = 42;
	return 0;
}

int main(int argc, char** argv){
	// Allocate stack for child process
	const int STACK_SIZE = 1 << 16;
	char* stack = malloc(STACK_SIZE);
	if(!stack){
		perror("malloc");
		return EXIT_FAILURE;
	}

	int flags = 0;
	if(argc > 1 && argv[1][0] == '1')
		flags |= CLONE_VM;    // the calling process and the child process run in the same memory space
	flags |= CLONE_FILES; // the calling process and the child process share the same file descriptor table

	int args[] = {42, 0};

	int pid = clone(&func, // function executed by child process
	                stack + STACK_SIZE, // top of stack for child process
	                flags, // specify what is shared between the two processes
	                args // only argument passed to func
	);
	if(pid < 0){
		perror("clone");
		return EXIT_FAILURE;
	}

	int status;
	if(waitpid(pid, &status, __WCLONE) < 0){
		perror("wait");
		return EXIT_FAILURE;
	}
	printf("Child process exited with status %d.\nargs[1] = %d\n", status, args[1]);

	// cleaning up is good
	free(stack);

	return 0;
}

