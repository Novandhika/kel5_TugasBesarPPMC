/* EL2208 Praktikum Pemecahan Masalah dengan C 2019/2020  
* MODUL 9 – TUGAS BESAR  
* Kelompok          : 5  
* Hari dan Tanggal  : Jumat, 10 April 2020  
* Asisten (NIM)     : Rizky Ardi Maulana (13217054)   
* Nama File         : gameFunc.h  
* Deskripsi         : Fungsi yang dibutuhkan dalam Game Of Life  
*/

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

//Belum toroidal
int cellNeighbors(char arr[rows_game][cols_game], int row_cell, int col_cell)
{
    int i, j;
    int count_alive = 0;
    int count_death = 0;
    
    /* Fungsi toroidal harusnya sudah benar, hanya salah tempat 
    //Mengisi baris ke -1 dengan baris terakhir (array toroidal)
    for(j=0;j<cols_game;j++)
	{
		arr[-1][j] = arr[(rows_game)-1][j];
	}; 
	
	 //Mengisi 1 baris setelah baris terakhir dengan baris pertama (array toroidal)
    for(j=0;j<cols_game;j++)
	{
		arr[rows_game][j] = arr[0][j];
	}; 
	
	//Mengisi kolom ke -1 dengan kolom terakhir (array toroidal)
    for(j=0;j<rows_game;j++)
	{
		arr[j][-1] = arr[j][(cols_game_)-1];
	}; 
    
    //Mengisi 1 kolom setelah kolom terakhir dengan kolom pertama (array toroidal)
    for(j=0;j<cols_game;j++)
	{
		arr[j][cols_game] = arr[j][0];
	}; 
	
	//Mengisi baris dan kolom ke -1 (pojok kiri atas)
	arr[-1][-1] = arr[(rows_game)-1][(cols_game)-1];
    
    //Mengisi baris ke -1 dan 1 kolom setelah kolom terakhir  (pojok kanan atas)
	arr[-1][cols_game] = arr[(rows_game)-1][0];
    
     //Mengisi kolom ke -1 dan 1 baris setelah baris terakhir  (pojok kiri bawah)
	arr[rows_game][-1] = arr[0][(cols_game)-1];
	
	 //Mengisi 1 baris setelah baris terakhir dan 1 kolom setelah kolom terakhir (pojok kanan bawah)
	arr[rows_game][cols_game] = arr[0][0];
    */
    //Proses utama
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
            if((arr[i][j] == 'X')&&((cellNeighbors(arr,i,j)-1) < 2)){	//di -1 karena proses cellNeighbors menghitung dirinya sendiri(tidak hanya disekelilignya)
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

//Apakah ini dipakai?
bool lanjut_iterasi(char arr1[rows_game][cols_game], char arr2[rows_game][cols_game])
{
    for(int i = 0; i<rows_game;i++){
        for(int j = 0; j<cols_game;j++)
        {
            if (arr1[i][j]==arr2[i][j]){
                return false;
            }else{
                return true;
            };
        };
    };
};

void delay(int longtime)
{
    int ms = 1000*longtime;
    clock_t start = clock();
    while (clock() < start+ms)
        ;
};

void jumlah_iterasi(char arr[rows_game][cols_game], char future[rows_game][cols_game], int N)
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
