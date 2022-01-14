#include<stdio.h>

void printArray(int arr[], int len){
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
};

void bubbleSort(int arr[], int len){
    int temp;
    int sorted;
    for (int i = 0; i < len-1; i++)
    {
        sorted = 1;
        for (int j = 0; j < len-1-i; j++)
        {
            if (arr[j]>arr[j+1])
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;   
                sorted = 0;
            }
            
        }
        if(sorted){
            // printf("Pass No. %d\n",i+1);
            return;
        }
    }
};

void selectionSort(int arr[], int len){
    int minIndex;
    int temp;
    for (int i = 0; i < len-1; i++)
    {
        minIndex = i;
        for (int j = i+1; j <= len-1; j++)
        {
            if (arr[j]<arr[minIndex])
            {
                minIndex = j;
            }
        }
        if(i!=minIndex){
            temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
    
};

int main(){
    int n;
    scanf("%d", &n);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    
    char ch;
    printf("Enter 'b' for bubble sort and 's' for selection sort: ");
    scanf(" %c", &ch);

    if(ch=='b'){
        bubbleSort(arr, n);
        printf("Sorted Array using bubble sort:\n");
        printArray(arr, n);
    }
    else if(ch=='s'){
        selectionSort(arr, n);
        printf("Sorted Array using selection sort:\n");
        printArray(arr, n);
    }
    else{
        printf("Invalid Input!");
    }

    return 0;
}