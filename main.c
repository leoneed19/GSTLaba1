#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


struct MyStruct {
    int m;
    int n;
    int *res;
};


void writeToFile(int *arrayOfAvg, long int time, int M) {
    int i;
    FILE *writeFile;
    writeFile = fopen("../output.txt", "w");
    for (i = 0; i < M; i++) {
        fprintf(writeFile, "%d", arrayOfAvg[i]);
        fprintf(writeFile, "%s", "\t");
        // printf("%d ", arrayOfAvg[i]);
        // printf("\t");
    }
    fprintf(writeFile, "\n");
    fprintf(writeFile, "%li ", time);
    fprintf(writeFile, "\n");
    fclose(writeFile);
}


struct MyStruct readFromFile() {
    int n = 0, s, k = 0;
    int iterations = 0;

    struct MyStruct result;

    FILE *myFile;
    myFile = fopen("../input.txt", "r");

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
        fscanf(myFile, "%d", &Res[i]);
        // printf("c[%d]=%d  ", i, Res[i]);
        // printf("\t");
    }
    printf("\n");
    result.res = Res;
    fclose(myFile);
    return result;
}


int main() {
    int N, M, i, j, summ, avg;
    struct MyStruct result = readFromFile();
    int *res;


    N = result.n;
    M = result.m;
    res = result.res;
    printf("%d", N);
    printf("\n");
    printf("%d", M);

    int *arrayOfAvg = (int *) malloc(M * sizeof(int));

    struct timespec mt1, mt2;
    long int tt;

    // Основной код
    clock_gettime(CLOCK_REALTIME, &mt1);
    for (i = 0; i < M; i++) {
        summ = 0;
        for (j = 0; j < N; j++) {
            summ = summ + res[i * N + j];
        }
        avg = summ / N;
        arrayOfAvg[i] = avg;
    }
    clock_gettime(CLOCK_REALTIME, &mt2);

    tt = 1000000000 * (mt2.tv_sec - mt1.tv_sec) + (mt2.tv_nsec - mt1.tv_nsec);

    printf("\n");

    writeToFile(arrayOfAvg, tt, M);

    return 0;
}