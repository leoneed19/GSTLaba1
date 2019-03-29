#include <math.h>
#include <stdlib.h>
#include <stdio.h>


// TO COMPILE cc generator.c -lm -o gen
// TO RUN ./gen


int main() {
    FILE *ptrfile;
    ptrfile = fopen("input.txt", "w");
    float numm;
    scanf("%e", &numm);
    printf("%e", numm);
    int N,M;

    char str[12];
    M = (int) (sqrtf(numm) * 1024.0 / sqrtf(3.061)) ;
    N = (int) (sqrtf(numm) * 1024.0 / sqrtf(3.061)) ;
    sprintf(str, "%d", M);
    fputs(str, ptrfile);
    fputs("\n", ptrfile);

    sprintf(str, "%d", N);
    fputs(str, ptrfile);
    fputs("\n", ptrfile);

    for (int j = 0; j < (int) (sqrtf(numm) * 1024.0 / sqrtf(3.061)); ++j) {
        for (int i = 0; i < (int) ((sqrtf(numm) * 1024.0) / sqrtf(3.061)); ++i) {
            int someInt = 1 + rand() % 100;
            char str[12];
            sprintf(str, "%d", someInt);
            fputs(str, ptrfile);
            fputs("\t", ptrfile);
        }
        fputs("\n", ptrfile);
    }
    fclose(ptrfile);
    return 0;
}