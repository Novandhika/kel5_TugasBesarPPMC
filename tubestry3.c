#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "gameFunc.h"

int main()
{
    FILE *fp;
    int pilihan, iterasi;
    char lanjutmain;
    char filename[100];
    int arrayInfo[2] = {0};
    int column, row;
    int b,k;

    printf("********************GAME OF LIFE*********************\n\n");
    printf("Permainan ini adalah permainan yang sangat seru gaess");
    printf("\n\n");
    A :
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

    printf("Daftar menu yang tersedia : \n");
    printf("1. Animate\n2. Tick\n3. End of itteration\n4. Quit\n");
    printf("Pilihan menu yang diinginkan> ");
    scanf("%d", &pilihan);
    while(pilihan != 4)
    {
        if(pilihan == 1)
        {
            printf("Jumlah iterasi yang diinginkan : ");
            scanf("%d", &iterasi);
            system("cls");
            jumlah_iterasi(MultiArray,nextArray,iterasi);
        }
        else if(pilihan == 2){
            showArray(MultiArray);
            nextGeneration(MultiArray,nextArray);
            showArray(nextArray);
        }
        else if(pilihan == 3)
        {
            system("cls");
            delay(0.25);
            nextGeneration(MultiArray, nextArray);
            showArray(nextArray);
            system("cls");
            delay(0.25);
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
                system("cls");
                delay(0.25);
            }
            showArray(nextArray);
        }
        B :
        printf("Daftar menu yang tersedia : \n");
        printf("1. Animate\n2. Tick\n3. End of itteration\n4. Quit\n");
        printf("Pilihan menu yang diinginkan> ");
        scanf("%d", &pilihan);
    }
    if(pilihan == 4){
        printf("Masih ingin bermain? Y/N > ");
        scanf("%c%c",lanjutmain);
        if((lanjutmain == 'Y')||(lanjutmain == 'y')){
            goto A;
        }
    }
    else{
        printf("Masukkan pilihan dari 1 sampai 4");
        goto B;
    }
    return 0;
}
