#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

struct MyStruct {
    int m;
    int n;
    long int *res;
};


void writeToFile(long int *arrayOfAvg, long int time, int M) {
    int i;
    FILE *writeFile;
    writeFile = fopen("../output.txt", "w");
    //TODO раскоментить!!!!
    /*for (i = 0; i < M; i++) {
        fprintf(writeFile, "%d", arrayOfAvg[i]);
        fprintf(writeFile, "%s", "\t");
        // printf("%d ", arrayOfAvg[i]);
        // printf("\t");
    }*/
    fprintf(writeFile, "\n");
    fprintf(writeFile, "%li ", time);
    fprintf(writeFile, "\n");
    fclose(writeFile);
}


struct MyStruct readFromFile() {
    int n = 0, s = 0, k = 0;
    int iterations = 0;

    struct MyStruct result;

    FILE *myFile;
    myFile = fopen("../input.txt", "r");

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


int main() {
    printf("aaaaa");
//    int N, M, i, j, summ, avg;
    int N = 0, M = 0, i = 0, j = 0, avg = 0;
    long int summ = 0;
    // printf("%d", 2);
    struct MyStruct result = readFromFile();
    long int *res;


    N = result.n;
    M = result.m;
    res = result.res;
    printf("%d", N);
    printf("\n");
    printf("%d", M);

    long int *arrayOfAvg = (long int *) malloc(M * sizeof(long int));

    struct timespec mt1, mt2;
    long int tt;

    // Основной код
    clock_gettime(CLOCK_REALTIME, &mt1);

#pragma omp parallel shared(res, arrayOfAvg) private(i, j, summ, avg)
    {
#pragma omp for
        for (i = 0; i < M; i++) {
            summ = 0;

            for (j = 0; j < N; j++) {
                summ = summ + res[i * N + j];
                // printf("%i", omp_get_thread_num());
                // printf("\n");
            }
            arrayOfAvg[i] = summ / N;
        }
    }
    clock_gettime(CLOCK_REALTIME, &mt2);

    tt = 1000000000 * (mt2.tv_sec - mt1.tv_sec) + (mt2.tv_nsec - mt1.tv_nsec);

    printf("\n");

    writeToFile(arrayOfAvg, tt, M);
    return 0;
}