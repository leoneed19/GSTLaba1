#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

/// to compile: mpicc main.c -o main
/// to run:     mpirun main

struct MyStruct {
    int m;
    int n;
    long int *res;
};


void writeToFile(long int *arrayOfAvg, double time, int M) {
//void writeToFile(long int *arrayOfAvg, double time, int M) {
    int i;
    FILE *writeFile;
    writeFile = fopen("output.txt", "w");
    //TODO раскоментить!!!!
    /*for (i = 0; i < M; i++) {
        fprintf(writeFile, "%d", arrayOfAvg[i]);
        fprintf(writeFile, "%s", "\t");
        // printf("%d ", arrayOfAvg[i]);
        // printf("\t");
    }*/
    fprintf(writeFile, "\n");
    fprintf(writeFile, "%f ", time);
    fprintf(writeFile, "\n");
    fclose(writeFile);
}


struct MyStruct readFromFile() {
    int n = 0, s = 0, k = 0;
    int iterations = 0;
    struct MyStruct result;
    FILE *myFile;
    myFile = fopen("input.txt", "r");
    long int *Res;

    while ((fscanf(myFile, "%d", &s) != EOF)) {
        if (!myFile)
            break;
        k += 1;
    }

    Res = (long int *) malloc(k * sizeof(long int));
    rewind(myFile);
    for (int i = 0; i < k; i++) {
        if (iterations == 0) {
            fscanf(myFile, "%d", &result.m);
            iterations++;
        }
        if (iterations == 1) {
            fscanf(myFile, "%d", &result.n);
            iterations++;
        }
        fscanf(myFile, "%li", &Res[i]);
        // printf("c[%d]=%d  ", i, Res[i]);
        // printf("\t");
    }
    printf("\n");
    result.res = Res;
    fclose(myFile);
    return result;
}


int main(int argc, char **argv) {
    int N = 0, M = 0, i = 0, j = 0, rank, size;
    long int summ = 0, avg = 0, avgValue = 0;
    double tt;
    struct MyStruct result = readFromFile();
    long int *res;
    N = result.n;
    M = result.m;
    res = result.res;
    long int *arrayOfAvg = (long int *) malloc(M * sizeof(long int));

    MPI_Init(&argc, &argv);
    /// Возвращает количество процессов в данном коммуникаторе
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    /// Возвращает наш ранк
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    printf("process %d of %d \n", rank, size);
    /// Таймирование
    double start = MPI_Wtime();
    /// Основной код

    // TODO есть идея как-то разделить входной массив данных на 3 части каждую посчитать на своем узле и отправить на
    //  нулевой ранк где мы добавляем наши средние суммы в массив
    // MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 1) {
        for (i = 0; i < M / 3; i++) {
            summ = 0;
            for (j = 0; j < N; j++) {
                summ = summ + res[i * N + j];
            }
            avg = summ / N;
            MPI_Send(&avg, 1, MPI_LONG_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    if (rank == 2) {
        for (i = M / 3; i < 2 * M / 3; i++) {
            summ = 0;
            for (j = 0; j < N; j++) {
                summ = summ + res[i * N + j];
            }
            avg = summ / N;
            MPI_Send(&avg, 1, MPI_LONG_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    if (rank == 3) {
        for (i = 2 * M / 3; i < M; i++) {
            summ = 0;
            for (j = 0; j < N; j++) {
                summ = summ + res[i * N + j];
            }
            avg = summ / N;
            MPI_Send(&avg, 1, MPI_LONG_INT, 0, 0, MPI_COMM_WORLD);
        }
    }
 /*   if (rank == 1) {
        for (i = 0; i < M; i++) {
            summ = 0;
            for (j = 0; j < N; j++) {
                summ = summ + res[i * N + j];
            }
            avg = summ / N;
            MPI_Send(&avg, 1, MPI_LONG_INT, 0, 0, MPI_COMM_WORLD);
        }
    }*/

    if (rank == 0) {
        for (i = 0; i < M/3; i++) {
            MPI_Recv(&avgValue, 1, MPI_LONG_INT, 1, 0, MPI_COMM_WORLD, &status);
            arrayOfAvg[i] = avgValue;
        }
        for (i = M/3; i < 2*M/3; i++) {
            MPI_Recv(&avgValue, 1, MPI_LONG_INT, 2, 0, MPI_COMM_WORLD, &status);
            arrayOfAvg[i] = avgValue;
        }
        for (i = 2*M/3; i < M; i++) {
            MPI_Recv(&avgValue, 1, MPI_LONG_INT, 3, 0, MPI_COMM_WORLD, &status);
            arrayOfAvg[i] = avgValue;
        }
    }

    /// Таймирование
    double end = MPI_Wtime();
    tt = end - start;

    MPI_Finalize();
    printf("\n");
    printf("%f", tt);

    writeToFile(arrayOfAvg, tt, M);
    return 0;
}