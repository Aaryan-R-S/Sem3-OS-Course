#include<stdio.h>

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapArr(int a[], int b[], int n){
    for (int i = 0; i < n; i++)
    {
        swap(&a[i], &b[i]);
    }
}

int main(){
    int d = 3, j = -23;
    printf("Vars before swap d=%d j=%d \n", d, j);
    swap(&d, &j);
    printf("Vars after swap d=%d j=%d \n", d, j);

    int n;
    printf("Enter no of elements in the arrays:\n");
    scanf("%d", &n);
    int arr1[n], arr2[n];

    for (int i = 0; i < n; i++){
        scanf("%d", &arr1[i]);
    }

    for (int i = 0; i < n; i++){
        scanf("%d", &arr2[i]);
    }

    swapArr(arr1, arr2, n);

    printf("Arrays after swapping\n");

    for (int i = 0; i < n; i++){
        printf("%d ", arr1[i]);
    }printf("\n");

    for (int i = 0; i < n; i++){
        printf("%d ", arr2[i]);
    }printf("\n");
    
    return 0;
}