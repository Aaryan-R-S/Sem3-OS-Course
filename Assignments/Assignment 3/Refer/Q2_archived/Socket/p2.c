#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/un.h>

#define PENDING_QUEUE_SIZE 1
#define MAX_MESSAGE_SIZE 6
#define LOCAL       "./sockP2"
#define DESTINATION "./sockP1" 

struct myStruct{
    char* myIdx;
    char* myStr;
};

void receive_t_rand_str(struct myStruct** myData, int n, int l, int* start){
	struct sockaddr_un address;
	int fd;

	// Make a socket file
	if((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){
		perror("Socket cannot be instantiated");
		exit(EXIT_FAILURE);
	}

	// Destination
	address.sun_family = AF_UNIX;
	memcpy(address.sun_path, DESTINATION, strlen(DESTINATION) + 1);

	// Connect - blocking call
	// STREAM are need to connect to the other hand before
	// starting a transfer.
	// The file descriptor is marked as connected
	// printf("Connecting...\n");
	if(connect(fd, (struct sockaddr*) &address, sizeof(address)) == -1){
		if(errno == ECONNREFUSED) printf("ECONNREFUSED\n");
		close(fd);
		perror("Cannot connect");
		exit(EXIT_FAILURE);
	}
	// printf("Established connection with: %s\n", address.sun_path);

	// Receiving
	struct myStruct *temp = (struct myStruct*) malloc(sizeof(struct myStruct));
	temp->myIdx = (char*) malloc(sizeof(char)*((*start)<10?2:3));
	temp->myStr = (char*) malloc(sizeof(char)*MAX_MESSAGE_SIZE);
	size_t size;
	while(1){
		// printf("Write a message: ");
		size = recv(fd, temp->myIdx, ((*start)<10?2:3), 0);
		if(size == -1) { 
			if(errno == ECONNRESET) printf("ECONNRESET\n");
			close(fd);
			perror("Receiver"); exit(EXIT_FAILURE); 
		}
		if((*start)!=0 && strcmp(temp->myIdx, (*myData)[(*start)-1].myIdx)==0){
			break;
		}
        memcpy((*myData)[*start].myIdx, temp->myIdx, ((*start)<10?2:3));
		size = recv(fd, temp->myStr, l, 0);
		if(size == -1) { 
			if(errno == ECONNRESET) printf("ECONNRESET\n");
			close(fd);
			perror("Receiver"); exit(EXIT_FAILURE); 
		}
        memcpy((*myData)[*start].myStr, temp->myStr, l);
		// connection_fd is marked as connected 
		// and it knows where the message should be directed
        printf("%s %s\n", (*myData)[*start].myIdx, (*myData)[*start].myStr);
		*start=*start+1;
		if(*start>=n){
			break;
		}
	}
	free(temp);
	close(fd);
}

void send_last_rand_str(struct myStruct* myData, int n, int l, int *start){
    struct sockaddr_un address;
	int fd, connected_fd;

	// Setting my domain
	address.sun_family = AF_UNIX;
	memcpy(address.sun_path, LOCAL, strlen(LOCAL) + 1); 

	// Make a socket file
	if((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){
		perror("Socket cannot be instantiated");
		exit(EXIT_FAILURE);
	}

	// Bind 
	// Naming the socket so other process can address it
	unlink(LOCAL);
	if(bind(fd, (struct sockaddr*) &address, sizeof(address)) == -1){
		perror("Cannot bind socket");
		exit(EXIT_FAILURE);
	}

	// Listen
	// Set the socket as passive for accepting connection
	// On the other side connect() will succeed immidiatly if
	// the queue is not full.
	if(listen(fd, PENDING_QUEUE_SIZE) == -1){
		perror("Cannot listen");
		exit(EXIT_FAILURE);
	}

	// Accept - blocking call
	// Wait for incoming communication request
	// Accepting a connection remove it from the pending requests,
	// therefore after accepting, 1 + PENDING_QUEUE_SIZE will succeed in connect()
	struct sockaddr_un agent; // The other process info
	socklen_t agent_length;
	memset(&agent, 0, sizeof(struct sockaddr_un));
	// printf("Waiting for incoming connection...\n");
	if((connected_fd = accept(fd,(struct sockaddr*) &agent, &agent_length))== -1){
		perror("Cannot accept connection");
		exit(EXIT_FAILURE);
	}
	// printf("Established connection with: %s\n", agent.sun_path); // it may show nothing because the socket is unbound

	// We could handle the response seperately in another thread
	// and continue accepting other requests. For purpose of clarity
	// I handle the request directly.
	// printf("Write a message: ");
	send(connected_fd, myData[(*start)-1].myIdx, ((*start)-1<10?2:3), 0);
	send(connected_fd, myData[(*start)-1].myStr, l, 0);
	// connection_fd is marked as connected 
	// and it knows where the message should be directed
	printf("%s\n", myData[(*start)-1].myIdx);
	// printf("%s %s\n", myData[(*start)-1].myIdx, myData[(*start)-1].myStr);

	// If client is blocking in recv(): ECONNRESET
	// If client is blocking in connect(): ECONNREFUSED
	close(connected_fd);
	close(fd); 
}

int main(int argc, const char* argv[]){
    int num_of_rand_str = 50;
    int len_of_rand_str = 6;

    struct myStruct *myData = (struct myStruct*) malloc(num_of_rand_str*sizeof(struct myStruct));
	
	for (int i = 0; i < num_of_rand_str; i++){
        myData[i].myStr = (char*) malloc((len_of_rand_str)*sizeof(char));
        myData[i].myIdx = (char*) malloc((i<10?2:3)*sizeof(char));
	}
	
	int start=0;
	while(start<num_of_rand_str){
        printf("Received data:\n");
		receive_t_rand_str(&myData, num_of_rand_str, len_of_rand_str, &start);
        printf("----------------\n");
		printf("Sent data:\n");
		send_last_rand_str(myData, num_of_rand_str, len_of_rand_str, &start);
        printf("----------------\n");
		sleep(1);
	}

    return 0;
}