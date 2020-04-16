/*
* EL2208 Praktikum Pemecahan Masalah dengan C 2019/2020
* MODUL 9 – TUGAS BESAR
* Kelompok          : 5
* Hari dan Tanggal  : Kamis, 16 April 2020
* Asisten (NIM)     : Rizky Ardi Maulana (13217054)
* Nama File         : utamarev5.c
* Deskripsi         : Implementasi main function rev0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gameFuncrev5.h"

int main()
{
    FILE *fp;
    int pilihan, iterasi;
    char lanjutmain;
    char filename[100];
    int column, row;
    int finish=0; //finish=0 berarti program belum selesai, finish = 1 berarti program telah selesai

    //Deskripsi program
    system("cls");
    printf("********************Conway's Game Of Life*********************\n");
    printf("--------------------------------------------------------------\n");
    printf("Asisten : Rizky Ardi Maulana\n\n\n");
    printf("                        Kelompok 5\n");
    printf("               Cedric Samuel           (13218060)\n");
    printf("               Muhammad Ali Novandhika (13218067)\n");
    printf("               Achmad Rifqy Pratama    (13218069)\n");
    printf("               Muhammad Heronan Hyanda (13218073)\n\n");
	printf("Peraturan Conway's Game Of Life\n");
	printf("1. Jika terdapat sebuah sel hidup yang memiliki kurang dari 2 tetangga\n   yang hidup, sel tersebut mati pada iterasi selanjutnya (underpopulation).\n");
    printf("2. Jika terdapat sebuah sel hidup yang memiliki 2 atau 3 tetangga yang\n   hidup, sel tersebut tetap hidup pada iterasi selanjutnya (next generation).\n");
    printf("3. Jika terdapat sebuah sel hidup yang memiliki lebih dari 3 tetangga\n   yang hidup, sel tersebut mati pada iterasi selanjutnya (overpopulation).\n");
    printf("4. Jika terdapat sebuah sel mati yang memiliki 3 tetangga yang hidup,\n   sel tersebut menjadi hidup pada iterasi selanjutnya (reproduction).\n\n\n");

    //Opening file
    printf("Masukkan nama file: ");
    gets(filename);
	fp = fopen(filename, "r");

	//Kasus apabila file tidak ditemukan
	while(fp==NULL)
	{
		printf("File tidak ditemukan. Silahkan masukkan ulang nama file.\n");
		printf("Masukkan nama file: ");
		gets(filename);
		fp = fopen(filename, "r");
	};

    //Dapatkan nilai MxN untuk multi dimensional array
    fscanf(fp, "%d", &row);
    fscanf(fp, "%d", &column);

    rows_game = row;
    cols_game = column;

    //Inisialisasi array penyimpanan life component
    char **MultiArray = (char **) malloc(row * sizeof(char *));
    for (int i = 0; i < row; i++) {
        MultiArray[i] = (char *) malloc(column * sizeof(char));
    }

    char **nextArray = (char **) malloc(row * sizeof(char *));
    for (int i = 0; i < row; i++) {
        nextArray[i] = (char *) malloc(column * sizeof(char));
    }

    char temp;

	//Mengisi variable MultiArray dengan data seed (file eksternal)
    fillArray(MultiArray, fp);

    //Menampilkan seed pada console
    showArray(MultiArray);

	//Pilihan untuk user
    printf("Daftar menu yang tersedia : \n");
    printf("1. Animate\n2. Tick\n3. End of itteration\n4. Quit\n");
    printf("Pilihan menu yang diinginkan : ");
    scanf("%d", &pilihan);

	while(finish==0)
	{
		//Kasus apabila input menu salah
		while((pilihan > 4)||(pilihan < 1))
		{
			printf("Input salah. Silahkan pilih ulang menu yang diinginkan\n");
			printf("Pilihan menu yang diinginkan : ");
			scanf("%d", &pilihan);
		};

		//Kasus apabila input menu benar
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
				end_generation(MultiArray,nextArray);
			}
			else
			{
				printf("Apakah Anda ingin melanjutkan permainan? \n(Ketikkan 'Y' / 'y' untuk ya dan 'N' / 'n' untuk tidak)\n");
				printf("Jawab : ");
				scanf("%s",&lanjutmain);

				char junk;
				scanf("%c", &junk); //Untuk menampung enter terakhir

				if((lanjutmain == 'Y')||(lanjutmain == 'y')){
					printf("Masukkan nama file: ");
					gets(filename);
					fp = fopen(filename, "r");

					//Kasus apabila file tidak ditemukan
					while(fp==NULL)
					{
						printf("File tidak ditemukan. Silahkan masukkan ulang nama file.\n");
						printf("Masukkan nama file: ");
						gets(filename);
						fp = fopen(filename, "r");
					};

					fscanf(fp, "%d", &row);
					fscanf(fp, "%d", &column);
					system("cls");

					rows_game = row;
					cols_game = column;

                    //resize array sesuai file baru
                    MultiArray = (char **) realloc(MultiArray, row * sizeof(char *));
                    for (int i = 0; i < row; i++) {
                        MultiArray[i] = NULL;
                    }
                    for (int i = 0; i < row; i++) {
                        MultiArray[i] = (char *) realloc(MultiArray[i], column * sizeof(char));
                    }

                    nextArray = (char **) realloc(nextArray, row * sizeof(char *));
                    for (int i = 0; i < row; i++) {
                        nextArray[i] = NULL;
                    }
                    for (int i = 0; i < row; i++) {
                        nextArray[i] = (char *) realloc(nextArray[i], column * sizeof(char));
                    }

					fillArray(MultiArray, fp);
					showArray(MultiArray);
				}
				else if((lanjutmain == 'N')||(lanjutmain == 'n')){
					printf("Permainan selesai.\n");
					finish=1;
					break;
				};
			};
			printf("Daftar menu yang tersedia : \n");
			printf("1. Animate\n2. Tick\n3. End of itteration\n4. Quit\n");
			printf("Pilihan menu yang diinginkan : ");
			scanf("%d", &pilihan);
		};
	 };

    printf("\n--------------------Terima Kasih---------------------\n");
    return (0);
}