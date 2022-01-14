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
#define LOCAL       "./sockP1"
#define DESTINATION "./sockP2" 

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

struct myStruct{
    char* myIdx;
    char* myStr;
};

void int_to_char(int curr, char **ptr){
    if(curr>=10){
        (*ptr)[0] = '0'+curr/10;
        (*ptr)[1] = '0'+curr%10;
        (*ptr)[2] ='\0';
    }
    else{
        (*ptr)[0] = '0'+curr;
        (*ptr)[1] = '\0';
    }
}

int char_to_int(char** ptr){
    int ans=0;
    int i = 0;
    while((*ptr)[i]!='\0'){
        ans *= 10;
        ans += (int)((*ptr)[i]-'0');
        i++;
    }
    return ans;
}

void generate_n_rand_str(struct myStruct** myData, int n, int l){
    srand(time(NULL));
    *myData = (struct myStruct*) malloc(n*sizeof(struct myStruct));
    int curr = 0;
    while(curr<n){
        (*myData)[curr].myStr = (char*) malloc((l)*sizeof(char));
        (*myData)[curr].myIdx = (char*) malloc((curr<10?2:3)*sizeof(char));
        int_to_char(curr, &(*myData)[curr].myIdx);

        for(int i = 0; i <= l-2; i++){
            (*myData)[curr].myStr[i] = 33 + rand()%62;
        }
        (*myData)[curr].myStr[l-1] = '\0';
        curr++;
    }
}

void send_t_rand_str(struct myStruct* myData, int n, int l, int t, int* start){
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
    for(int i=*start; i<MIN(*start+t,n); i++){
		// printf("Write a message: ");
		send(connected_fd, myData[i].myIdx, (i<10?2:3), 0);
		send(connected_fd, myData[i].myStr, l, 0);
		// connection_fd is marked as connected 
		// and it knows where the message should be directed
        printf("%s %s\n", myData[i].myIdx, myData[i].myStr);
    }

	// If client is blocking in recv(): ECONNRESET
	// If client is blocking in connect(): ECONNREFUSED
	close(connected_fd);
	close(fd); 
}

int receive_last_rand_str(struct myStruct** myData, int n, int l, int *start){
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
    // printf("Write a message: ");
    size = recv(fd, temp->myIdx, ((*start)<10?2:3), 0);
    if(size == -1) { 
        if(errno == ECONNRESET) printf("ECONNRESET\n");
        close(fd);
        perror("Receiver"); exit(EXIT_FAILURE); 
    }
    size = recv(fd, temp->myStr, l, 0);
    if(size == -1) { 
        if(errno == ECONNRESET) printf("ECONNRESET\n");
        close(fd);
        perror("Receiver"); exit(EXIT_FAILURE); 
    }
    // connection_fd is marked as connected 
    // and it knows where the message should be directed
    printf("%s\n", temp->myIdx);
    // printf("%s %s\n", temp->myIdx, temp->myStr);

    int r_val = char_to_int(&temp->myIdx);
	free(temp);
	close(fd);
    return r_val;
}

int main(int argc, const char* argv[]){
    struct myStruct* myData;
    int num_of_rand_str = 50;
    int len_of_rand_str = 6;
    generate_n_rand_str(&myData, num_of_rand_str, len_of_rand_str) ;
    // printf("ok\n");
    // for(int i=0; i<num_of_rand_str; i++){
    //     printf("%s %s\n", myData[i].myIdx, myData[i].myStr);
    // }
    // printf("ok\n");

    int start = 0;
    while(start<num_of_rand_str){
        printf("Sent data:\n");
        send_t_rand_str(myData, num_of_rand_str, len_of_rand_str, 5, &start);
        printf("----------------\n");
        sleep(1);
        printf("Received data:\n");
        start = receive_last_rand_str(&myData, num_of_rand_str, len_of_rand_str, &start)+1;
        printf("----------------\n");
    }

    return 0;
}