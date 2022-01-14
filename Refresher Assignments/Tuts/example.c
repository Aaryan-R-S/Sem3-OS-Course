#include<stdio.h>

const char *numbers[] = {
    "o", "t", "t", "f", "f", "s", "s", "e", "n", "t"
};

void say(int i){
    const char *msg = numbers[i-1];
    printf("%s\n", msg);
}

int main(){
    for (int i = 1; i <= 10; i++)
    {
        say(i);
    }
    return 0;
}