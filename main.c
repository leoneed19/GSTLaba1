#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>


//TODO короче в rank == 0 делаем инициализацию, дальше Bcast посылает M N Size может что-то еще..Затем scatter потом recv потом gather результат в rank == 0

//#include <gmpxx.h>

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
//void writeToFile(int *arrayOfAvg, double time, int M) {
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

int *myf(int N, int M, int size, int *recvbuf) {
    int i, j;
    int avg;
    int * arrayOfAvgLittle = (int *) malloc(M / size * sizeof(int));
    for (i = 0; i < M / size; i++) {
        int summ = 0;
        for (j = 0; j < N; j++) {
            summ = summ + recvbuf[j];
        }
        avg = summ / N;
        printf("%ld", avg);
        arrayOfAvgLittle[i] = avg;
        //MPI_Send(&avg, 1, MPI_LONG_INT, 0, 0, MPI_COMM_WORLD);
    }
    return arrayOfAvgLittle;
}

struct MyStruct readFromFile() {
    int n = 0, s = 0, k = 0;
    int iterations = 0;
    struct MyStruct result;
    FILE *myFile;
    myFile = fopen("input.txt", "r");
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

    int *arrayOfAvgLittle = (int *) malloc(50 * sizeof(int));
    int *res;
    int *arrayOfAvg = (int *) malloc(10 * sizeof(int));;
    int N = 0, M = 0, i = 0, j = 0, rank, size, rc, resultat;
    if ((rc = MPI_Init(&argc, &argv)) != MPI_SUCCESS) {

        fprintf(stderr, "Error starting MPI program. Terminating.\n");

        MPI_Abort(MPI_COMM_WORLD, rc);

    }

    struct MyStruct result = readFromFile();

    N = result.n;
    M = result.m;
    if (rank == 0) {
        int summ = 0, avg = 0, avgValue = 0;
        double tt;
        //struct MyStruct result = readFromFile();
        int *res;
        //N = result.n;
        //M = result.m;
        res = result.res;
        int *arrayOfAvg = (int *) malloc(M * sizeof(int));
        //MPI_Bcast(&M, 1, MPI_INT,0, MPI_COMM_WORLD);
        //M = 10;
//        MPI_Bcast(&N, 1, MPI_INT,0, MPI_COMM_WORLD);
    }
    printf("%d", M);
    MPI_Bcast(&M, 1, MPI_INT,0, MPI_COMM_WORLD);
    //MPI_Init(&argc, &argv);

    int *recvbuf;
    /// Возвращает количество процессов в данном коммуникаторе
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    /// Возвращает наш ранк
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("process %d of %d \n", rank, size);
    //printf("jopa");

    /// Таймирование
    //double start = MPI_Wtime();
    /// Основной код
    // MPI_Barrier(MPI_COMM_WORLD);
    int *resss = (int *) malloc(M * sizeof(int));
    //    int *recvbuf = (int *) malloc(M / size * sizeof(int));
//    if (rank == 0) {
//    recvbuf = (int *) malloc(M  * N/ size * sizeof(int));
//    }
    recvbuf = (int *) malloc(M * N / size * sizeof(int));
    //recvbuf = (int *) malloc(M * sizeof(int));
    //recvbuf2 = (int *) malloc(M * sizeof(int));
    //if (rank == 0) {
    //printf("Number of tasks=%d\n", size);
    //printf("jopa");
    //MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    //recvbuf2 = (int *) malloc(M * sizeof(int));
    //}
    //if (rank != 0){
    //if (rank == 0) {
    //printf("M=%d",3);
    MPI_Status status;
   // MPI_Recv(&M, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    MPI_Scatter(res, M * N / size, MPI_LONG_INT, recvbuf, M * N / size, MPI_LONG_INT, 0, MPI_COMM_WORLD);
    //}
   // printf("efwegerg");

    printf("%ld",recvbuf[0]);
    printf("\n");
    printf("%ld",recvbuf[1]);
    printf("\n");
    printf("%ld",recvbuf[2]);
    printf("\n");
    //printf("My rank=%d recvbuf=%ld recvbuf=%ld avgValue=%ld\n", rank, recvbuf[0], recvbuf[1], avgValue);
    arrayOfAvgLittle = myf(N, M, size, recvbuf);
    printf("M%d",M);
    //}
    //MPI_Reduce(&recvbuf, &summ, M, MPI_INT, MPI_SUM, rank, MPI_COMM_WORLD);
    //avg = summ / N;
    //MPI_Gather(&avg, 1, MPI_LONG_INT, arrayOfAvg, 1, MPI_LONG_INT, rank, MPI_COMM_WORLD);
    //MPI_Reduce(&avg, &resss, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    //MPI_Gather(arrayOfAvgLittle, M / size, MPI_LONG_INT, arrayOfAvg, M / size, MPI_LONG_INT, 0, MPI_COMM_WORLD);
    //printf("%ld", recvbuf[0]);
    //printf("%ld", recvbuf[1]);
   // printf("efwegerg");
    //if (rank != 0){
    MPI_Gather(arrayOfAvgLittle, M * N / size, MPI_LONG_INT, arrayOfAvg, M * N / size, MPI_LONG_INT, rank,
               MPI_COMM_WORLD);
 //   printf("efwegerg");
    printf("%ld",arrayOfAvg[0]);
    printf("%ld",arrayOfAvg[1]);
    printf("%ld",arrayOfAvg[2]);

    //}

    //MPI_Gather(arrayOfAvgLittle, M * N / size, MPI_LONG_INT, arrayOfAvg, M * N / size, MPI_LONG_INT, rank,
      //         MPI_COMM_WORLD);

    /*if (rank != 0) {
       // for (int ii = 0; ii < size; ii++)
            printf("%id",rank);

            //MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    }*/
        /*for (i = 0; i < M; i++) {
            summ = 0;
            for (j = 0; j < N; j++) {
                summ = summ + res[i * N + j];
            }

            arrayOfAvg[i] = avgValue;
            avg = summ / N;
            MPI_Send(&avg, 1, MPI_LONG_INT, 0, 0, MPI_COMM_WORLD);
        }*/
        //MPI_Gather(res, 1 , MPI_LONG_INT, recvbuf, 1, MPI_LONG_INT, 0, MPI_COMM_WORLD);
 //       printf("%ld", recvbuf[0]);
   //     printf("%ld", recvbuf[1]);
        //printf("jopa");
        //MPI_Status status;
        //MPI_Recv(&valueN, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        //int *recvbuf2 = (int *) malloc(M * sizeof(int));
        //printf((const char *) recvbuf[0]);
        // MPI_Recv(&valueN, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
         //printf("%s","rank = 0");


    //}


    /*if (rank == 0) {
        for (j = 0; j < size; j++) {
            MPI_Recv(&avgValue, 1, MPI_LONG_INT, j, MPI_COMM_WORLD, &status);
        }
        arrayOfAvg[i] = avgValue;
    }*/
    /*printf("%d", valueN);
    for (i = 0; i < M; i++) {
        printf("%ld", arrayOfAvg[i]);
        printf("\t");
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