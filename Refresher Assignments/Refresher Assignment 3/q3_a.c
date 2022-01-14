#include<stdio.h>
#include<stdlib.h>

/*
         7
     3        10
   1   5    9   15
      4    8
*/

struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* head = NULL;

void setData(struct Node* this, int data){
    this->data = data;
};

void setPtr(struct Node* this, struct Node* l, struct Node* r){
    this->left = l;
    this->right = r;
};

struct Node* createNode(int data, struct Node* left, struct Node* right){
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->left = left;
    n->data = data;
    n->right = right;
    return n;
};

void inOrder(struct Node* n){
    if (n!=NULL){
        inOrder(n->left);
        printf("%d ", n->data);
        inOrder(n->right);
    }
};

void insertBST(struct Node* root, int key){
    struct Node* prev = NULL;
    while (root!=NULL)
    {
        if (root->data==key)
        {
            printf("Already Exists\n");
            return;
        }
        else if (root->data>key)
        {
            prev=root;
            root=root->left;
        }
        else
        {
            prev=root;
            root=root->right;
        }
    }
    struct Node* n = createNode(key, NULL, NULL);
    if (prev->data>key)
    {
        prev->left=n;
    }
    else{
        prev->right=n;
    }
};

struct Node* deleteBST(struct Node* root, int key){
    if(root==NULL){
        return root;
    }
    if(root->data>key){
        root->left = deleteBST(root->left, key);
    }
    else if(root->data<key){
        root->right = deleteBST(root->right, key);
    }
    else{
        if(root->left==NULL){
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right==NULL){
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        else{
            struct Node* temp = root->right;
            while(temp->left!=NULL){
                temp = temp->left;
            }
            root->data = temp->data;
            root->right = deleteBST(root->right, temp->data);
            return root;
        }
    }
    return root;
}

int main()
{
    struct Node* Root = createNode(7, NULL, NULL);
    struct Node* N1 = createNode(3, NULL, NULL);
    struct Node* N2 = createNode(10, NULL, NULL);
    struct Node* N3 = createNode(1, NULL, NULL);
    struct Node* N4 = createNode(5, NULL, NULL);
    struct Node* N5 = createNode(4, NULL, NULL);
    struct Node* N6 = createNode(9, NULL, NULL);
    struct Node* N7 = createNode(15, NULL, NULL);
    struct Node* N8 = createNode(8, NULL, NULL);

    setPtr(Root, N1, N2);
    setPtr(N1, N3, N4);
    setPtr(N4, N5, NULL);
    setPtr(N2, N6, N7);
    setPtr(N6, N8, NULL);
    insertBST(Root, 6);

    inOrder(Root);
    printf("\n");
    
    deleteBST(Root, 4);
    inOrder(Root);
    printf("\n");

    deleteBST(Root, 9);
    inOrder(Root);
    printf("\n");

    deleteBST(Root, 10);
    inOrder(Root);
    printf("\n");

    deleteBST(Root, 11);
    inOrder(Root);
    printf("\n");

    deleteBST(Root, 7);
    inOrder(Root);
    printf("\n");

    return 0;
}