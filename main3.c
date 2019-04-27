#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
//#include <gmpxx.h>

/// to compile: mpicc main.c -o main
/// to run:     mpirun main
/// to run with 4 threads: mpiexec --use-hwthread-cpus --n 4 ./main
/// to run with 2 threads: mpiexec -np 2 ./main

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

long int *myf(int N, int M, int size, long int *recvbuf) {
    int i, j;
    long int avg;
    long int * arrayOfAvgLittle = (long int *) malloc(M / size * sizeof(long int));
    for (i = 0; i < M / size; i++) {
        int summ = 0;
        for (j = 0; j < N; j++) {
            summ = summ + recvbuf[j];
        }
        avg = summ / N;
        printf("%ld", avg);
        arrayOfAvgLittle[i] = avg;
    }
    return arrayOfAvgLittle;
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
    int N = 0, M = 0, i = 0, j = 0, rank, size, rc, resultat;
    long int summ = 0, avg = 0, avgValue = 0;
    double tt;
    struct MyStruct result = readFromFile();
    long int *res;
    N = result.n;
    M = result.m;
    res = result.res;
    long int *arrayOfAvg = (long int *) malloc(M * sizeof(long int));


    printf("%d", M);

    if ((rc = MPI_Init(&argc, &argv)) != MPI_SUCCESS) {

        fprintf(stderr, "Error starting MPI program. Terminating.\n");

        MPI_Abort(MPI_COMM_WORLD, rc);

    }
    long int *recvbuf;

    /// Возвращает количество процессов в данном коммуникаторе
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    /// Возвращает наш ранк
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("process %d of %d \n", rank, size);

    long int *arrayOfAvgLittle = (long int *) malloc(M * N/ size * sizeof(long int));

    /// Таймирование
    //double start = MPI_Wtime();
    /// Основной код

    //long int *resss = (long int *) malloc(M * sizeof(long int));
    recvbuf = (long int *) malloc(M * N / size * sizeof(long int));
    if (rank == 0) {
        MPI_Scatter(res, M * N / size, MPI_LONG_INT, recvbuf, M * N / size, MPI_LONG_INT, rank, MPI_COMM_WORLD);
    }
    printf("efwegerg");
    arrayOfAvgLittle = myf(N, M, size, recvbuf);
    printf("efwegerg");
    if (rank != 0){
        MPI_Gather(arrayOfAvgLittle, M * N / size, MPI_LONG_INT, arrayOfAvg, M * N / size, MPI_LONG_INT, rank,
                   MPI_COMM_WORLD);
        printf("efwegerg");

    }

    /// Таймирование
    //double end = MPI_Wtime();
    //tt = end - start;

    MPI_Finalize();
    printf("\n");
    //printf("%f", tt);

    //writeToFile(arrayOfAvg, tt, M);
    return 0;
}