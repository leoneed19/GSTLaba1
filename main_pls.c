#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <mpi.h>

/// to compile: mpicc main.c -o main
/// to run:     mpirun main
/// to run with 4 threads: mpiexec --use-hwthread-cpus --n 4 ./main
/// to run with 2 threads: mpiexec -np 2 ./main

struct MyStruct {
    int m;
    int n;
    int *res;
};


void writeToFile(int *arrayOfAvg, double time, int M) {
    int i;
    FILE *writeFile;
    writeFile = fopen("/home/mpirun/mpi4py_benchmarks/output.txt", "w");
    for (i = 0; i < M; i++) {
        fprintf(writeFile, "%d", arrayOfAvg[i]);
        fprintf(writeFile, "%s", "\t");
    }
    fprintf(writeFile, "\n");
    fprintf(writeFile, "%f ", time);
    fprintf(writeFile, "\n");
    fclose(writeFile);
}


struct MyStruct readFromFile() {
    int s = 0, k = 0;
    int iterations = 0;
    struct MyStruct result;
    FILE *myFile;
    myFile = fopen("/home/mpirun/mpi4py_benchmarks/input.txt", "r");
//    myFile = fopen("input.txt", "r");
    int *Res;

    while ((fscanf(myFile, "%d", &s) != EOF)) {
        if (!myFile)
            break;
        k += 1;
    }

    Res = (int *) malloc(k * sizeof(int));
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
        fscanf(myFile, "%i", &Res[i]);
    }
    printf("\n");
    result.res = Res;
    fclose(myFile);
    return result;
}


void process_data(int size, int m, const int *resss, int *r) {
    int summ = 0;
    for (int i = 0; i < m / size; i++) {
        summ = 0;
        for (int j = 0; j < m; j++) {
            summ = summ + resss[i * m + j];
        }
        r[i] = summ / m;
    }
}


int main(int argc, char **argv) {
    int M = 0, rank, size, rc;
    int *res;
    int *res2 = NULL;
    double startTime = 0;
    double endTime = 0;
    if ((rc = MPI_Init(&argc, &argv)) != MPI_SUCCESS) {

        fprintf(stderr, "Error starting MPI program. Terminating.\n");

        MPI_Abort(MPI_COMM_WORLD, rc);

    }
    /// Возвращает количество процессов в данном коммуникаторе
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    /// Возвращает наш ранк
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        struct MyStruct result = readFromFile();
        M = result.m;
    }

    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
    res2 = (int *) malloc((M * M) * sizeof(int));

    if (rank == 0) {
        struct MyStruct result = readFromFile();
        res = result.res;
        int i11;
        for (i11 = 0; i11 < M * M; i11++) {
            res2[i11] = res[i11];
        }
        free(res);
    }

    MPI_Bcast(res2, M * M, MPI_INT, 0, MPI_COMM_WORLD);
//    int *send = (int *) malloc(M * M * sizeof(int));
    int *resss = (int *) malloc(M * M / size * sizeof(int));
    int *r = (int *) malloc(M / size * sizeof(int));
    int *r2 = (int *) malloc(M * sizeof(int));
    int part_count = (int) (M * M / size);

    if (rank == 0) {
        startTime = MPI_Wtime();
    }

    MPI_Scatter(res2, part_count, MPI_INT, resss, part_count,
                MPI_INT, 0,
                MPI_COMM_WORLD);
    // что то сделать с данными
    process_data(size, M, resss, r);

    MPI_Gather(r, M / size, MPI_INT, r2, M / size,
               MPI_INT, 0,
               MPI_COMM_WORLD);
    if (rank == 0) {
        endTime = MPI_Wtime();
        FILE *writeFile;
        writeFile = fopen("/home/mpirun/mpi4py_benchmarks/output.txt", "w");
//        writeFile = fopen("output.txt", "w");
        fprintf(writeFile, "%f", endTime - startTime);

    }

    if (rank == 0) {
        free(res2);
    }
    MPI_Finalize();
    //writeToFile(arrayOfAvg, tt, M);
    return 0;
}