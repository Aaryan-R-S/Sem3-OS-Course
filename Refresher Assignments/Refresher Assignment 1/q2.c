#include<stdio.h>
#include<string.h>

// Store a 256-bit unsigned integer number on a 32 byte character array. Add two such
// 256-bit numbers and print the result.

void printAns(char arr[], int n){
    int k = 0;
    for (int i = 0; i < n; i++){
        if(arr[i]!=0){
            break;
        }
        k++;
    }
    if(k==n){
        printf("0");
    }
    else{
        for (int i = k; i < n; i++){
            printf("%d", (int)arr[i]);
        }
    }
    printf("\n");
}

void printArr(char arr[], int n){
    for (int i = 0; i < n; i++){
        if(arr[i]<0){
            printf("%d ", 256+(int)arr[i]);
        }
        else{
            printf("%d ", (int)arr[i]);
        }
    }
    printf("ok\n");
}

void divArr(char temp_100[], int n){
    char temp_100_temp[n];
    for (int i = 0; i < n; i++)
    {
        temp_100_temp[i] = 0;
    }

    int rem = 0;
    for (int i = 0; i < n; i++)
    {
        temp_100_temp[i] = (rem+(int)temp_100[i])/2;
        rem = 10*((rem+(int)temp_100[i])%2);
    }
    
    for (int j = 0; j < n; j++)
    {
        temp_100[j] = temp_100_temp[j];
    }
    
}

void setCharArr(char set_32[], char num_100[]){
    char set_256[256];
    int n = strlen(num_100);
    char temp_100[n];
    for (int i = 0; i < n; i++)
    {
        temp_100[i] = (int)num_100[i]-(int)'0';
    }
    for (int i = 0; i < 32; i++)
    {
        set_32[i] = 0;
    }
    for (int i = 0; i < 256; i++)
    {
        set_256[i] = 0;
    }
    int j = 0;
    // printArr(temp_100, n);
    while(j!=256){
        set_256[255-j] = ((int)temp_100[n-1]%2 == 0 ? 0:1 );
        divArr(temp_100, n);
        // printArr(temp_100, n);
        j++;
    }
    // printArr(set_256, 256);
    for (int i = 0; i < 32; i++)
    {
        int te = 0;
        for (int ii = 0; ii < 8; ii++)
        {
            te = te*2 + (int)set_256[8*i+ii];
        }
        set_32[i] = te;
    }
    
}

void addCharArr(char num1[], char num2[], char ans[]){
    int c=0, pc=0;
    for (int i = 0; i < 32; i++)
    {
        ans[i] = 0;
    }
    for (int i = 31; i >= 0; i--)
    {
        c = 0;
        int op1 = (int)num1[i];
        int op2 = (int)num2[i];
        if(op1<0){
            op1 = op1+256;
        }
        if(op2<0){
            op2 = op2+256;
        }
        ans[i] = (op1 + op2 + pc)%256;
        if((op1 + op2 + pc) > 255){
            c = 1;
        }
        pc = c;
    }
}

void calPow(char a[]){
    int c = 0, pc = 0;
    for (int i = 99; i >= 0; i--)
    {
        c = 0;
        int op = (int)a[i];
        a[i] = (op*2 + pc)%10;
        c = (op*2 + pc)/10;
        pc = c;
    }
    
}

void addArr(char a[], char powOfa[]){
    int c = 0, pc = 0; 
    for (int i = 99; i >= 0; i--)
    {
        c = 0;
        int op = (int)a[i] + (int)powOfa[i] + pc;
        a[i] = op%10;
        c = op/10;
        pc = c;
    }
    
}

void interpretCharArr(char a_32[], char a[]){
    char powOfa[100];
    for (int i = 0; i < 100; i++)
    {
        a[i] = 0;
        powOfa[i] = 0;
    }
    powOfa[99] = 1;
    for (int i = 31; i >= 0; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            if(((a_32[i]+256)%256)&(1<<j)){
                addArr(a, powOfa);
            }
            calPow(powOfa);
        }
    }

}

int main(){
    char m_char[32];
    char n_char[32];
    char a_char[32];
    char m[100];
    char n[100];
    char a[100];

    printf("Enter num 1: ");
    scanf("%s", &m);

    printf("Enter num 2: ");
    scanf("%s", &n);

    setCharArr(m_char, m);
    // printArr(m_char, 32);

    setCharArr(n_char, n);
    // printArr(n_char, 32);

    addCharArr(m_char, n_char, a_char);
    // printArr(a_char, 32);

    printf("Sum num 1 + num 2 = ");
    interpretCharArr(a_char, a);
    printAns(a, 100);

    return 0;
}