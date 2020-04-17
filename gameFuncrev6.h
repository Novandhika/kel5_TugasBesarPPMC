/* EL2208 Praktikum Pemecahan Masalah dengan C 2019/2020  
* MODUL 9 – TUGAS BESAR  
* Kelompok          : 5  
* Hari dan Tanggal  : Jumat, 17 April 2020  
* Asisten (NIM)     : Rizky Ardi Maulana (13217054)   
* Nama File         : gameFuncFINAL.h  
* Deskripsi         : Fungsi yang dibutuhkan dalam Game Of Life  
*/

int rows_game, cols_game;

void showArray (char **arr)
{
    int i, j;
    for (i = 0; i < rows_game; i++)
    {
        for (j = 0; j < cols_game; j++)
        {
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void fillArray(char **arr, FILE *f)
{
    int count_row = -1, count_col = 0;
    char ch;
    while (((ch = fgetc(f)) != '#')&&(count_row < rows_game)) {
        if (ch != '\n') {
            arr[count_row][count_col] = ch;
            count_col++;
        }
        else {
            count_col = 0;
            count_row++;
        }
    }
    fclose(f);
}

int cellNeighbors(char **arr, int row_cell, int col_cell)
{
    int i, j;
    int count_alive = 0;
    int count_death = 0;

    //Menghitung sel tetangga hidup dan mati
    for(i = -1; i<2; i++)
    {
        for(j = -1; j<2; j++)
        {
            int row = (row_cell + i + rows_game) % rows_game;
            int col = (col_cell + j + cols_game) % cols_game;
            if(arr[row][col] == 'X'){
                count_alive++;
            }else{
                count_death++;
            }
        }
    }
    return count_alive;
}

void nextGeneration(char **arr, char **future)
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

int lanjut_iterasi(char **arr1, char **arr2)
{
    int isEqual = 1;
    for(int i = 0; i<rows_game;i++){
        for(int j = 0; j<cols_game;j++)
        {
            if (arr2[i][j]!=arr1[i][j]){
                isEqual = 0;
                break;
            };
        };
    };
    return isEqual;
};

void delay(int longtime)
{
    int ms = 1000*longtime;
    clock_t start = clock();
    while (clock() < start+ms)
        ;
};

void jumlah_iterasi(char **arr, char **future, int N)
{
    int times = 0;
    char temp;
    nextGeneration(arr, future);
    showArray(future);
    system("cls");
    delay(0.25);
    while (times<N)
    {
        for(int b = 0; b<rows_game; b++){
            for(int k = 0; k<cols_game; k++){
                temp = arr[b][k];
                arr[b][k] = future[b][k];
                future[b][k] = temp;
            };
        };
        nextGeneration(arr, future);
        showArray(future);
        system("cls");
        delay(0.25);
        times++;
    };
    showArray(arr);
};
