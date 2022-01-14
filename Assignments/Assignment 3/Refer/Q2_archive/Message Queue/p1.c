#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<sys/msg.h>

#define KEY 0x01
#define KEY_REV 0x02

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

struct myMessage {
	long type;
	int idx;
	char msg[6];
};

struct myStruct{
    int myIdx;
    char* myStr;
};

void generate_n_rand_str(struct myStruct** myData, int n, int l){
    srand(time(NULL));
    *myData = (struct myStruct*) malloc(n*sizeof(struct myStruct));
    int curr = 0;
    while(curr<n){
        (*myData)[curr].myStr = (char*) malloc((l)*sizeof(char));
        (*myData)[curr].myIdx = curr;
        // int_to_char(curr, &(*myData)[curr].myIdx);

        for(int i = 0; i <= l-2; i++){
            (*myData)[curr].myStr[i] = 33 + rand()%62;
        }
        (*myData)[curr].myStr[l-1] = '\0';
        curr++;
    }
}

int getMessageQueue(char id){
	key_t queue_key = ftok(".", id);
	// printf("Queue key: %X\n", queue_key);
	int queue_id;
	if((queue_id = msgget(queue_key, IPC_CREAT | 0660)) == -1){
		perror("Cannot retrive queue");
		exit(EXIT_FAILURE);
	}
	return queue_id;
}

void removeEmptyQueue(int queue_id){
	struct msqid_ds info;

	if(msgctl(queue_id, IPC_STAT, &info) == -1){
		perror("Cannot retrieve information about the message queue");
		exit(EXIT_FAILURE);
	}

	if(info.msg_qnum == 0){
		if(msgctl(queue_id, IPC_RMID, NULL) == -1){
			perror("Cannot remove the message queue");
			exit(EXIT_FAILURE);
		}
	}
	// printf("Message queue removed\n");
	return;
}

void send_t_rand_str(struct myStruct* myData, int n, int l, int t, int* start){
	int queue_id = getMessageQueue(KEY);

    for(int i=*start; i<MIN(*start+t,n); i++){
        struct myMessage m1;
        m1.type = 1;
        m1.idx = myData[i].myIdx;
        memcpy(m1.msg, myData[i].myStr, l);

        // Enqueue the message
        if(msgsnd(queue_id, &m1, sizeof(struct myMessage)-sizeof(long), 0) == -1){
            perror("Cannot send message");
            exit(EXIT_FAILURE);
        }
        printf("%d %s\n", myData[i].myIdx, myData[i].myStr);
    }
}

int receive_last_rand_str(struct myStruct** myData, int n, int l, int *start){
    int queue_id = getMessageQueue(KEY_REV);
	struct myMessage m1;

	int type = 0;
	if(msgrcv(queue_id, &m1, sizeof(struct myMessage)-sizeof(long), type, 0) == -1){
		perror("Cannot receive message");
		exit(EXIT_FAILURE);
	}
	printf("%d %s\n", m1.idx, m1.msg);
    removeEmptyQueue(queue_id);
    return m1.idx;
}

int main(int argc, const char* argv[]){
    struct myStruct* myData;
    int num_of_rand_str = 50;
    int len_of_rand_str = 6;
    generate_n_rand_str(&myData, num_of_rand_str, len_of_rand_str) ;
    // printf("ok\n");
    // for(int i=0; i<num_of_rand_str; i++){
    //     printf("%d %s\n", myData[i].myIdx, myData[i].myStr);
    // }
    // printf("ok\n");

    int start = 0;
    while(start<num_of_rand_str){
        printf("Sent data:\n");
        send_t_rand_str(myData, num_of_rand_str, len_of_rand_str, 5, &start);
        printf("----------------\n");
        printf("Received data:\n");
        start = receive_last_rand_str(&myData, num_of_rand_str, len_of_rand_str, &start)+1;
        printf("----------------\n");
    }

    return 0;
}