/* EL2208 Praktikum Pemecahan Masalah dengan C 2019/2020  
* MODUL 9 – TUGAS BESAR  
* Kelompok          : 5  
* Hari dan Tanggal  : Jumat, 10 April 2020  
* Asisten (NIM)     : Rizky Ardi Maulana (13217054)   
* Nama File         : utamarev1.c
* Deskripsi         : Implementasi main function rev0  
*/

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
    system("cls");
    printf("********************GAME OF LIFE*********************\n\n");
    printf("Permainan ini adalah permainan yang sangat seru gaess");
    printf("\n\n");
    
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

    while((pilihan <= 4)&&(pilihan >= 1))
    {
        if(pilihan == 1)
        {
            printf("Jumlah iterasi yang diinginkan : ");
            scanf("%d", &iterasi);
            system("cls");
            jumlah_iterasi(MultiArray,nextArray,iterasi);
        }
        else if(pilihan == 2){
            jumlah_iterasi(MultiArray,nextArray,1);
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
            showArray(MultiArray);
        }
        else
        {
            printf("Masih ingin bermain? Y/N > ");
            scanf("%s",&lanjutmain);
            if((lanjutmain == 'Y')||(lanjutmain == 'y')){
                printf("Masukkan nama file: ");
                scanf("%s",&filename);
                fp = fopen(filename, "r");
                fscanf(fp, "%d", &row);
                fscanf(fp, "%d", &column);
                system("cls");
                rows_game = row;
                cols_game = column;
                fillArray(MultiArray, fp);
                showArray(MultiArray);
            }
            else if((lanjutmain == 'N')||(lanjutmain == 'n')){
                printf("Permainan selesai.\n");
                break;
            }
        }
        printf("Daftar menu yang tersedia : \n");
        printf("1. Animate\n2. Tick\n3. End of itteration\n4. Quit\n");
        printf("Pilihan menu yang diinginkan> ");
        scanf("%d", &pilihan);
    }
    // printf("Masukkan pilihan dari 1 sampai 4 !\n\n");
    // printf("Daftar menu yang tersedia : \n");
    // printf("1. Animate\n2. Tick\n3. End of itteration\n4. Quit\n");
    // printf("Pilihan menu yang diinginkan> ");
    // scanf("%d", &pilihan);
    return 0;
}
