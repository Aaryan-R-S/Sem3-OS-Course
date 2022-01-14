#include<stdio.h>

void swap(char* a, char* b){
    char c = *a;
    *a = *b;
    *b = c;
}

void reverseStr(char str[]){
    int n = 0;
    while (str[n]!='\0'){
        n++;
    }
    
    for (int i = 0; i < n/2; i++)
    {
        swap(&str[i], &str[n-i-1]);
    }
}

int main(){
    char str[1000];
    printf("Enter the string:\n");
    scanf("%[^\n]s", &str);

    printf("String before reversing = %s\n", str);

    reverseStr(str);
    printf("String after reversing = %s\n", str);

    return 0;
}