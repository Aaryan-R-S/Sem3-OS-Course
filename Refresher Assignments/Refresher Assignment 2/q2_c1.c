#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
    int data;
    struct Node *next;
};

struct Node* head = NULL;

void printLL(struct Node* n){
    while(n->next!=NULL){
        n = n->next;
    }
    printf("%d \n", n->data);
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

void deleteFromEndLL(struct Node* p){
    if(p->next==NULL){
        head = NULL;
        free(p);
        return;
    }
    struct Node* t = p->next;
    while(t->next!=NULL){
        p = p->next;
        t = t->next;
    }
    p->next = NULL;
    free(t);
}

void printStackTop(struct Node* n){
    if(head==NULL){
        printf("Stack is empty!\n");
    }
    else{
        printLL(n);
    }
}

void push(struct Node* p){
    insertAtEndLL(p);
}

void pop(struct Node* p){
    if(head==NULL){
        printf("Stack is already empty!\n");
    }
    else{
        deleteFromEndLL(p);
    }
}

int main(){
    int q;
    printf("Enter the number of queries:\n");
    scanf("%d", &q);

    while(q--){
        char ch;
        printf("Enter 'p' for push operation, 'd' for pop operation and 's' for printing the stack top:\n");
        scanf(" %c", &ch);
        if(ch=='p'){
            push(head);
        }
        else if(ch=='d'){
            pop(head);
        }
        else if(ch=='s'){
            printStackTop(head);
        }
        else{
            printf("Invalid Input!\n");
        }
    }

    return 0;
}