#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
    char name[50];
    int rollno;
    int yearOfJoin;
    char acadProgram[50];
    struct Node *prev;
    struct Node *next;
};

struct Node* head = NULL;

void printList(struct Node* n){
    while(n!=NULL){
        printf("Name: %s | Roll: %d | Year of join: %d | Academic Program: %s\n", n->name, n->rollno, n->yearOfJoin, n->acadProgram);
        n = n->next;
    }
}

void insertLL(struct Node* p){
    struct Node* n = malloc(sizeof(struct Node));

    printf("Enter name:\n");
    scanf(" %s", &(n->name));
    printf("Enter roll no:\n");
    scanf(" %d", &(n->rollno));
    printf("Enter year of joining:\n");
    scanf(" %d", &(n->yearOfJoin));
    printf("Enter enrolled academic program:\n");
    scanf(" %s", &(n->acadProgram));
    n->prev = NULL;
    n->next = NULL;

    if(p==NULL){
        head = n;
        return;
    }
    while(p->next!=NULL){
        p=p->next;
    }
    p->next = n;
    n->prev = p;
    return;
}

void searchLL(struct Node* p, char name[]){
    while(p!=NULL){
        if(strcmp(name, p->name)==0){
            printf("Entry of %s is PRESENT in the list\n", name);
            printf("Name: %s | Roll: %d | Year of join: %d | Academic Program: %s\n", p->name, p->rollno, p->yearOfJoin, p->acadProgram);
            return;
        }
        p = p->next;
    }
    printf("Entry of %s is NOT PRESENT in the list\n", name);
}

int main(){
    int students;
    printf("Enter the number of students:\n");
    scanf("%d", &students);

    while(students--){
        insertLL(head);
        printList(head);
    }

    int q;
    printf("Enter the number of queries:\n");
    scanf("%d", &q);

    while(q--){
        char ch;
        printf("Enter 'p' for printing the list of students and 's' for searching a student:\n");
        scanf(" %c", &ch);
        if(ch=='p'){
            printList(head);
        }
        else if(ch=='s'){
            char nam[50];
            printf("Enter the name of student to search:\n");
            scanf(" %s", &nam);
            searchLL(head, nam);
        }
        else{
            printf("Invalid Input!\n");
        }
    }

    return 0;
}