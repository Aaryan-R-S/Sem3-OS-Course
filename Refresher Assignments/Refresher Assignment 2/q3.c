#include<stdio.h>

void add(int a, int b){
    printf("%d+%d = %d\n", a, b, a+b);
}

void sub(int a, int b){
    printf("%d-%d = %d\n", a, b, a-b);
}

void mul(int a, int b){
    printf("%d*%d = %d\n", a, b, a*b);
}

void div(int a, int b){
    if(b!=0){
        printf("%d/%d = %f\n", a, b, (float)a/b);
    }
    else{
        printf("%d/%d = UNDEFINED", a, b);
    }
}

void expo(int a, int b){
    int ans = 1;
    for (int i = 0; i < b; i++)
    {
        ans = ans*a;
    }
    printf("%d^%d = %d\n", a, b, ans);
}

int main(){
    void (*arr[]) (int, int) = {add, sub, mul, div, expo};

    int q;
    printf("Enter no of queries:\n");
    scanf("%d", &q);

    while (q--)
    {
        int a, b;
        printf("Enter a:\n");
        scanf("%d", &a);
        printf("Enter b:\n");
        scanf("%d", &b);

        int ch;
        printf("Enter '0' for add, '1' for subtract, '2' for multplication, '3' for division and '4' for exponentiation operation:\n");
        scanf("%d", &ch);

        if(ch>4 || ch<0){
            printf("Invalid input!\n");
        }
        else{
            (*arr[ch])(a,b);
        }
    }
    

    return 0;
}