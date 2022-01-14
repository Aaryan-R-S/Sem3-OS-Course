#include<stdio.h>
#include<stdlib.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

struct Node{
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

void preorder(struct Node* n){
    if(n!=NULL){
        printf("%d ", n->key);
        preorder(n->left);
        preorder(n->right);
    }
}

void inorder(struct Node* n){
    if(n!=NULL){
        inorder(n->left);
        printf("%d ", n->key);
        inorder(n->right);
    }
}

int getHeight(struct Node* n){
    if(n==NULL){
        return 0;
    }
    return n->height;
}

int getBalance(struct Node* n){
    if(n==NULL){
        return 0;
    }
    return getHeight(n->right) - getHeight(n->left);
}

struct Node* RR(struct Node* y){
    struct Node* x = y->right;
    struct Node* t = x->left;

    // main rotations
    x->left = y;
    y->right = t;

    // reset height of changed pointers
    y->height = 1 + MAX(getHeight(y->left), getHeight(y->right));
    x->height = 1 + MAX(getHeight(x->left), getHeight(x->right));

    // return new parent
    return x;
}

struct Node* LL(struct Node* y){
    struct Node* x = y->left;
    struct Node* t = x->right;

    // main rotations
    x->right = y;
    y->left = t;

    // reset height of changed pointers
    y->height = 1 + MAX(getHeight(y->left), getHeight(y->right));
    x->height = 1 + MAX(getHeight(x->left), getHeight(x->right));

    // return new parent
    return x;
}

struct Node* balance(struct Node* n, int key){
    int balanceFactor = getBalance(n);
    // RR Case
    if(balanceFactor>1 && key > n->right->key){
        return RR(n);
    }
    // LL Case
    else if(balanceFactor<-1 && key < n->left->key){
        return LL(n);
    }
    // RL Case
    else if(balanceFactor>1 && key < n->right->key){
        n->right = LL(n->right);
        return RR(n);
    }
    // LR Case
    else if(balanceFactor<-1 && key > n->left->key){
        n->left = RR(n->left);
        return LL(n);
    }
    return n;
}

struct Node* insert(struct Node* n, int key){
    if(n==NULL){
        struct Node* t = (struct Node*)malloc(sizeof(struct Node));
        t->key = key;
        t->left = NULL;
        t->right = NULL;
        t->height = 1;
        return t;
    }
    else if(n->key > key){
        n->left = insert(n->left, key);
    }
    else if(n->key < key){
        n->right = insert(n->right, key);
    }
    else{
        return n;
    }
    n->height = 1 + MAX(getHeight(n->left), getHeight(n->right));
    return balance(n, key);
}

struct Node* balanceDel(struct Node* n){
    int balanceFactor = getBalance(n);
    int balanceLeft = getBalance(n->left);
    int balanceRight = getBalance(n->right);
    // RR Case
    if(balanceFactor>1 && balanceRight>=0){
        return RR(n);
    }
    // LL Case
    else if(balanceFactor<-1 && balanceLeft<=0){
        return LL(n);
    }
    // RL Case
    else if(balanceFactor>1 && balanceRight<0){
        n->right = LL(n->right);
        return RR(n);
    }
    // LR Case
    else if(balanceFactor<-1 && balanceLeft>0){
        n->left = RR(n->left);
        return LL(n);
    }
    return n;
}

struct Node* deleteNode(struct Node* n, int key){
    if(n==NULL){
        return n;
    }
    else if(key > n->key){
        n->right = deleteNode(n->right, key);
    }
    else if(key < n->key){
        n->left = deleteNode(n->left, key);
    }
    else{
        if(n->left==NULL || n->right==NULL){
            struct Node* t = (n->right!=NULL) ? n->right : n->left;
            if(t==NULL){
                t = n;
                n = NULL;
            }
            else{
                *n = *t;    // copy the values from t to n
            }
            free(t);     // free n or t
        }
        else{
            struct Node* t = n->right;
            while (t->left!=NULL)
            {
                t = t->left;
            }
            n->key = t->key;
            n->right = deleteNode(n->right, t->key);
        }
    }
    if(n==NULL){
        return n;
    }
    n->height = 1 + MAX(getHeight(n->left), getHeight(n->right));

    return balanceDel(n);
}

int main()
{
    struct Node *root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    preorder(root); // 30 20 10 25 40 50 
    printf("\n");
    inorder(root);  // 10 20 25 30 40 50 
    printf("\n");

    root = deleteNode(root, 40);
    root = deleteNode(root, 50);
    preorder(root); // 20 10 30 25 
    printf("\n");
    inorder(root);  // 10 20 25 30
    printf("\n");
    root = deleteNode(root, 10);
    preorder(root); // 25 20 30 
    printf("\n");
    inorder(root);  // 20 25 30
    printf("\n");
    root = deleteNode(root, 200);
    root = deleteNode(root, 25);
    root = deleteNode(root, 20);
    root = deleteNode(root, 30);
    preorder(root); // 
    printf("\n");
    inorder(root);  // 
    printf("\n");

    return 0;
}