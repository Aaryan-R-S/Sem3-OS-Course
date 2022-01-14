#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

/* ----------------------------------------------------------------------------
 * Named pipes are special file that are used by processes to communicate
 *
 * The name of the file is define in PIPE_NAME and it will persist after
 * termination, it can be reused.
 *
 * Opening a named pipe is a blocking call, until both ends are connected.
 * This behavior can be override with O_NDELAY in open(). A process writting
 * a pipe with no reader will be signaled with SIGPIPE.
 *
 * File permissions in mknod are added with the current user permission.
 * Therfore using umask(0) will clean the inherited permission.
 *
 */

#define PIPE_NAME "./MyPipe"

// Process id
pid_t child_pid;

int main(int argc, const char *argv[]){

	// Creating the pipe
	umask(0);
	if(mknod(PIPE_NAME, S_IFIFO | 0660, 0) == -1){
		if(errno != EEXIST){
			perror("Cannot create the pipe");
			exit(EXIT_FAILURE);
		}
		else
			printf("Using existing file\n");
	}

	// Reading
	char buffer[128];
	int fd = open(PIPE_NAME, O_RDONLY);
	read(fd, buffer, 128);
	close(fd);
	printf("Received: %s\n", buffer);

	return 0;
}
