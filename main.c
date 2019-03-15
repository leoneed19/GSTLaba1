#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
int N;
int M;
struct StructMatrix {
    int A[N][M];
    int N;
    int M;
};*/
// Чтение из файла
int * readFromFile(N, M) {
    FILE *ptrfile;
    //printf("Использовали файл: %s", argv[1]);
    //printf("\n");
    int i,j,k;
    char file_name[255] = "../IN.txt";
    k = 0;
    int s;
    int B[N][M];
    //int** p = (int **) A;
    ptrfile = fopen(file_name, "r+");
    //printf(ptrfile);
    while ((fscanf(ptrfile, "%d", &s) != EOF)) {
        if (!ptrfile)
            break;
        k += 1;
    }
    int *A = (int *) malloc(k * sizeof(int));
    rewind(ptrfile);
    for (int i = 0; i < k; i++) {
        fscanf(ptrfile, "%d", &A[i]);
        printf("c[%d]=%d  ", i, A[i]);
        printf("\n");
    }
    /*int x = M;
    for (i = 0; i < N; i++ ) {
        for (j = 0; j < M; j++) {
            B[i][j] = A[x*i+j];
            printf("%d ", B[i][j]);
            printf("c[%d]=%d  ", i, B[i][j]);
        }
        printf("\n");
    }*/
  //  int* ptr = (int *) &A;

    return A;
}


int main() {
    //FILE *myfile;
    int N,M,i,j;

    N = 100;
    M = 50;
  /*  scanf("%d",&N);
    scanf("%d",&M);*/
    //int A[N][M];
    int B[N][M];
    int Res[N];
    int *ptr;
    ptr = readFromFile(N, M);
   /* for (i = 0; i < N; i++ ) {
        for (j = 0; j < M; j++) {
            A[i][j] = 10 + rand() % (20 - 10 + 1);
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
*/
    int *A = ptr;

    int x = M;
    for (i = 0; i < N; i++ ) {
        for (j = 0; j < M; j++) {
            B[i][j] = A[x*i+j];
            printf("%d ", B[i][j]);
            printf("c[%d]=%d  ", M*i+j, B[i][j]);
        }
        printf("\n");
    }
   
   for (i = 0; i < N; i++) {
        int summ = 0;
        for (j = 0; j < M; j++) {
            summ =  summ + B[i][j];
        }
        //Формирование результрующего массива как среднего по каждой строке
        Res[i] = summ / M;
    }

    printf("%s ","Res");
    for (i = 0; i < N; i++ ) {
        //for (j = 0; j < M; j++) {
        //A[i][j] = 10 + rand() % (20 - 10 + 1);
        printf("%d ", Res[i]);


        //}
        printf("\t");
    }


    FILE *file;
    if ((file=fopen("../OUT.txt","w"))==NULL) {
        printf("Невозможно открыть файл\n");
        exit(1);
    };

    for (i = 0; i < N; i++) {
        fprintf(file, "%i ", Res[i]);
    }
    fprintf(file, "\n");


    return 0;
}


