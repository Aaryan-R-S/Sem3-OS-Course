#include<stdio.h>
#include <stdlib.h>
#include<time.h>

void createMatrix(int** ptr, int col_in_rows[], int rows){
    for (int i = 0; i < rows; i++)
    {
        ptr[i] = (int*)malloc(col_in_rows[i]*sizeof(int));
    }
    return;
}

void populateMatrix(int** ptr, int col_in_rows[], int rows){
    srand(time(0));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < col_in_rows[i]; j++)
        {
            ptr[i][j] = (rand()%10) + 1;
        }
    }
    return;
}

void displayMatrix(int** ptr, int col_in_rows[], int rows){
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < col_in_rows[i]; j++)
        {
            printf("%d ", ptr[i][j]);
        }
        printf("\n");
    }
    return;
}

int main(){
    int rows = 6;
    int col_in_rows[] = {7,4,6,3,7,2}; 

    int** ptr = (int**)malloc(rows*sizeof(int*));

    createMatrix(ptr, col_in_rows, rows);
    printf("Matrix created...\n");

    populateMatrix(ptr, col_in_rows, rows);
    printf("Matrix populated with random numbers... \n");
    
    displayMatrix(ptr, col_in_rows, rows);
    printf("Matrix displayed... \n");

    return 0;
}