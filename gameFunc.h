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

void delay(int longtime)
{
    int ms = 1000*longtime;
    clock_t start = clock();
    while (clock() < start+ms)
        ;
}

void jumlah_iterasi(char arr[rows_game][cols_game], char future[rows_game][cols_game], int N)
{
    int times = 0;
    char temp;
    nextGeneration(arr, future);
    showArray(future);
    system("cls");
    delay(0.25);
    while (times<N-1)
    {
        for(int b = 0; b<rows_game; b++){
            for(int k = 0; k<cols_game; k++){
                temp = arr[b][k];
                arr[b][k] = future[b][k];
                future[b][k] = temp;
            }
        }
        nextGeneration(arr, future);
        showArray(future);
        system("cls");
        delay(0.25);
        times++;
    }
    showArray(future);
}