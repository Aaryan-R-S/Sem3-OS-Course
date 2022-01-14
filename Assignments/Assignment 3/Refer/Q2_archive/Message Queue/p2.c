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

struct myMessage {
	long type;
	int idx;
	char msg[6];
};

struct myStruct{
    int myIdx;
    char* myStr;
};

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

void receive_t_rand_str(struct myStruct** myData, int n, int l, int* start){
	int queue_id = getMessageQueue(KEY);
	struct myMessage m1;

	struct msqid_ds info;
	if(msgctl(queue_id, IPC_STAT, &info) == -1){
		perror("Cannot retrieve information about the message queue");
		exit(EXIT_FAILURE);
	}

	// Dequeue the message
	// type=0: the oldest message in the queue
	// type=n: the oldest message with type == n
	int type = 0;
	while(info.msg_qnum!=0){
		if(msgrcv(queue_id, &m1, sizeof(struct myMessage)-sizeof(long), type, 0) == -1){
			perror("Cannot receive message");
			exit(EXIT_FAILURE);
		}
		(*myData)[*start].myIdx = m1.idx;
		memcpy((*myData)[*start].myStr, m1.msg, l);

		printf("%d %s\n", (*myData)[*start].myIdx, (*myData)[*start].myStr);

		*start=*start+1;
		if(*start>=n){
			break;
		}
		if(msgctl(queue_id, IPC_STAT, &info) == -1){
			perror("Cannot retrieve information about the message queue");
			exit(EXIT_FAILURE);
		}
	}
	removeEmptyQueue(queue_id);
}

void send_last_rand_str(struct myStruct* myData, int n, int l, int *start){
	int queue_id = getMessageQueue(KEY_REV);

	struct myMessage m1;
	m1.type = 1;
	m1.idx = myData[*start-1].myIdx;
	memcpy(m1.msg, myData[*start-1].myStr, l);

	// Enqueue the message
	if(msgsnd(queue_id, &m1, sizeof(struct myMessage)-sizeof(long), 0) == -1){
		perror("Cannot send message");
		exit(EXIT_FAILURE);
	}
    printf("%d %s\n", myData[*start-1].myIdx, myData[*start-1].myStr);
}

int main(int argc, const char* argv[]){
    int num_of_rand_str = 50;
    int len_of_rand_str = 6;

    struct myStruct *myData = (struct myStruct*) malloc(num_of_rand_str*sizeof(struct myStruct));
	
	for (int i = 0; i < num_of_rand_str; i++){
        myData[i].myStr = (char*) malloc((len_of_rand_str)*sizeof(char));
	}
	
	int start=0;
	while(start<num_of_rand_str){
        printf("Received data:\n");
		receive_t_rand_str(&myData, num_of_rand_str, len_of_rand_str, &start);
        printf("----------------\n");
		printf("Sent data:\n");
		send_last_rand_str(myData, num_of_rand_str, len_of_rand_str, &start);
        printf("----------------\n");
		sleep(2);
	}

    return 0;
}