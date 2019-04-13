#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

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
    int N = 0, M = 0, i = 0, j = 0, rank, size, rc, resultat;
    long int summ = 0, avg = 0, avgValue = 0;
    double tt;
    struct MyStruct result = readFromFile();
    long int *res;
    N = result.n;
    M = result.m;
    res = result.res;
    long int *arrayOfAvg = (long int *) malloc(M * sizeof(long int));


    int valueN = 0;
    int gg = 0, razmer = 0, x = 0;

    printf("%d", M);

    //MPI_Init(&argc, &argv);
    if ((rc = MPI_Init(&argc, &argv)) != MPI_SUCCESS) {

        fprintf(stderr, "Error starting MPI program. Terminating.\n");

        MPI_Abort(MPI_COMM_WORLD, rc);

    }
    long int *recvbuf;
    long int *recvbuf2;
    /// Возвращает количество процессов в данном коммуникаторе
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    /// Возвращает наш ранк
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("process %d of %d \n", rank, size);
    //printf("jopa");

    /// Таймирование
    //double start = MPI_Wtime();
    /// Основной код

    //  есть идея как-то разделить входной массив данных на 3 части каждую посчитать на своем узле и отправить на
    //  нулевой ранк где мы добавляем наши средние суммы в массив
    // MPI_Barrier(MPI_COMM_WORLD);

//    long int *recvbuf = (long int *) malloc(M / size * sizeof(long int));

    recvbuf = (long int *) malloc(M * sizeof(long int));
//    recvbuf2 = (long int *) malloc(M * sizeof(long int));
    if (rank == 0) {
        printf("Number of tasks=%d\n", size);
        //printf("jopa");
        //MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
        recvbuf = (long int *) malloc(M * sizeof(long int));
        recvbuf2 = (long int *) malloc(M * sizeof(long int));
    }
    MPI_Scatter(res, M , MPI_LONG_INT, recvbuf, M , MPI_LONG_INT, 0, MPI_COMM_WORLD);

    /*for (i = 0; i < M / size; i++) {
        summ = 0;
        for (j = 0; j < N; j++) {
            summ = summ + recvbuf[j];
        }
//        arrayOfAvg[i] = avgValue;
        avg = summ / N;
        //MPI_Send(&avg, 1, MPI_LONG_INT, 0, 0, MPI_COMM_WORLD);
    }*/
    //printf("My rank=%d recvbuf=%ld recvbuf=%ld avgValue=%ld\n", rank, recvbuf[0], recvbuf[1], avgValue);

    MPI_Reduce(&recvbuf, &summ, M, MPI_INT, MPI_SUM, rank, MPI_COMM_WORLD);
    avg = summ / N;
    MPI_Gather(&avg, 1 , MPI_LONG_INT, arrayOfAvg, 1 , MPI_LONG_INT, rank, MPI_COMM_WORLD);
    if (rank == 0) {
        /*for (i = 0; i < M; i++) {
            summ = 0;
            for (j = 0; j < N; j++) {
                summ = summ + res[i * N + j];
            }

            arrayOfAvg[i] = avgValue;
            avg = summ / N;
            MPI_Send(&avg, 1, MPI_LONG_INT, 0, 0, MPI_COMM_WORLD);
        }*/

        //printf("jopa");
        //MPI_Status status;
        //MPI_Recv(&valueN, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("%d", valueN);
        for (i = 0; i < M; i++) {
            printf("%ld", arrayOfAvg[i]);
        }
        //long int *recvbuf2 = (long int *) malloc(M * sizeof(long int));
        //printf((const char *) recvbuf[0]);
        // MPI_Recv(&valueN, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        // printf("%d",valueN);
    }


    /*if (rank == 0) {
        for (j = 0; j < size; j++) {
            MPI_Recv(&avgValue, 1, MPI_LONG_INT, j, MPI_COMM_WORLD, &status);
        }
        arrayOfAvg[i] = avgValue;
    }*/

    /// Таймирование
    //double end = MPI_Wtime();
    //tt = end - start;

    MPI_Finalize();
    printf("\n");
    //printf("%f", tt);

    //writeToFile(arrayOfAvg, tt, M);
    return 0;
}