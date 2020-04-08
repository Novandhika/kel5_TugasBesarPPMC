#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void showArray (char *arr, int r, int c)
{
    int i, j;
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            printf("%c", *((arr+i*c)+j));
        }
        printf("\n");
    }
}

void fillArray(char *arr, FILE *f, int i, int j)
{
    int count_row = -1, count_col = 0;
    char ch;
    while ((ch = fgetc(f)) != '#') {
        if (ch != '\n') {
            *((arr+count_row*j)+count_col)= ch;
            count_col++;
        }
        else {
            count_col = 0;
            count_row++;
        }
    }
}
int main()
{
    FILE *fp;
    int column, row;

    //opening file
    fp = fopen("1.txt", "r");

    //dapatkan nilai MxN untuk multi dimensional array
    fscanf(fp, "%d", &row);
    fscanf(fp, "%d", &column);

    //inisialisasi array penyimpanan life component
    char charArr[row][column];
    char *ptr = &charArr[0][0];
    fillArray(ptr, fp, row, column);
    showArray(ptr, row, column);
    free(ptr);
}

