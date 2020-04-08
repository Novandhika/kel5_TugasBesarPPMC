#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int rows_game, cols_game;
void showArray (char arr[rows_game][cols_game])
{
    int i, j;
    for (i = 0; i < rows_game; i++)
    {
        for (j = 0; j < cols_game; j++)
        {
            printf("%c", arr[i][j]);//*((arr+i*cols_game)+j));
        }
        printf("\n");
    }
    printf("\n");
}

void fillArray(char arr[rows_game][cols_game], FILE *f)
{
    int count_row = -1, count_col = 0;
    char ch;
    while ((ch = fgetc(f)) != '#') {
        if (ch != '\n') {
            arr[count_row][count_col] = ch;
            count_col++;
        }
        else {
            count_col = 0;
            count_row++;
        }
    }
}

int cellNeighbors(char arr[rows_game][cols_game], int row_cell, int col_cell)
{
    int i, j;
    int count_alive = 0;
    int count_death = 0;
    for(i = row_cell-1; i<=row_cell+1; i++)
    {
        for(j = col_cell-1; j<=col_cell+1; j++)
        {
            if(arr[i][j] == 'X'){
                count_alive++;
            }else{
                count_death++;
            }
        }
    }
    return count_alive;
}

void nextGeneration(char arr[rows_game][cols_game], char future[rows_game][cols_game])
{
    int i, j;
    for (i = 0; i < rows_game; i++)
    {
        for (j = 0; j < cols_game; j++)
        {
            if((arr[i][j] == 'X')&&((cellNeighbors(arr,i,j)-1) < 2)){
                future[i][j] = '-';
            }else if((arr[i][j] == 'X')&&(((cellNeighbors(arr,i,j)-1) == 2)||((cellNeighbors(arr,i,j)-1) == 3))){
                future[i][j] = 'X';
            }else if((arr[i][j] == 'X')&&((cellNeighbors(arr,i,j)-1) > 3)){
                future[i][j] = '-';
            }else if((arr[i][j] == '-')&&(cellNeighbors(arr,i,j) == 3)){
                future[i][j] = 'X';
            }else{
                future[i][j] = arr[i][j];
            }
        }
    }
}

bool lanjut_iterasi(char arr1[rows_game][cols_game], char arr2[rows_game][cols_game])
{
    for(int i = 0; i<rows_game;i++){
        for(int j = 0; j<cols_game;j++)
        {
            if (arr1[i][j]==arr2[i][j]){
                return false;
            }else{
                return true;
            }
        }
    }
}

int main()
{
    FILE *fp;
    char ch;
    char filename[100];
    int i = 0, arrayInfo[2] = {0};
    int column, row;
    int b,k;

    //opening file
    printf("Masukkan nama file: ");
    gets(filename);
    fp = fopen(filename, "r");

    //dapatkan nilai MxN untuk multi dimensional array
    fscanf(fp, "%d", &row);
    fscanf(fp, "%d", &column);

    rows_game = row;
    cols_game = column;

    //inisialisasi array penyimpanan life component
    char MultiArray[rows_game][cols_game];
    char nextArray[rows_game][cols_game];
    char temp;

    fillArray(MultiArray, fp);
    showArray(MultiArray);
    nextGeneration(MultiArray, nextArray);
    showArray(nextArray);
    while(!lanjut_iterasi(MultiArray,nextArray)){
        for(int b = 0; b<rows_game; b++){
            for(int k = 0; k<cols_game; k++){
                temp = MultiArray[b][k];
                MultiArray[b][k] = nextArray[b][k];
                nextArray[b][k] = temp;
            }
        }
        nextGeneration(MultiArray, nextArray);
        showArray(nextArray);
    }
    return 0;
}