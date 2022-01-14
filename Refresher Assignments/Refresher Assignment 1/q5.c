#include<stdio.h>

#define ull unsigned long long int 

void merge(ull A[], int low, int mid, int high, int n){
    int i=low;
    int j=mid+1;
    int k=low; 
    ull B[n]; 

    while (i<=mid && j<=high)
    {
        if (A[i]<=A[j])
        {
            B[k] = A[i];
            i++; 
            k++;
        }
        else
        {
            B[k] = A[j];
            j++; 
            k++;
        }
    }

    while (i<=mid)
    {
        B[k] = A[i];
        k++;
        i++; 
    }
    while (j<=high)
    {
        B[k] = A[j];
        j++; k++;
    }

    for (int i = low; i <= high; i++)
    {
        A[i] = B[i];
    }
};

void mergeSort(ull A[], int low, int high, int n){
    int mid;
    if (low<high)
    {
        mid = (low+high)/2;
        mergeSort(A, low, mid, n);
        mergeSort(A, mid+1, high, n);
        merge(A, low, mid, high, n);
    }  
};

int binarySearch(ull arr[], int n, ull num){
    int low = 0, high = n-1, mid = 0;
    while(low<=high){
        mid = low+(high-low)/2;
        if(arr[mid]==num){
            return mid;
        }
        else if(num>arr[mid]){
            low = mid+1;
        }
        else{
            high = mid-1;
        }
    }
    return -1;
}

int main(){
    int n;
    printf("Enter no of elements in the array:\n");
    scanf("%d", &n);

    ull arr[n];
    for (int i = 0; i < n; i++){
        scanf("%llu", &arr[i]);        
    }

    mergeSort(arr, 0, n-1, n);

    printf("Sorted array is as follows:\n");
    for (int i = 0; i < n; i++){
        printf("%llu ", arr[i]);
    }printf("\n");
    
    int q;
    printf("Enter no of queries:\n");
    scanf("%d", &q);

    while (q--)
    {
        ull num;
        scanf("%llu", &num);
        int v = binarySearch(arr, n, num);
        if(v==-1){
            printf("Element not found!\n");
        }
        else{
            printf("Found at index %d \n", v);
        }
    }

    return 0;
}