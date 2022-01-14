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

void changeMatrix(int** ptr, int col_in_rows[], int rows, int r, int c){
    int temp = col_in_rows[r-1];
    col_in_rows[r-1] = c;

    ptr[r-1] = realloc(ptr[r-1], col_in_rows[r-1]*sizeof(int));
    
    if(temp<c){
        for (int i = temp; i < c; i++)
        {
            ptr[r-1][i] = (rand()%10) + 1;
        }
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
    printf("[Matrix created] \n");

    populateMatrix(ptr, col_in_rows, rows);
    printf("[Matrix populated with random numbers] \n");
    
    displayMatrix(ptr, col_in_rows, rows);
    printf("[Matrix displayed] \n");

    int q;
    printf("Enter the number of queries:\n");
    scanf("%d", &q);

    while(q--){
        int r;
        printf("Enter the row number whose no of columns you want to change (1-6):\n");
        scanf("%d", &r);

        if(r<1 || r>6){
            printf("Invalid row number!\n");
            continue;
        }

        int c;
        printf("Enter the number of columns you want to have in the row %d (currently %d columns):\n", r, col_in_rows[r-1]);
        scanf("%d", &c);

        changeMatrix(ptr, col_in_rows, rows, r, c);
        
        displayMatrix(ptr, col_in_rows, rows);
        printf("[Matrix displayed] \n");
    }

    return 0;
}