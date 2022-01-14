#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
    int data;
    struct Node *next;
};

struct Node* head = NULL;

void printLL(struct Node* n){
    while(n!=NULL){
        printf("%d ", n->data);
        n = n->next;
    }
    printf("\n");
}

void insertAtEndLL(struct Node* p){
    struct Node* n = malloc(sizeof(struct Node));

    printf("Enter unique key:\n");
    scanf(" %d", &(n->data));
    n->next = NULL;

    if(p==NULL){
        head = n;
        return;
    }
    while(p->next!=NULL){
        p=p->next;
    }
    p->next = n;
    return;
}

void deleteFromStartLL(struct Node* p){
    if(p->next==NULL){
        head = NULL;
        free(p);
        return;
    }
    struct Node* t = p->next;
    head = t;
    free(p);
}

void printQueue(struct Node* n){
    if(head==NULL){
        printf("Queue is empty!\n");
    }
    else{
        printLL(n);
    }
}

void enqueue(struct Node* p){
    insertAtEndLL(p);
}

void dequeue(struct Node* p){
    if(head==NULL){
        printf("Queue is already empty!\n");
    }
    else{
        deleteFromStartLL(p);
    }
}

int main(){
    int q;
    printf("Enter the number of queries:\n");
    scanf("%d", &q);

    while(q--){
        char ch;
        printf("Enter 'p' for enqueue operation, 'd' for dequeue operation and 's' for printing the queue:\n");
        scanf(" %c", &ch);
        if(ch=='p'){
            enqueue(head);
        }
        else if(ch=='d'){
            dequeue(head);
        }
        else if(ch=='s'){
            printQueue(head);
        }
        else{
            printf("Invalid Input!\n");
        }
    }

    return 0;
}